#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "EmotionState.generated.h"

USTRUCT(BlueprintType)
struct FEmotionState
{
    GENERATED_BODY()


public:
    // The gameplay tags representing all emotion in the state , include range and combined emotions
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="EmotionSystem")
    FGameplayTagContainer EmotionTags;

    FEmotionState()
        : Intensity(0.f)
    {
    }

    FEmotionState(const FGameplayTag& InTag, float InIntensity)
        : EmotionTag(InTag)
        , Intensity(InIntensity)
    {
    }

    // Get an emotion tag intensity
    UFUNCTION(BlueprintCallable, Category="EmotionSystem", meta=(Categories="Emotion.Core"))
    float GetIntensity(const FGameplayTag& InTag) const
    {
        return IntensityMap.Contains(InTag) ? IntensityMap[InTag] : 0.f;
    }

    // add Core emotion tag start with "Emotion.Core" only , expose to Blueprint Callable
    UFUNCTION(BlueprintCallable, Category="EmotionSystem", meta=(Categories="Emotion.Core"))
    void AddCoreEmotionTag(const FGameplayTag& InTag, float InIntensity)
    {
        if (!InTag.MatchTags("Emotion.Core")) {
            return;
        }
        CoreEmotionTags.AddTag(InTag);
        IntensityMap.Add(InTag, InIntensity);
        UpdateCombinedEmotionTag(InTag);
    }

    // remove Core emotion tag start with "Emotion.Core" only , expose to Blueprint Callable
    UFUNCTION(BlueprintCallable, Category="EmotionSystem", meta=(Categories="Emotion.Core"))
    void RemoveCoreEmotionTag(const FGameplayTag& InTag)
    {
        if (!InTag.MatchTags("Emotion.Core")) {
            return;
        }
        CoreEmotionTags.RemoveTag(InTag);
        IntensityMap.Remove(InTag);
        UpdateCombinedEmotionTag(InTag);
    }

    // Set intensity for a emotiontag
    UFUNCTION(BlueprintCallable, Category="EmotionSystem", meta=(Categories="Emotion.Core"))
    void SetIntensity(const FGameplayTag& InTag, float InIntensity)
    {
        if (!InTag.MatchTags("Emotion.Core") && CoreEmotionTags.HasTag(InTag)) {
            return;
        }
        IntensityMap.Emplace(InTag, InIntensity);
        UpdateRangeEmotionTag(InTag, InIntensity);
    }

private:
    UPROPERTY()
    FGameplayTagContainer CoreEmotionTags;

    UPROPERTY()
    TMap<FGameplayTag, float> IntensityMap;
    
    // add/remove range emotion tag to add to EmotionTags on a core emotion tags intensity change
    void UpdateRangeEmotionTag(const FGameplayTag& InCoreEmotionTag, float InCoreEmotionIntensity)
    {
        // Check if the tag is a core emotion tag
        if (!InCoreEmotionTag.MatchesTag(FGameplayTag::RequestGameplayTag("Emotion.Core")))
        {
            return;
        }

        // Define intensity thresholds for high and low emotions
        const float HighIntensityThreshold = 0.7f;
        const float LowIntensityThreshold = 0.3f;

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
        
        // Remove existing range tags for this emotion
        EmotionTags.RemoveTag(HighRangeTag);
        EmotionTags.RemoveTag(LowRangeTag);
        
        // Add the appropriate range tag based on intensity
        if (InCoreEmotionIntensity >= HighIntensityThreshold)
        {
            EmotionTags.AddTag(HighRangeTag);
        }
        else if (InCoreEmotionIntensity <= LowIntensityThreshold && InCoreEmotionIntensity > 0.0f)
        {
            EmotionTags.AddTag(LowRangeTag);
        }
        // If intensity is between low and high thresholds, no range tag is added
    }

    void UpdateCombinedEmotionTag(const FGameplayTag& InCoreEmotionTag)
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
        EmotionTags.RemoveTags(FGameplayTagContainer(FGameplayTag::RequestGameplayTag("Emotion.Combined")));
        
        // Now check for each combination
        if (CoreEmotionTags.HasTag(FGameplayTag::RequestGameplayTag("Emotion.Core.Joy")) &&
            CoreEmotionTags.HasTag(FGameplayTag::RequestGameplayTag("Emotion.Core.Trust")))
        {
            EmotionTags.AddTag(FGameplayTag::RequestGameplayTag("Emotion.Combined.Love"));
        }
        
        if (CoreEmotionTags.HasTag(FGameplayTag::RequestGameplayTag("Emotion.Core.Trust")) &&
            CoreEmotionTags.HasTag(FGameplayTag::RequestGameplayTag("Emotion.Core.Fear")))
        {
            EmotionTags.AddTag(FGameplayTag::RequestGameplayTag("Emotion.Combined.Submission"));
        }
        
        if (CoreEmotionTags.HasTag(FGameplayTag::RequestGameplayTag("Emotion.Core.Fear")) &&
            CoreEmotionTags.HasTag(FGameplayTag::RequestGameplayTag("Emotion.Core.Surprise")))
        {
            EmotionTags.AddTag(FGameplayTag::RequestGameplayTag("Emotion.Combined.Awe"));
        }
        
        if (CoreEmotionTags.HasTag(FGameplayTag::RequestGameplayTag("Emotion.Core.Surprise")) &&
            CoreEmotionTags.HasTag(FGameplayTag::RequestGameplayTag("Emotion.Core.Sadness")))
        {
            EmotionTags.AddTag(FGameplayTag::RequestGameplayTag("Emotion.Combined.Disapproval"));
        }
        
        if (CoreEmotionTags.HasTag(FGameplayTag::RequestGameplayTag("Emotion.Core.Sadness")) &&
            CoreEmotionTags.HasTag(FGameplayTag::RequestGameplayTag("Emotion.Core.Disgust")))
        {
            EmotionTags.AddTag(FGameplayTag::RequestGameplayTag("Emotion.Combined.Remorse"));
        }
        
        if (CoreEmotionTags.HasTag(FGameplayTag::RequestGameplayTag("Emotion.Core.Disgust")) &&
            CoreEmotionTags.HasTag(FGameplayTag::RequestGameplayTag("Emotion.Core.Anger")))
        {
            EmotionTags.AddTag(FGameplayTag::RequestGameplayTag("Emotion.Combined.Contempt"));
        }
        
        if (CoreEmotionTags.HasTag(FGameplayTag::RequestGameplayTag("Emotion.Core.Anger")) &&
            CoreEmotionTags.HasTag(FGameplayTag::RequestGameplayTag("Emotion.Core.Anticipation")))
        {
            EmotionTags.AddTag(FGameplayTag::RequestGameplayTag("Emotion.Combined.Aggressiveness"));
        }
        
        if (CoreEmotionTags.HasTag(FGameplayTag::RequestGameplayTag("Emotion.Core.Anticipation")) &&
            CoreEmotionTags.HasTag(FGameplayTag::RequestGameplayTag("Emotion.Core.Joy")))
        {
            EmotionTags.AddTag(FGameplayTag::RequestGameplayTag("Emotion.Combined.Optimism"));
        }
    }
};