#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EmotionData.h"
#include "EmotionState.h"
#include "EmotionSystemLibrary.generated.h"

/**
 * Blueprint function library for working with the Emotion System
 */
UCLASS()
class EMOTIONENGINE_API UEmotionSystemLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    // Get the default emotion library asset
    UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
    static UEmotionLibrary* GetDefaultEmotionLibrary();
    
    // Create a new emotion state
    UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
    static UEmotionState* CreateEmotionState();
    
    // Apply an emotion to an emotion state
    UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
    static void ApplyEmotion(UEmotionState* EmotionState, const FGameplayTag& EmotionTag, float Intensity);
    
    // Get the dominant emotion in an emotion state
    UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
    static FGameplayTag GetDominantEmotion(UEmotionState* EmotionState);
    
    // Get emotion data for a specific emotion tag
    UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
    static UEmotionData* GetEmotionData(const FGameplayTag& EmotionTag, UEmotionLibrary* EmotionLibrary = nullptr);
    
    // Check if two emotions are opposite
    UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
    static bool AreEmotionsOpposite(const FGameplayTag& EmotionTag1, const FGameplayTag& EmotionTag2, UEmotionLibrary* EmotionLibrary = nullptr);
    
    // Check if two emotions are adjacent
    UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
    static bool AreEmotionsAdjacent(const FGameplayTag& EmotionTag1, const FGameplayTag& EmotionTag2, UEmotionLibrary* EmotionLibrary = nullptr);
    
    // Get the combined emotion from two emotions
    UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
    static FGameplayTag GetCombinedEmotion(const FGameplayTag& EmotionTag1, const FGameplayTag& EmotionTag2, UEmotionLibrary* EmotionLibrary = nullptr);
};
