#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "EmotionType.h"
#include "Emotion.generated.h"

struct FEmotion;

USTRUCT(BlueprintType)
struct EMOTIONENGINE_API FEmotionTriggerRange
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EmotionSystem", meta = (Categories = "Emotion"))
    FGameplayTag EmotionTagTriggered;
    
    // The start of the intensity range (0.0 - 100.0) for triggering the emotion.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EmotionSystem")
    float Start;
    
    // The end of the intensity range (0.0 - 100.0) for triggering the emotion.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EmotionSystem")
    float End;

    FORCEINLINE bool IsInRange(float Value) const
    {
        // Check if Value is within the [Start, End] range, inclusive.
        // Use small tolerance for float comparison if necessary, but direct comparison often sufficient for game logic thresholds.
        return Value >= Start && Value <= End;
    }

    FORCEINLINE FGameplayTag GetEmotionTagTriggered(float Value) const
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

    // The intensity threshold (0.0 - 100.0) the source emotion needs to reach to potentially trigger variation emotions from this link.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EmotionSystem")
    float Threshold;

    // Array of Variatian Emotion that triggered by this emotion link. The Range check inside FEmotionTriggerRange uses the Link's Threshold value.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EmotionSystem")
    TArray<FEmotionTriggerRange> VariationEmotionTags;

    // Gets the triggered variation tag based on the Link's Threshold value fitting within one of the VariationEmotionTags ranges.
    FORCEINLINE FGameplayTag GetEmotionTagTriggered() const
    {
        for (const FEmotionTriggerRange& TriggerRange : VariationEmotionTags)
        {
            // Check if the Link's Threshold falls within the range defined in VariationEmotionTags
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

    // Type of emotion
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EmotionSystem")
    EEmotionType::Type Type;

    // Current intensity of this emotion (0.0 to 100.0)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EmotionSystem")
    float Intensity;

    /* Valence Arousal Coordinate 
    * Vector 2D represent Valence as X Axis and Arousal as Y Axis
    * High Arousal, Positive Valence (Top-Right): Ecstasy (V: +0.9, A: 0.9), Excitement (V: +0.7, A: 0.8), Happy (V: +0.8, A: 0.7)
    * Low Arousal, Positive Valence (Bottom-Right): Content (V: +0.6, A: 0.3), Calm (V: +0.3, A: 0.1), Relaxed (V: +0.4, A: 0.2)
    * Low Arousal, Negative Valence (Bottom-Left): Sad (V: -0.6, A: 0.2), Bored (V: -0.3, A: 0.1), Depressed (V: -0.7, A: 0.1)
    * High Arousal, Negative Valence (Top-Left): Afraid (V: -0.8, A: 0.9), Angry (V: -0.7, A: 0.8), Stressed (V: -0.5, A: 0.7), Tense (V: -0.4, A: 0.8)
    * TODO: Adapt this coordinate to the rest of the system
    *       This can be good way to find adjacent Emotion by search nearest emotion in radius  
    */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EmotionSystem")
    FVector2D VACoordinate;

    // The opposite emotion tag (e.g., Joy vs Sadness), 
    // intensity add to current emotion will deduct the opposite emotion and viceversa
    // Opposite emotion can't be linked
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EmotionSystem", meta = (Categories = "Emotion"))
    FGameplayTag OppositeEmotionTag;

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
            // Check if current Intensity falls within the range
            if (RangeEmotion.IsInRange(Intensity))
            {
                AllTags.AddTag(RangeEmotion.EmotionTagTriggered);
            }
        }
        
        // Add all linked emotion tags triggered
        for (const FEmotionLink& Link : LinkEmotions)
        {
            // Check if current Intensity meets the link's threshold requirement
            if (Intensity >= Link.Threshold)
            {
                // Get the variation tag determined by the link's threshold fitting into a variation range
                FGameplayTag EmotionLinkTriggered = Link.GetEmotionTagTriggered();
                if (EmotionLinkTriggered.IsValid())
                {
                    AllTags.AddTag(EmotionLinkTriggered);
                }
            }
        }
        
        return AllTags;
    }
};
