#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "EmotionState.generated.h"

USTRUCT(BlueprintType)
struct FEmotion
{
    GENERATED_BODY()
public:
    // The gameplay tag that identifies this emotion
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EmotionSystem", meta = (Categories = "Emotion"))
    FGameplayTag Tag;

    // Current intensity of this emotion (typically 0.0 to 1.0)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EmotionSystem")
    float Intensity;

    // The opposite emotion tag (e.g., Joy vs Sadness)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EmotionSystem", meta = (Categories = "Emotion"))
    FGameplayTag OppositeEmotionTag;

    // Adjacent emotions on Plutchik's wheel
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EmotionSystem", meta = (Categories = "Emotion"))
    FGameplayTagContainer AdjacentEmotionTags;

    // Map of result of this emotion combined with another emotion
    // Key: Another emotion tag, Value: The resulting combined emotion tag
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EmotionSystem", meta = (Categories = "Emotion"))
    TMap<FGameplayTag, FGameplayTag> CombinedEmotionTag;
};

UCLASS(BlueprintType)
class EMOTIONENGINE_API UEmotionState : public UObject
{
    GENERATED_BODY()


public:
    // The gameplay tags representing all emotion in the state , include range and combined emotions
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="EmotionSystem")
    FGameplayTagContainer EmotionTags;

    // Get an emotion tag intensity
    UFUNCTION(BlueprintCallable, Category="EmotionSystem", meta=(Categories="Emotion.Core"))
    float GetIntensity(const FGameplayTag& InTag) const;

    // add Core emotion tag start with "Emotion.Core" only, expose to Blueprint Callable
    // Intensity range is -1.0 to 1.0, with negative values representing opposite emotions
    UFUNCTION(BlueprintCallable, Category="EmotionSystem", meta=(Categories="Emotion.Core"))
    void AddCoreEmotionTag(const FGameplayTag& InTag, float InIntensity);

    // remove Core emotion tag start with "Emotion.Core" only , expose to Blueprint Callable
    UFUNCTION(BlueprintCallable, Category="EmotionSystem", meta=(Categories="Emotion.Core"))
    void RemoveCoreEmotionTag(const FGameplayTag& InTag);

    // Set intensity for a emotiontag. For core emotions, intensity range is -1.0 to 1.0
    UFUNCTION(BlueprintCallable, Category="EmotionSystem", meta=(Categories="Emotion.Core"))
    void SetIntensity(const FGameplayTag& InTag, float InIntensity);

private:
    UPROPERTY()
    FGameplayTagContainer CoreEmotionTags;

    UPROPERTY()
    TMap<FGameplayTag, float> IntensityMap;
    
    // Separate map to store core emotion intensities that can be -1 to 1
    UPROPERTY()
    TMap<FGameplayTag, float> CoreEmotionIntensities;
    
    // add/remove range emotion tag to add to EmotionTags on a core emotion tags intensity change
    // Uses sign of intensity (-/+) to determine which range tag to add (high/low)
    void UpdateRangeEmotionTag(const FGameplayTag& InCoreEmotionTag, float InCoreEmotionIntensity);

    void UpdateCombinedEmotionTag(const FGameplayTag& InCoreEmotionTag);
};