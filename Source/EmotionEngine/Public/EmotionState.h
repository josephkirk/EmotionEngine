#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "EmotionData.h"
#include "Emotion.h"
#include "EmotionState.generated.h"

// Forward declare UEmotionLibrary
class UEmotionLibrary;

UCLASS(BlueprintType)
class EMOTIONENGINE_API UEmotionState : public UObject
{
    GENERATED_BODY()

public:
    // Initialize the state with the Emotion Library
    UFUNCTION(BlueprintCallable, Category="EmotionSystem")
    void Initialize(UEmotionLibrary* InEmotionLibrary);

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
    TObjectPtr<UEmotionLibrary> EmotionLibraryInstance;

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

    // Add/remove linked emotion tags based on core emotion intensity and definitions in UEmotionData
    void UpdateLinkedEmotionTag(const FGameplayTag& InCoreEmotionTag, float InCoreEmotionIntensity);
};