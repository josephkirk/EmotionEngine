#include "EmotionData.h"
#include "Kismet/KismetMathLibrary.h"

// UEmotionData implementation
UEmotionData::UEmotionData()
{
    // Initialize with default values
    Emotion.Intensity = 0.0f;
    Emotion.DecayRate = 1.0f;
    Emotion.InfluenceRadius = 0.1f;
    Emotion.Type = EEmotionType::Core;
    Color = FLinearColor::White;
}

FGameplayTagContainer UEmotionData::GetAllEmotionTags() const
{
    return Emotion.GetAllEmotionTags();
}

FGameplayTagContainer UEmotionData::UpdateIntensity(float DeltaIntensity)
{
    // Store previous tags to compare later
    FGameplayTagContainer PreviousTags = GetAllEmotionTags();
    
    // Update intensity, clamping between 0 and 100
    Emotion.Intensity = FMath::Clamp(Emotion.Intensity + DeltaIntensity, 0.0f, 100.0f);
    
    // Get new tags after intensity update
    FGameplayTagContainer NewTags = GetAllEmotionTags();
    
    // Return only the newly triggered tags (tags that weren't active before)
    FGameplayTagContainer TriggeredTags;
    for (const FGameplayTag& Tag : NewTags)
    {
        if (!PreviousTags.HasTag(Tag))
        {
            TriggeredTags.AddTag(Tag);
        }
    }
    
    return TriggeredTags;
}

void UEmotionData::ApplyDecay(float DeltaTime)
{
    // Apply decay based on the decay rate and time passed
    if (Emotion.Intensity > 0.0f && Emotion.DecayRate > 0.0f)
    {
        float DecayAmount = Emotion.DecayRate * DeltaTime;
        Emotion.Intensity = FMath::Max(0.0f, Emotion.Intensity - DecayAmount);
    }
}

bool UEmotionData::IsOppositeEmotion(const FGameplayTag& EmotionTag) const
{
    return Emotion.OppositeEmotionTag.IsValid() && Emotion.OppositeEmotionTag == EmotionTag;
}

// UEmotionLibrary implementation
UEmotionData* UEmotionLibrary::GetEmotionByTag(const FGameplayTag& EmotionTag) const
{
    for (UEmotionData* EmotionData : Emotions)
    {
        if (EmotionData && EmotionData->Emotion.Tag == EmotionTag)
        {
            return EmotionData;
        }
    }
    return nullptr;
}

TArray<UEmotionData*> UEmotionLibrary::GetOppositeEmotions(const FGameplayTag& EmotionTag) const
{
    TArray<UEmotionData*> Result;
    UEmotionData* SourceEmotion = GetEmotionByTag(EmotionTag);
    
    if (SourceEmotion)
    {
        // Get the direct opposite
        if (SourceEmotion->Emotion.OppositeEmotionTag.IsValid())
        {
            UEmotionData* OppositeEmotion = GetEmotionByTag(SourceEmotion->Emotion.OppositeEmotionTag);
            if (OppositeEmotion)
            {
                Result.Add(OppositeEmotion);
            }
        }
    }
    
    return Result;
}

TArray<UEmotionData*> UEmotionLibrary::GetAdjacentEmotions(const FGameplayTag& EmotionTag, float MaxDistance) const
{
    TArray<UEmotionData*> Result;
    UEmotionData* SourceEmotion = GetEmotionByTag(EmotionTag);
    
    if (SourceEmotion)
    {
        // Find emotions within the specified distance in VA space
        for (UEmotionData* EmotionData : Emotions)
        {
            if (EmotionData && EmotionData != SourceEmotion)
            {
                // Calculate distance in VA space
                float Distance = FVector2D::Distance(SourceEmotion->Emotion.VACoordinate, EmotionData->Emotion.VACoordinate);
                
                // Add to result if within the specified distance
                if (Distance <= MaxDistance)
                {
                    Result.Add(EmotionData);
                }
            }
        }
        
        // Sort by distance (closest first)
        Result.Sort([SourceEmotion](const UEmotionData& A, const UEmotionData& B)
        {
            float DistanceA = FVector2D::Distance(SourceEmotion->Emotion.VACoordinate, A.Emotion.VACoordinate);
            float DistanceB = FVector2D::Distance(SourceEmotion->Emotion.VACoordinate, B.Emotion.VACoordinate);
            return DistanceA < DistanceB;
        });
    }
    
    return Result;
}

UEmotionData* UEmotionLibrary::GetCombinedEmotion(const FGameplayTag& EmotionTag1, const FGameplayTag& EmotionTag2) const
{
    // Check all combination mappings
    for (const UCombinedEmotionMapping* Mapping : CombineEmotions)
    {
        if (Mapping)
        {
            for (const FCombineEmotionMapping& CombineMapping : Mapping->CombinedEmotions)
            {
                // Create a container with the two emotion tags
                FGameplayTagContainer TestContainer;
                TestContainer.AddTag(EmotionTag1);
                TestContainer.AddTag(EmotionTag2);
                
                // Check if this combination matches the mapping
                if (TestContainer.HasAll(CombineMapping.TriggerEmotions) && 
                    TestContainer.Num() == CombineMapping.TriggerEmotions.Num())
                {
                    return CombineMapping.ResultEmotion;
                }
            }
        }
    }
    
    return nullptr;
}

TArray<UEmotionData*> UEmotionLibrary::FindEmotionsInRadius(const FVector2D& VACoordinate, float Radius) const
{
    TArray<UEmotionData*> Result;
    
    // Find all emotions within the specified radius in VA space
    for (UEmotionData* EmotionData : Emotions)
    {
        if (EmotionData)
        {
            // Calculate distance in VA space
            float Distance = FVector2D::Distance(VACoordinate, EmotionData->Emotion.VACoordinate);
            
            // Add to result if within the specified radius
            if (Distance <= Radius)
            {
                Result.Add(EmotionData);
            }
        }
    }
    
    // Sort by distance (closest first)
    Result.Sort([VACoordinate](const UEmotionData& A, const UEmotionData& B)
    {
        float DistanceA = FVector2D::Distance(VACoordinate, A.Emotion.VACoordinate);
        float DistanceB = FVector2D::Distance(VACoordinate, B.Emotion.VACoordinate);
        return DistanceA < DistanceB;
    });
    
    return Result;
}
