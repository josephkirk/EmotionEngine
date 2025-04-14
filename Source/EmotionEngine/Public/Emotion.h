#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Emotion.generated.h"

struct FEmotion;

USTRUCT(BlueprintType)
struct EMOTIONENGINE_API FEmotionTriggerRange
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EmotionSystem", meta = (Categories = "Emotion"))
    FGameplayTag EmotionTagTriggered;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EmotionSystem")
    uint8 Start;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EmotionSystem")
    uint8 End;

    FORCEINLINE bool IsInRange(int Value) const
    {
        return Value >= Start && Value <= End;
    }

    FORCEINLINE FGameplayTag GetEmotionTagTriggered(int Value) const
    {
        return IsInRange(Value) ? EmotionTagTriggered : FGameplayTag();
    }
};

//TODO: Maybe this should be more generic
USTRUCT(BlueprintType)
struct EMOTIONENGINE_API FEmotionLink
{
GENERATED_BODY()
public:

    // The emotion tag that this link is associated with
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EmotionSystem", meta = (Categories = "Emotion"))
    FGameplayTag LinkEmotion;

    // The threshold for this emotion Link
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EmotionSystem")
    uint8 Threshold;

    // Array of Variatian Emotion that triggered by this emotion link
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EmotionSystem")
    TArray<FEmotionTriggerRange> VariationEmotionTags;

    FORCEINLINE FGameplayTag GetEmotionTagTriggered() const
    {
        for (const FEmotionTriggerRange& TriggerRange : VariationEmotionTags)
        {
            if (TriggerRange.IsInRange(Threshold))
            {
                return TriggerRange.EmotionTagTriggered;
            }
        }
        return FGameplayTag();
    }
};

//TODO: Need to rework Component Implementation
USTRUCT(BlueprintType)
struct EMOTIONENGINE_API FEmotion
{
    GENERATED_BODY()
public:
    // The gameplay tag that identifies this emotion
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EmotionSystem", meta = (Categories = "Emotion"))
    FGameplayTag Tag;

    // Current intensity of this emotion (typically 0.0 to 1.0)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EmotionSystem")
    uint8 Intensity;

    /* Valence Arousal Coordinate 
    * Vector 2D represent Valence as X Axis and Arousal as Y Axis
    * High Arousal, Positive Valence (Top-Right): Ecstasy (V: +0.9, A: 0.9), Excitement (V: +0.7, A: 0.8), Happy (V: +0.8, A: 0.7)
    * Low Arousal, Positive Valence (Bottom-Right): Content (V: +0.6, A: 0.3), Calm (V: +0.3, A: 0.1), Relaxed (V: +0.4, A: 0.2)
    * Low Arousal, Negative Valence (Bottom-Left): Sad (V: -0.6, A: 0.2), Bored (V: -0.3, A: 0.1), Depressed (V: -0.7, A: 0.1)
    * High Arousal, Negative Valence (Top-Left): Afraid (V: -0.8, A: 0.9), Angry (V: -0.7, A: 0.8), Stressed (V: -0.5, A: 0.7), Tense (V: -0.4, A: 0.8)
    * TODO: Adapt this coordinate to the rest of the system
    */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EmotionSystem")
    FVector2D VACoordinate;

    // The opposite emotion tag (e.g., Joy vs Sadness), 
    // intensity add to current emotion will deduct the opposite emotion and viceversa
    // Opposite emotion can't be linked
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EmotionSystem", meta = (Categories = "Emotion"))
    FGameplayTag OppositeEmotionTag;

    // // Adjacent emotions on Plutchik's wheel
    // UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EmotionSystem", meta = (Categories = "Emotion"))
    // FGameplayTagContainer AdjacentEmotionTags;

    // Map of result of this emotion combined with another emotion
    // Key: A Core emotion tag, Value: The resulting combined emotion
    //UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EmotionSystem", meta = (Categories = "Emotion"))
    //TMap<FGameplayTag, FGameplayTag> CombinedEmotions;

    // Map of result of intensity elevate this emotion to another emotion
    // Key: value from 0 to 1, Value: The resulting Range emotion tag
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EmotionSystem", meta = (Categories = "Emotion.Range"))
    TArray<FEmotionTriggerRange> RangeEmotionTags;

    // Map of result of intensity change this emotion to more nuance emotion base on how it lean toward adjacent emotions
    // Key: value from 0 to 1, Value: The resulting variation emotion tag
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EmotionSystem", meta = (Categories = "Emotion.Variation"))
    TArray<FEmotionLink> LinkEmotions;


    FORCEINLINE FGameplayTagContainer GetAllEmotionTags() const
    {
        FGameplayTagContainer AllTags;
        
        // Add the main emotion tag
        if (Tag.IsValid())
        {
            AllTags.AddTag(Tag);
        }
        
        // Add all range emotion tags triggered
        for (const FEmotionTriggerRange& RangeEmotion : RangeEmotionTags)
        {
            if (RangeEmotion.IsInRange(Intensity))
            {
                AllTags.AddTag(RangeEmotion.EmotionTagTriggered);
            }
        }
        
        // Add all linked emotion tags triggered
        for (const FEmotionLink& Link : LinkEmotions)
        {
            
            // Add variation emotion tags from links
            FGameplayTag EmotionLinkTriggered = Link.GetEmotionTagTriggered();
            if (EmotionLinkTriggered.IsValid())
            {
                AllTags.AddTag(EmotionLinkTriggered);
            }
        }
        
        return AllTags;
    }
};
