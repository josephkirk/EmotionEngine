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
        return;
    }

    void UpdateCombinedEmotionTag(const FGameplayTag& InCoreEmotionTag)
    {
        return;
    }
};