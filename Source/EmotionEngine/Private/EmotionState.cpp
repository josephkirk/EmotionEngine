#include "EmotionState.h"


#include UE_INLINE_GENERATED_CPP_BY_NAME(EmotionState)

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
    // Clamp intensity between -1 and 1
    const float ClampedIntensity = FMath::Clamp(InIntensity, -1.0f, 1.0f);
    
    CoreEmotionTags.AddTag(InTag);
    
    // Store intensity in a separate private map, not in IntensityMap
    CoreEmotionIntensities.Add(InTag, ClampedIntensity);
    
    // Update the range emotion tag with the intensity value
    UpdateRangeEmotionTag(InTag, ClampedIntensity);
    UpdateCombinedEmotionTag(InTag);
}

void UEmotionState::RemoveCoreEmotionTag(const FGameplayTag& InTag)
{
    if (!InTag.MatchesTag(FGameplayTag::RequestGameplayTag("Emotion.Core"))) {
        return;
    }
    CoreEmotionTags.RemoveTag(InTag);
    CoreEmotionIntensities.Remove(InTag);
    
    // Remove the corresponding range tags
    UpdateRangeEmotionTag(InTag, 0.0f); // Passing 0 intensity will clear the tags
    UpdateCombinedEmotionTag(InTag);
}

void UEmotionState::SetIntensity(const FGameplayTag& InTag, float InIntensity)
{
    // Only allow setting intensity for tags that exist in CoreEmotionTags
    if (!InTag.MatchesTag(FGameplayTag::RequestGameplayTag("Emotion.Core")) || !CoreEmotionTags.HasTag(InTag)) {
        return;
    }
    // Clamp intensity between -1 and 1 for core emotions
    const float ClampedIntensity = FMath::Clamp(InIntensity, -1.0f, 1.0f);
    
    // Store core emotion intensity in separate map
    CoreEmotionIntensities.Emplace(InTag, ClampedIntensity);
    
    UpdateRangeEmotionTag(InTag, ClampedIntensity);
    UpdateCombinedEmotionTag(InTag);
}

void UEmotionState::UpdateRangeEmotionTag(const FGameplayTag& InCoreEmotionTag, float InCoreEmotionIntensity)
{
    // Check if the tag is a core emotion tag
    if (!InCoreEmotionTag.MatchesTag(FGameplayTag::RequestGameplayTag("Emotion.Core")))
    {
        return;
    }

    // Get the absolute intensity value
    const float AbsoluteIntensity = FMath::Abs(InCoreEmotionIntensity);
    
    // Extract the specific emotion type from the core tag
    FString CoreTagString = InCoreEmotionTag.ToString();
    FString EmotionType;

    // Strip the "Emotion.Core." prefix to get the emotion type
    if (CoreTagString.StartsWith("Emotion.Core."))
    {
        EmotionType = CoreTagString.RightChop(13); // 13 is length of "Emotion.Core."
    }
    else
    {
        return; // Invalid tag format
    }

    // Construct the high and low intensity tag strings
    FString HighRangeTagString = FString::Printf(TEXT("Emotion.Range.High.%s"), *EmotionType);
    FString LowRangeTagString = FString::Printf(TEXT("Emotion.Range.Low.%s"), *EmotionType);
    
    // Map specific emotions to their high/low intensity variants
    if (EmotionType == "Joy")
    {
        HighRangeTagString = "Emotion.Range.High.Joy.Ecstasy";
        LowRangeTagString = "Emotion.Range.Low.Joy.Serenity";
    }
    else if (EmotionType == "Trust")
    {
        HighRangeTagString = "Emotion.Range.High.Trust.Admiration";
        LowRangeTagString = "Emotion.Range.Low.Trust.Acceptance";
    }
    else if (EmotionType == "Fear")
    {
        HighRangeTagString = "Emotion.Range.High.Fear.Terror";
        LowRangeTagString = "Emotion.Range.Low.Fear.Apprehension";
    }
    else if (EmotionType == "Surprise")
    {
        HighRangeTagString = "Emotion.Range.High.Surprise.Amazement";
        LowRangeTagString = "Emotion.Range.Low.Surprise.Distraction";
    }
    else if (EmotionType == "Sadness")
    {
        HighRangeTagString = "Emotion.Range.High.Sadness.Grief";
        LowRangeTagString = "Emotion.Range.Low.Sadness.Pensiveness";
    }
    else if (EmotionType == "Disgust")
    {
        HighRangeTagString = "Emotion.Range.High.Disgust.Loathing";
        LowRangeTagString = "Emotion.Range.Low.Disgust.Boredom";
    }
    else if (EmotionType == "Anger")
    {
        HighRangeTagString = "Emotion.Range.High.Anger.Rage";
        LowRangeTagString = "Emotion.Range.Low.Anger.Annoyance";
    }
    else if (EmotionType == "Anticipation")
    {
        HighRangeTagString = "Emotion.Range.High.Anticipation.Vigilance";
        LowRangeTagString = "Emotion.Range.Low.Anticipation.Interest";
    }
    
    // Get the tags
    FGameplayTag HighRangeTag = FGameplayTag::RequestGameplayTag(FName(*HighRangeTagString));
    FGameplayTag LowRangeTag = FGameplayTag::RequestGameplayTag(FName(*LowRangeTagString));
    
    // Remove existing range tags for this emotion from EmotionTags
    EmotionTags.RemoveTag(HighRangeTag);
    EmotionTags.RemoveTag(LowRangeTag);
    
    // Clear the intensity map entries for these tags
    IntensityMap.Remove(HighRangeTag);
    IntensityMap.Remove(LowRangeTag);
    
    // Only add range tags if the intensity is non-zero
    if (AbsoluteIntensity > 0.0f)
    {
        // Determine which range tag to add based on sign of the intensity (positive/negative)
        if (InCoreEmotionIntensity > 0.0f)
        {
            // Positive intensity = high range tag
            EmotionTags.AddTag(HighRangeTag);
            IntensityMap.Emplace(HighRangeTag, AbsoluteIntensity);
        }
        else // Intensity < 0.0f
        {
            // Negative intensity = low range tag
            EmotionTags.AddTag(LowRangeTag);
            IntensityMap.Emplace(LowRangeTag, AbsoluteIntensity);
        }
    }
    
    // Core emotion tag itself is not added to EmotionTags, only stored in CoreEmotionTags
}

void UEmotionState::UpdateCombinedEmotionTag(const FGameplayTag& InCoreEmotionTag)
{
    // Combined emotions according to Plutchik's wheel:
    // Love = Joy + Trust
    // Submission = Trust + Fear
    // Awe = Fear + Surprise
    // Disapproval = Surprise + Sadness
    // Remorse = Sadness + Disgust
    // Contempt = Disgust + Anger
    // Aggressiveness = Anger + Anticipation
    // Optimism = Anticipation + Joy
    
    // First, remove all combined emotion tags to recalculate
    // Also remove them from the IntensityMap
    FGameplayTagContainer CombinedTags = FGameplayTagContainer(FGameplayTag::RequestGameplayTag("Emotion.Combined"));
    for (const FGameplayTag& Tag : CombinedTags)
    {
        IntensityMap.Remove(Tag);
    }
    EmotionTags.RemoveTags(CombinedTags);
    
    // Define all core emotion tags
    FGameplayTag JoyTag = FGameplayTag::RequestGameplayTag("Emotion.Core.Joy");
    FGameplayTag TrustTag = FGameplayTag::RequestGameplayTag("Emotion.Core.Trust");
    FGameplayTag FearTag = FGameplayTag::RequestGameplayTag("Emotion.Core.Fear");
    FGameplayTag SurpriseTag = FGameplayTag::RequestGameplayTag("Emotion.Core.Surprise");
    FGameplayTag SadnessTag = FGameplayTag::RequestGameplayTag("Emotion.Core.Sadness");
    FGameplayTag DisgustTag = FGameplayTag::RequestGameplayTag("Emotion.Core.Disgust");
    FGameplayTag AngerTag = FGameplayTag::RequestGameplayTag("Emotion.Core.Anger");
    FGameplayTag AnticipationTag = FGameplayTag::RequestGameplayTag("Emotion.Core.Anticipation");
    
    // Helper function to calculate combined intensity
    auto CalculateCombinedIntensity = [this](const FGameplayTag& Tag1, const FGameplayTag& Tag2) -> float {
        float Intensity1 = CoreEmotionIntensities.Contains(Tag1) ? CoreEmotionIntensities[Tag1] : 0.0f;
        float Intensity2 = CoreEmotionIntensities.Contains(Tag2) ? CoreEmotionIntensities[Tag2] : 0.0f;
        return FMath::Abs((Intensity1 + Intensity2) / 2.0f); // Average of the two intensities
    };
    
    // Check for each combination with positive values in both emotions
    if (CoreEmotionIntensities.Contains(JoyTag) && CoreEmotionIntensities.Contains(TrustTag) && 
        FMath::Abs(CoreEmotionIntensities[JoyTag]) > 0.0f && FMath::Abs(CoreEmotionIntensities[TrustTag]) > 0.0f)
    {
        float CombinedIntensity = CalculateCombinedIntensity(JoyTag, TrustTag);
        if (CombinedIntensity > 0.0f)
        {
            FGameplayTag LoveTag = FGameplayTag::RequestGameplayTag("Emotion.Combined.Love");
            EmotionTags.AddTag(LoveTag);
            // Store combined intensity
            IntensityMap.Emplace(LoveTag, CombinedIntensity);
        }
    }
    
    if (CoreEmotionIntensities.Contains(TrustTag) && CoreEmotionIntensities.Contains(FearTag) && 
        FMath::Abs(CoreEmotionIntensities[TrustTag]) > 0.0f && FMath::Abs(CoreEmotionIntensities[FearTag]) > 0.0f)
    {
        float CombinedIntensity = CalculateCombinedIntensity(TrustTag, FearTag);
        if (CombinedIntensity > 0.0f)
        {
            FGameplayTag SubmissionTag = FGameplayTag::RequestGameplayTag("Emotion.Combined.Submission");
            EmotionTags.AddTag(SubmissionTag);
            IntensityMap.Emplace(SubmissionTag, CombinedIntensity);
        }
    }
    
    if (CoreEmotionIntensities.Contains(FearTag) && CoreEmotionIntensities.Contains(SurpriseTag) && 
        FMath::Abs(CoreEmotionIntensities[FearTag]) > 0.0f && FMath::Abs(CoreEmotionIntensities[SurpriseTag]) > 0.0f)
    {
        float CombinedIntensity = CalculateCombinedIntensity(FearTag, SurpriseTag);
        if (CombinedIntensity > 0.0f)
        {
            FGameplayTag AweTag = FGameplayTag::RequestGameplayTag("Emotion.Combined.Awe");
            EmotionTags.AddTag(AweTag);
            IntensityMap.Emplace(AweTag, CombinedIntensity);
        }
    }
    
    if (CoreEmotionIntensities.Contains(SurpriseTag) && CoreEmotionIntensities.Contains(SadnessTag) && 
        FMath::Abs(CoreEmotionIntensities[SurpriseTag]) > 0.0f && FMath::Abs(CoreEmotionIntensities[SadnessTag]) > 0.0f)
    {
        float CombinedIntensity = CalculateCombinedIntensity(SurpriseTag, SadnessTag);
        if (CombinedIntensity > 0.0f)
        {
            FGameplayTag DisapprovalTag = FGameplayTag::RequestGameplayTag("Emotion.Combined.Disapproval");
            EmotionTags.AddTag(DisapprovalTag);
            IntensityMap.Emplace(DisapprovalTag, CombinedIntensity);
        }
    }
    
    if (CoreEmotionIntensities.Contains(SadnessTag) && CoreEmotionIntensities.Contains(DisgustTag) && 
        FMath::Abs(CoreEmotionIntensities[SadnessTag]) > 0.0f && FMath::Abs(CoreEmotionIntensities[DisgustTag]) > 0.0f)
    {
        float CombinedIntensity = CalculateCombinedIntensity(SadnessTag, DisgustTag);
        if (CombinedIntensity > 0.0f)
        {
            FGameplayTag RemorseTag = FGameplayTag::RequestGameplayTag("Emotion.Combined.Remorse");
            EmotionTags.AddTag(RemorseTag);
            IntensityMap.Emplace(RemorseTag, CombinedIntensity);
        }
    }
    
    if (CoreEmotionIntensities.Contains(DisgustTag) && CoreEmotionIntensities.Contains(AngerTag) && 
        FMath::Abs(CoreEmotionIntensities[DisgustTag]) > 0.0f && FMath::Abs(CoreEmotionIntensities[AngerTag]) > 0.0f)
    {
        float CombinedIntensity = CalculateCombinedIntensity(DisgustTag, AngerTag);
        if (CombinedIntensity > 0.0f)
        {
            FGameplayTag ContemptTag = FGameplayTag::RequestGameplayTag("Emotion.Combined.Contempt");
            EmotionTags.AddTag(ContemptTag);
            IntensityMap.Emplace(ContemptTag, CombinedIntensity);
        }
    }
    
    if (CoreEmotionIntensities.Contains(AngerTag) && CoreEmotionIntensities.Contains(AnticipationTag) && 
        FMath::Abs(CoreEmotionIntensities[AngerTag]) > 0.0f && FMath::Abs(CoreEmotionIntensities[AnticipationTag]) > 0.0f)
    {
        float CombinedIntensity = CalculateCombinedIntensity(AngerTag, AnticipationTag);
        if (CombinedIntensity > 0.0f)
        {
            FGameplayTag AggressivenessTag = FGameplayTag::RequestGameplayTag("Emotion.Combined.Aggressiveness");
            EmotionTags.AddTag(AggressivenessTag);
            IntensityMap.Emplace(AggressivenessTag, CombinedIntensity);
        }
    }
    
    if (CoreEmotionIntensities.Contains(AnticipationTag) && CoreEmotionIntensities.Contains(JoyTag) && 
        FMath::Abs(CoreEmotionIntensities[AnticipationTag]) > 0.0f && FMath::Abs(CoreEmotionIntensities[JoyTag]) > 0.0f)
    {
        float CombinedIntensity = CalculateCombinedIntensity(AnticipationTag, JoyTag);
        if (CombinedIntensity > 0.0f)
        {
            FGameplayTag OptimismTag = FGameplayTag::RequestGameplayTag("Emotion.Combined.Optimism");
            EmotionTags.AddTag(OptimismTag);
            IntensityMap.Emplace(OptimismTag, CombinedIntensity);
        }
    }
}