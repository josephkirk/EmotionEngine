#include "EmotionState.h"
#include "EmotionData.h" // Include for UEmotionLibrary and UEmotionDefinition
#include "GameplayTagsManager.h" // Include for tag manipulation
#include "Kismet/GameplayStatics.h" // For GetTimeSeconds

#include UE_INLINE_GENERATED_CPP_BY_NAME(EmotionState)

UEmotionState::UEmotionState()
    : VACoordinate(FVector2D::ZeroVector)
    , InfluenceRadius(0.3f)
{}

void UEmotionState::Initialize(UEmotionLibrary* InEmotionLibrary)
{
    EmotionLibraryInstance = InEmotionLibrary;
    EmotionTags.Reset();
    ActiveEmotions.Empty();
    VACoordinate = FVector2D::ZeroVector;
}

void UEmotionState::Tick(float DeltaTime)
{
    // Apply decay to all active emotions
    ApplyDecay(DeltaTime);
    
    // Update VA coordinate based on active emotions
    UpdateVACoordinate(DeltaTime);
    
    // Process any potential emotion combinations
    ProcessEmotionCombinations();
    
    // Update emotion tags based on active emotions
    UpdateEmotionTags();
}

float UEmotionState::GetIntensity(const FGameplayTag& InTag) const
{
    // Check if the tag is in active emotions
    if (ActiveEmotions.Contains(InTag))
    {
        return ActiveEmotions[InTag].Intensity;
    }
    
    return 0.0f;
}

void UEmotionState::AddEmotion(const FGameplayTag& InTag, float InIntensity)
{
    if (!EmotionLibraryInstance)
    {
        UE_LOG(LogTemp, Warning, TEXT("UEmotionState::AddEmotion - EmotionLibraryInstance is not set!"));
        return;
    }

    // Get the emotion data for this tag
    UEmotionDefinition* EmotionData = EmotionLibraryInstance->GetEmotionByTag(InTag);
    if (!EmotionData)
    {
        UE_LOG(LogTemp, Warning, TEXT("UEmotionState::AddEmotion - Could not find emotion data for tag %s"), *InTag.ToString());
        return;
    }

    // Clamp intensity between 0 and 100
    const float ClampedIntensity = FMath::Clamp(InIntensity, 0.0f, 100.0f);
    
    // Handle opposite emotions (adding to one reduces the other) : DISABLED
    // HandleOppositeEmotions(InTag, ClampedIntensity);
    
    // Check if emotion already exists
    if (ActiveEmotions.Contains(InTag))
    {
        // Add to existing emotion intensity
        FActiveEmotion& Emotion = ActiveEmotions[InTag];
        Emotion.Intensity = FMath::Clamp(Emotion.Intensity + ClampedIntensity, 0.0f, 100.0f);
        Emotion.LastUpdateTime = UGameplayStatics::GetTimeSeconds(this);
    }
    else
    {
        // Create new active emotion
        FActiveEmotion NewEmotion(EmotionData, ClampedIntensity, UGameplayStatics::GetTimeSeconds(this));
        ActiveEmotions.Add(InTag, NewEmotion);
    }
    
    // Update emotion tags
    UpdateEmotionTags();
}

void UEmotionState::RemoveEmotion(const FGameplayTag& InTag)
{
    if (ActiveEmotions.Contains(InTag))
    {
        ActiveEmotions.Remove(InTag);
        
        // Update emotion tags
        UpdateEmotionTags();
    }
}

void UEmotionState::SetIntensity(const FGameplayTag& InTag, float InIntensity)
{
    if (!EmotionLibraryInstance)
    {
        UE_LOG(LogTemp, Warning, TEXT("UEmotionState::SetIntensity - EmotionLibraryInstance is not set!"));
        return;
    }

    // Get the emotion data for this tag
    UEmotionDefinition* EmotionData = EmotionLibraryInstance->GetEmotionByTag(InTag);
    if (!EmotionData)
    {
        UE_LOG(LogTemp, Warning, TEXT("UEmotionState::SetIntensity - Could not find emotion data for tag %s"), *InTag.ToString());
        return;
    }

    // Clamp intensity between 0 and 100
    const float ClampedIntensity = FMath::Clamp(InIntensity, 0.0f, 100.0f);
    
    // Handle opposite emotions (setting one affects the other) : DISABLED 
    // HandleOppositeEmotions(InTag, ClampedIntensity);
    
    // Check if emotion already exists
    if (ActiveEmotions.Contains(InTag))
    {
        // Update existing emotion intensity
        FActiveEmotion& Emotion = ActiveEmotions[InTag];
        Emotion.Intensity = ClampedIntensity;
        Emotion.LastUpdateTime = UGameplayStatics::GetTimeSeconds(this);
    }
    else if (ClampedIntensity > 0.0f)
    {
        // Create new active emotion if intensity > 0
        FActiveEmotion NewEmotion(EmotionData, ClampedIntensity, UGameplayStatics::GetTimeSeconds(this));
        ActiveEmotions.Add(InTag, NewEmotion);
    }
    
    // Update emotion tags
    UpdateEmotionTags();
}

TArray<FActiveEmotion> UEmotionState::GetActiveEmotions() const
{
    TArray<FActiveEmotion> Result;
    ActiveEmotions.GenerateValueArray(Result);
    return Result;
}

void UEmotionState::GetDominantEmotion(FGameplayTag& OutEmotionTag, float& OutIntensity) const
{
    OutEmotionTag = FGameplayTag::EmptyTag;
    OutIntensity = 0.0f;
    
    // Find the emotion with the highest intensity
    for (const auto& Pair : ActiveEmotions)
    {
        if (Pair.Value.Intensity > OutIntensity)
        {
            OutEmotionTag = Pair.Key;
            OutIntensity = Pair.Value.Intensity;
        }
    }
}

TArray<UEmotionDefinition*> UEmotionState::FindEmotionsInRadius(float Radius) const
{
    if (!EmotionLibraryInstance)
    {
        return TArray<UEmotionDefinition*>();
    }
    
    return EmotionLibraryInstance->FindEmotionsInRadius(VACoordinate, Radius);
}

void UEmotionState::UpdateVACoordinate(float DeltaTime)
{
    if (ActiveEmotions.Num() == 0)
    {
        // If no active emotions, gradually return to neutral (0,0)
        if (!VACoordinate.IsNearlyZero())
        {
            // Simple linear interpolation toward zero
            VACoordinate = FMath::Vector2DInterpTo(VACoordinate, FVector2D::ZeroVector, DeltaTime, 0.5f);
        }
        return;
    }
    
    // Calculate the target VA coordinate based on active emotions
    FVector2D TargetVA = FVector2D::ZeroVector;
    float TotalIntensity = 0.0f;
    
    // Each emotion pulls the VA coordinate toward its own VA coordinate
    // with force proportional to its intensity
    for (const auto& Pair : ActiveEmotions)
    {
        if (Pair.Value.EmotionData)
        {
            const FVector2D& EmotionVA = Pair.Value.EmotionData->GetEmotionCoordinate();
            const float Intensity = Pair.Value.Intensity;
            
            // Add weighted contribution
            TargetVA += EmotionVA * Intensity;
            TotalIntensity += Intensity;
        }
    }
    
    // Normalize the target VA coordinate
    if (TotalIntensity > 0.0f)
    {
        TargetVA /= TotalIntensity;
        
        // Clamp to valid VA space (-1,1) for both axes
        TargetVA.X = FMath::Clamp(TargetVA.X, -1.0f, 1.0f);
        TargetVA.Y = FMath::Clamp(TargetVA.Y, -1.0f, 1.0f);
        
        // Apply spring model - smoothly interpolate toward target
        // The higher the total intensity, the faster the movement
        float InterpSpeed = FMath::Clamp(TotalIntensity / 100.0f, 0.1f, 1.0f) * 2.0f;
        VACoordinate = FMath::Vector2DInterpTo(VACoordinate, TargetVA, DeltaTime, InterpSpeed);
    }
}

void UEmotionState::ApplyDecay(float DeltaTime)
{
    // Get current time
    float CurrentTime = UGameplayStatics::GetTimeSeconds(this);
    
    // Create a list of emotions to remove (can't remove while iterating)
    TArray<FGameplayTag> EmotionsToRemove;
    
    // Apply decay to all active emotions
    for (auto& Pair : ActiveEmotions)
    {
        FActiveEmotion& Emotion = Pair.Value;
        if (Emotion.EmotionData)
        {
            // Calculate time since last update
            float TimeSinceUpdate = CurrentTime - Emotion.LastUpdateTime;
            
            // Apply decay based on the emotion's decay rate
            float DecayAmount = Emotion.EmotionData->Emotion.DecayRate * TimeSinceUpdate;
            Emotion.Intensity = FMath::Max(0.0f, Emotion.Intensity - DecayAmount);
            
            // Update the last update time
            Emotion.LastUpdateTime = CurrentTime;
            
            // If intensity has decayed to zero, mark for removal
            if (FMath::IsNearlyZero(Emotion.Intensity))
            {
                EmotionsToRemove.Add(Pair.Key);
            }
        }
    }
    
    // Remove emotions that have decayed to zero
    for (const FGameplayTag& TagToRemove : EmotionsToRemove)
    {
        ActiveEmotions.Remove(TagToRemove);
    }
}

void UEmotionState::UpdateEmotionTags()
{
    // Clear existing emotion tags
    EmotionTags.Reset();
    
    // Add tags for all active emotions
    for (const auto& Pair : ActiveEmotions)
    {
        if (Pair.Value.EmotionData)
        {
            // Add the main emotion tag
            EmotionTags.AddTag(Pair.Key);
            
            // Add all related tags (range and variation tags)
            FGameplayTagContainer RelatedTags = Pair.Value.EmotionData->GetAllEmotionTags();
            EmotionTags.AppendTags(RelatedTags);
        }
    }
}

void UEmotionState::HandleOppositeEmotions(const FGameplayTag& InTag, float InIntensity)
{
    if (!EmotionLibraryInstance)
    {
        return;
    }
    
    // Get the emotion data for this tag
    UEmotionDefinition* EmotionData = EmotionLibraryInstance->GetEmotionByTag(InTag);
    if (!EmotionData || !EmotionData->Emotion.OppositeEmotionTag.IsValid())
    {
        return;
    }
    
    // Get the opposite emotion tag
    FGameplayTag OppositeTag = EmotionData->Emotion.OppositeEmotionTag;
    
    // Check if the opposite emotion is active
    if (ActiveEmotions.Contains(OppositeTag))
    {
        FActiveEmotion& OppositeEmotion = ActiveEmotions[OppositeTag];
        
        // Reduce the opposite emotion's intensity
        // The reduction is proportional to the intensity being added
        float ReductionAmount = InIntensity * 0.5f; // Adjust this factor as needed
        OppositeEmotion.Intensity = FMath::Max(0.0f, OppositeEmotion.Intensity - ReductionAmount);
        OppositeEmotion.LastUpdateTime = UGameplayStatics::GetTimeSeconds(this);
        
        // If the opposite emotion's intensity is reduced to zero, remove it
        if (FMath::IsNearlyZero(OppositeEmotion.Intensity))
        {
            ActiveEmotions.Remove(OppositeTag);
        }
    }
}

void UEmotionState::ProcessEmotionCombinations()
{
    if (!EmotionLibraryInstance || !EmotionLibraryInstance->CombineEmotions.Num())
    {
        return;
    }
    
    // Get all active emotion tags
    FGameplayTagContainer ActiveTags;
    for (const auto& Pair : ActiveEmotions)
    {
        ActiveTags.AddTag(Pair.Key);
    }
    
    // Check each combination mapping
    for (UCombinedEmotionMapping* CombineMapping : EmotionLibraryInstance->CombineEmotions)
    {
        if (!CombineMapping)
        {
            continue;
        }
        
        for (const FCombineEmotionMapping& Mapping : CombineMapping->CombinedEmotions)
        {
            // Check if all trigger emotions are present
            bool bAllTriggersPresent = true;
            float MinIntensity = FLT_MAX;
            
            for (const FGameplayTag& TriggerTag : Mapping.TriggerEmotions)
            {
                if (!ActiveTags.HasTag(TriggerTag))
                {
                    bAllTriggersPresent = false;
                    break;
                }
                
                // Track the minimum intensity among trigger emotions
                float TagIntensity = GetIntensity(TriggerTag);
                MinIntensity = FMath::Min(MinIntensity, TagIntensity);
            }
            
            // If all triggers are present and we have a valid result emotion
            if (bAllTriggersPresent && Mapping.ResultEmotion)
            {
                // Add the combined emotion with intensity based on the minimum intensity of triggers
                FGameplayTag ResultTag = Mapping.ResultEmotion->Emotion.Tag;
                if (ResultTag.IsValid())
                {
                    // Only add if not already present with higher intensity
                    float CurrentIntensity = GetIntensity(ResultTag);
                    if (MinIntensity > CurrentIntensity)
                    {
                        // Create or update the combined emotion
                        FActiveEmotion CombinedEmotion(Mapping.ResultEmotion, MinIntensity, UGameplayStatics::GetTimeSeconds(this));
                        ActiveEmotions.Add(ResultTag, CombinedEmotion);
                    }
                }
            }
        }
    }
}