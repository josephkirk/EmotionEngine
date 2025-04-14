#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "Emotion.h"
#include "EmotionData.generated.h"

class UEmotionData;
class UEmotionLibrary;


USTRUCT(BlueprintType)
struct EMOTIONENGINE_API FCombineEmotionMapping
{
    GENERATED_USTRUCT_BODY()
public:
    PROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EmotionSystem", meta = (Categories = "Emotion"))
    FGameplayTagContainer TriggedEmotions;

    // Emotion Result from the combination, we only accept Combined Emotion Type here.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EmotionSystem", meta = (Categories = "Emotion"))
    UEmotionData* ResultEmotion;
}

/** 
 * Emotion Tendency is mapping of cofficiencies to input emotions intensity
 * This is used mainly to expess how personality affect certain emotions more than the others
 */
USTRUCT(BlueprintType)
class EMOTIONENGINE_API UEmotionalTendency : public UDataAsset
{
    GENERATE_BODY()
public:
    // Emotion tag map to a float value ( default 1.0) 
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EmotionSystem", meta = (Categories = "Emotion"))
    TMap<FGameplayTag, float> EmotionTendencies;

    // Display name for this emotion tendencies
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EmotionSystem")
    FText DisplayName;
    
    // Description of this emotion tendencies
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EmotionSystem", meta = (MultiLine = true))
    FText Description;
}

/** 
 * Combine Emotion Mapping is mapping of how 2 or more emotion combination create a new emotion
 */
USTRUCT(BlueprintType)
class EMOTIONENGINE_API UCombinedEmotionMapping : public UDataAsset
{
    GENERATE_BODY()
public:
    // Emotion tag map to a float value ( default 1.0) 
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EmotionSystem", meta = (Categories = "Emotion"))
    TArray<FCombineEmotionMapping> CombinedEmotions;
}

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
    
    // Core emotions (the primary emotions in Plutchik's wheel), only accept Core Emotion Type
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EmotionSystem")
    TArray<UEmotionData*> CoreEmotions;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EmotionSystem")
    TArray<UCombinedEmotionMapping*> CombineEmotions;
    
    // Emotional Tendencies (or coefficient) affect input intensity of emotions in this library
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EmotionSystem")
    EmotionalTendency* EmotionalTendency;

    // Get an emotion data by its tag
    UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
    UEmotionData* GetEmotionByTag(const FGameplayTag& EmotionTag) const;
    
    // Get all emotions that are opposites of the given emotion
    UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
    TArray<UEmotionData*> GetOppositeEmotions(const FGameplayTag& EmotionTag) const;
    
    // Get all emotions that are adjacent to the given emotion ( closest in VACoordinate)
    UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
    TArray<UEmotionData*> GetAdjacentEmotions(const FGameplayTag& EmotionTag) const;
    
    // Get the result of combining two emotions
    UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
    UEmotionData* GetCombinedEmotion(const FGameplayTag& EmotionTag1, const FGameplayTag& EmotionTag2) const;
};
