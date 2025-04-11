#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "EmotionState.generated.h"

USTRUCT(BlueprintType)
struct FEmotionState
{
    GENERATED_BODY()

    // The gameplay tag representing the emotion (e.g., Emotion.Joy)
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Emotion", meta=(Categories="Emotion.Core"))
    FGameplayTag EmotionTag;

    // Intensity in the range [0.0, 1.0]
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Emotion")
    float Intensity;

    FEmotionState()
        : Intensity(0.f)
    {
    }

    FEmotionState(const FGameplayTag& InTag, float InIntensity)
        : EmotionTag(InTag)
        , Intensity(InIntensity)
    {
    }

    // Getters and setters
    UFUNCTION(BlueprintCallable, Category="Emotion")
    FGameplayTag GetEmotionTag() const { return EmotionTag; }

    UFUNCTION(BlueprintCallable, Category="Emotion")
    void SetEmotionTag(const FGameplayTag& InTag) { EmotionTag = InTag; }

    // Intensity management
    UFUNCTION(BlueprintCallable, Category="Emotion")
    float GetIntensity() const { return Intensity; }

    UFUNCTION(BlueprintCallable, Category="Emotion")
    void SetIntensity(float InIntensity) { Intensity = FMath::Clamp(InIntensity, 0.f, 1.f); }
};