#include "EmotionData.h"
#include "Kismet/KismetMathLibrary.h"

// UEmotionDefinition implementation
UEmotionDefinition::UEmotionDefinition()
{
    // Initialize with default values
    //AssetImportData = CreateDefaultSubobject<UAssetImportData>(TEXT("AssetImportData"));
    Emotion.Intensity = 0.0f;
    Emotion.DecayRate = 1.0f;
    Emotion.InfluenceRadius = 0.1f;
    Emotion.Type = EEmotionType::Core;
    Color = FLinearColor::White;
}

void UEmotionDefinition::PostInitProperties()
{
#if WITH_EDITORONLY_DATA
    if (!HasAnyFlags(RF_ClassDefaultObject) && !(GetOuter() && GetOuter()->HasAnyFlags(RF_ClassDefaultObject | RF_ArchetypeObject)))
    {
        AssetImportData = NewObject<UAssetImportData>(this, TEXT("AssetImportData"));
    }
#endif
    Super::PostInitProperties();
}

FGameplayTagContainer UEmotionDefinition::GetAllEmotionTags() const
{
    return Emotion.GetAllEmotionTags();
}

FGameplayTagContainer UEmotionDefinition::UpdateIntensity(float DeltaIntensity)
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

void UEmotionDefinition::ApplyDecay(float DeltaTime)
{
    // Apply decay based on the decay rate and time passed
    if (Emotion.Intensity > 0.0f && Emotion.DecayRate > 0.0f)
    {
        float DecayAmount = Emotion.DecayRate * DeltaTime;
        Emotion.Intensity = FMath::Max(0.0f, Emotion.Intensity - DecayAmount);
    }
}

bool UEmotionDefinition::IsOppositeEmotion(const FGameplayTag& EmotionTag) const
{
    return Emotion.OppositeEmotionTag.IsValid() && Emotion.OppositeEmotionTag == EmotionTag;
}

// UEmotionLibrary implementation
UEmotionDefinition* UEmotionLibrary::GetEmotionByTag(const FGameplayTag& EmotionTag) const
{
    for (UEmotionDefinition* EmotionData : Emotions)
    {
        if (EmotionData && EmotionData->Emotion.Tag == EmotionTag)
        {
            return EmotionData;
        }
    }
    return nullptr;
}

TArray<UEmotionDefinition*> UEmotionLibrary::GetOppositeEmotions(const FGameplayTag& EmotionTag) const
{
    TArray<UEmotionDefinition*> Result;
    UEmotionDefinition* SourceEmotion = GetEmotionByTag(EmotionTag);
    
    if (SourceEmotion)
    {
        // Get the direct opposite
        if (SourceEmotion->Emotion.OppositeEmotionTag.IsValid())
        {
            UEmotionDefinition* OppositeEmotion = GetEmotionByTag(SourceEmotion->Emotion.OppositeEmotionTag);
            if (OppositeEmotion)
            {
                Result.Add(OppositeEmotion);
            }
        }
    }
    
    return Result;
}

FVector2D UEmotionDefinition::GetEmotionCoordinate() const
{
	return Emotion.VACoordinate.GetCartesianCoordinate();
}

TArray<UEmotionDefinition*> UEmotionLibrary::GetAdjacentEmotions(const FGameplayTag& EmotionTag, float MaxDistance) const
{
    TArray<UEmotionDefinition*> Result;
    UEmotionDefinition* SourceEmotion = GetEmotionByTag(EmotionTag);
    
    if (SourceEmotion)
    {
        // Find emotions within the specified distance in VA space
        for (UEmotionDefinition* EmotionData : Emotions)
        {
            if (EmotionData && EmotionData != SourceEmotion)
            {
                // Calculate distance in VA space
                float Distance = FVector2D::Distance(SourceEmotion->GetEmotionCoordinate(), EmotionData->GetEmotionCoordinate());
                
                // Add to result if within the specified distance
                if (Distance <= MaxDistance)
                {
                    Result.Add(EmotionData);
                }
            }
        }
        
        // Sort by distance (closest first)
        Result.Sort([SourceEmotion](const UEmotionDefinition& A, const UEmotionDefinition& B)
        {
            float DistanceA = FVector2D::Distance(SourceEmotion->GetEmotionCoordinate(), A.GetEmotionCoordinate());
            float DistanceB = FVector2D::Distance(SourceEmotion->GetEmotionCoordinate(), B.GetEmotionCoordinate());
            return DistanceA < DistanceB;
        });
    }
    
    return Result;
}

UEmotionDefinition* UEmotionLibrary::GetCombinedEmotion(const FGameplayTag& EmotionTag1, const FGameplayTag& EmotionTag2) const
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

TArray<UEmotionDefinition*> UEmotionLibrary::FindEmotionsInRadius(const FVector2D& VACoordinate, float Radius) const
{
    TArray<UEmotionDefinition*> Result;
    
    // Find all emotions within the specified radius in VA space
    for (UEmotionDefinition* EmotionData : Emotions)
    {
        if (EmotionData)
        {
            // Calculate distance in VA space
            float Distance = FVector2D::Distance(VACoordinate, EmotionData->GetEmotionCoordinate());
            
            // Add to result if within the specified radius
            if (Distance <= Radius)
            {
                Result.Add(EmotionData);
            }
        }
    }
    
    // Sort by distance (closest first)
    Result.Sort([VACoordinate](const UEmotionDefinition& A, const UEmotionDefinition& B)
    {
        float DistanceA = FVector2D::Distance(VACoordinate, A.GetEmotionCoordinate());
        float DistanceB = FVector2D::Distance(VACoordinate, B.GetEmotionCoordinate());
        return DistanceA < DistanceB;
    });
    
    return Result;
}
