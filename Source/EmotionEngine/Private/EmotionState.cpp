#include "EmotionState.h"
#include "EmotionData.h" // Include for UEmotionLibrary and UEmotionData
#include "GameplayTagsManager.h" // Include for tag manipulation

#include UE_INLINE_GENERATED_CPP_BY_NAME(EmotionState)

void UEmotionState::Initialize(UEmotionLibrary* InEmotionLibrary)
{
    EmotionLibraryInstance = InEmotionLibrary;
}

float UEmotionState::GetIntensity(const FGameplayTag& InTag) const
{
    // If it's a core emotion tag, return from CoreEmotionIntensities
    if (InTag.MatchesTag(FGameplayTag::RequestGameplayTag("Emotion.Core")) && CoreEmotionIntensities.Contains(InTag))
    {
        return CoreEmotionIntensities[InTag];
    }
    
    // Otherwise return from IntensityMap (range and combined tags)
    return IntensityMap.Contains(InTag) ? IntensityMap[InTag] : 0.f;
}

void UEmotionState::AddCoreEmotionTag(const FGameplayTag& InTag, float InIntensity)
{
    if (!InTag.MatchesTag(FGameplayTag::RequestGameplayTag("Emotion.Core"))) {
        return;
    }
    if (!EmotionLibraryInstance)
    {
        UE_LOG(LogTemp, Warning, TEXT("UEmotionState::AddCoreEmotionTag - EmotionLibraryInstance is not set!"));
        return;
    }

    // Clamp intensity between -1 and 1
    const float ClampedIntensity = FMath::Clamp(InIntensity, -1.0f, 1.0f);
    
    CoreEmotionTags.AddTag(InTag);
    
    // Store intensity in a separate private map, not in IntensityMap
    CoreEmotionIntensities.Add(InTag, ClampedIntensity);
    
    // Update the range and linked emotion tags with the intensity value
    UpdateRangeEmotionTag(InTag, ClampedIntensity);
    UpdateLinkedEmotionTag(InTag, ClampedIntensity); // Changed from UpdateCombinedEmotionTag
}

void UEmotionState::RemoveCoreEmotionTag(const FGameplayTag& InTag)
{
    if (!InTag.MatchesTag(FGameplayTag::RequestGameplayTag("Emotion.Core"))) {
        return;
    }
    if (!EmotionLibraryInstance)
    {
        UE_LOG(LogTemp, Warning, TEXT("UEmotionState::RemoveCoreEmotionTag - EmotionLibraryInstance is not set!"));
        return;
    }

    CoreEmotionTags.RemoveTag(InTag);
    CoreEmotionIntensities.Remove(InTag);
    
    // Remove the corresponding range and linked tags
    UpdateRangeEmotionTag(InTag, 0.0f); // Passing 0 intensity will clear the tags
    UpdateLinkedEmotionTag(InTag, 0.0f); // Clear linked tags too
}

void UEmotionState::SetIntensity(const FGameplayTag& InTag, float InIntensity)
{
    // Only allow setting intensity for tags that exist in CoreEmotionTags
    if (!InTag.MatchesTag(FGameplayTag::RequestGameplayTag("Emotion.Core")) || !CoreEmotionTags.HasTag(InTag)) {
        return;
    }
    if (!EmotionLibraryInstance)
    {
        UE_LOG(LogTemp, Warning, TEXT("UEmotionState::SetIntensity - EmotionLibraryInstance is not set!"));
        return;
    }

    // Clamp intensity between -1 and 1 for core emotions
    const float ClampedIntensity = FMath::Clamp(InIntensity, -1.0f, 1.0f);
    
    // Store core emotion intensity in separate map
    CoreEmotionIntensities.Emplace(InTag, ClampedIntensity);
    
    UpdateRangeEmotionTag(InTag, ClampedIntensity);
    UpdateLinkedEmotionTag(InTag, ClampedIntensity); // Changed from UpdateCombinedEmotionTag
}

void UEmotionState::UpdateRangeEmotionTag(const FGameplayTag& InCoreEmotionTag, float InCoreEmotionIntensity)
{
    // Check if the tag is a core emotion tag
    if (!InCoreEmotionTag.MatchesTag(FGameplayTag::RequestGameplayTag("Emotion.Core")) || !EmotionLibraryInstance)
    {
        return;
    }

    UEmotionData* EmotionData = EmotionLibraryInstance->GetEmotionByTag(InCoreEmotionTag);
    if (!EmotionData)
    {
        return;
    }

    // First, remove all existing range tags derived *from this specific core emotion*
    for (const FEmotionTriggerRange& RangeInfo : EmotionData->Emotion.RangeEmotionTags)
    {
        if (RangeInfo.EmotionTagTriggered.IsValid())
        {
            EmotionTags.RemoveTag(RangeInfo.EmotionTagTriggered);
            IntensityMap.Remove(RangeInfo.EmotionTagTriggered);
        }
    }

    // Get the absolute intensity value
    const float AbsoluteIntensity = FMath::Abs(InCoreEmotionIntensity);

    // If intensity is effectively zero, we just cleared the tags, so we're done.
    if (FMath::IsNearlyZero(AbsoluteIntensity))
    {
        return;
    }

    // Find the matching range tag based on the current intensity
    for (const FEmotionTriggerRange& RangeInfo : EmotionData->Emotion.RangeEmotionTags)
    {
        // Use the signed intensity for range check, as ranges might be defined for negative values too
        if (RangeInfo.IsInRange(InCoreEmotionIntensity) && RangeInfo.EmotionTagTriggered.IsValid())
        {
            EmotionTags.AddTag(RangeInfo.EmotionTagTriggered);
            // Store the absolute intensity for the range tag
            IntensityMap.Emplace(RangeInfo.EmotionTagTriggered, AbsoluteIntensity);
            break; // Assume only one range tag can be active at a time for a given core emotion
        }
    }
}

void UEmotionState::UpdateLinkedEmotionTag(const FGameplayTag& InCoreEmotionTag, float InCoreEmotionIntensity)
{
    if (!InCoreEmotionTag.MatchesTag(FGameplayTag::RequestGameplayTag("Emotion.Core")) || !EmotionLibraryInstance)
    {
        return;
    }

    UEmotionData* EmotionData = EmotionLibraryInstance->GetEmotionByTag(InCoreEmotionTag);
    if (!EmotionData)
    {
        return;
    }

    // First, remove all existing linked/variation tags derived *from this specific core emotion's links*
    for (const FEmotionLink& LinkInfo : EmotionData->Emotion.LinkEmotions)
    {
        // Remove the direct link tag if it exists (though it seems unused in FEmotionLink's GetEmotionTagTriggered)
        if(LinkInfo.LinkEmotion.IsValid())
        {
            EmotionTags.RemoveTag(LinkInfo.LinkEmotion);
            IntensityMap.Remove(LinkInfo.LinkEmotion);
        }
        // Remove all potential variation tags defined within this link
        for (const FEmotionTriggerRange& VariationInfo : LinkInfo.VariationEmotionTags)
        {
            if (VariationInfo.EmotionTagTriggered.IsValid())
            {
                EmotionTags.RemoveTag(VariationInfo.EmotionTagTriggered);
                IntensityMap.Remove(VariationInfo.EmotionTagTriggered);
            }
        }
    }

    // If intensity is effectively zero, we just cleared the tags, so we're done.
    if (FMath::IsNearlyZero(InCoreEmotionIntensity))
    {
         return;
    }

    // Find any triggered linked/variation tags based on the current core intensity
    for (const FEmotionLink& LinkInfo : EmotionData->Emotion.LinkEmotions)
    {
        // NOTE: FEmotionLink::GetEmotionTagTriggered uses LinkInfo.Threshold internally for its checks.
        // This might need refinement if the core intensity should be used instead.
        // Following current FEmotionLink implementation:
        FGameplayTag TriggeredVariationTag = LinkInfo.GetEmotionTagTriggered(); 
        
        if (TriggeredVariationTag.IsValid())
        {
            // Check if the core emotion's intensity meets the link's threshold requirement
            // We assume positive intensity is required to activate a link threshold
            if(InCoreEmotionIntensity >= LinkInfo.Threshold)
            {
                EmotionTags.AddTag(TriggeredVariationTag);
                // Use the absolute core intensity for the derived variation tag intensity
                IntensityMap.Emplace(TriggeredVariationTag, FMath::Abs(InCoreEmotionIntensity));
                // Assuming only one Link/Variation can be triggered per core emotion for now
                break; 
            }
        }
    }
}