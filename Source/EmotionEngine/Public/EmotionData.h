#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "EmotionState.h"
#include "EmotionData.generated.h"

/**
 * Data asset containing information about a single emotion
 */
UCLASS(BlueprintType)
class EMOTIONENGINE_API UEmotionData : public UDataAsset
{
    GENERATED_BODY()

public:
    // The emotion this data asset represents
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EmotionSystem")
    FEmotion Emotion;
    
    // Display name for this emotion
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EmotionSystem")
    FText DisplayName;
    
    // Description of this emotion
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EmotionSystem", meta = (MultiLine = true))
    FText Description;
    
    // Color associated with this emotion for UI purposes
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EmotionSystem")
    FLinearColor Color;
    
    // Optional icon for this emotion
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EmotionSystem")
    UTexture2D* Icon;
};

/**
 * Data asset containing a collection of emotions and their relationships
 */
UCLASS(BlueprintType)
class EMOTIONENGINE_API UEmotionLibrary : public UDataAsset
{
    GENERATED_BODY()

public:
    // All emotions in this library
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EmotionSystem")
    TArray<UEmotionData*> Emotions;
    
    // Core emotions (the primary emotions in Plutchik's wheel)
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EmotionSystem")
    TArray<UEmotionData*> CoreEmotions;
    
    // Get an emotion data by its tag
    UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
    UEmotionData* GetEmotionByTag(const FGameplayTag& EmotionTag) const;
    
    // Get all emotions that are opposites of the given emotion
    UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
    TArray<UEmotionData*> GetOppositeEmotions(const FGameplayTag& EmotionTag) const;
    
    // DEPRECATED Get all emotions that are adjacent to the given emotion
    UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
    TArray<UEmotionData*> GetAdjacentEmotions(const FGameplayTag& EmotionTag) const;
    
    // Get the result of combining two emotions
    UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
    UEmotionData* GetCombinedEmotion(const FGameplayTag& EmotionTag1, const FGameplayTag& EmotionTag2) const;
};
