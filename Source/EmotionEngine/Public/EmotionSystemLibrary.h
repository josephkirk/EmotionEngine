#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EmotionData.h"
#include "EmotionState.h"
#include "EmotionComponent.h"
#include "EmotionSystemLibrary.generated.h"

/**
 * Blueprint function library for working with the Emotion System
 */
UCLASS()
class EMOTIONENGINE_API UEmotionSystemLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    // Helper method to get library or default
    static UEmotionLibrary* GetLibraryOrDefault(UEmotionLibrary* ProvidedLibrary);

    // Get the default emotion library asset
    UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
    static UEmotionLibrary* GetDefaultEmotionLibrary();
    
    // Create a new emotion state
    UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
    static UEmotionState* CreateEmotionState(UEmotionLibrary* EmotionLibrary = nullptr);
    
    // Apply an emotion to an emotion state
    UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
    static void ApplyEmotion(UEmotionState* EmotionState, const FGameplayTag& EmotionTag, float Intensity);
    
    // Get the dominant emotion in an emotion state
    UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
    static void GetDominantEmotion(UEmotionState* EmotionState, FGameplayTag& OutEmotionTag, float& OutIntensity);
    
    // Get emotion data for a specific emotion tag
    UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
    static UEmotionData* GetEmotionData(const FGameplayTag& EmotionTag, UEmotionLibrary* EmotionLibrary = nullptr);
    
    // Check if two emotions are opposite
    UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
    static bool AreEmotionsOpposite(const FGameplayTag& EmotionTag1, const FGameplayTag& EmotionTag2, UEmotionLibrary* EmotionLibrary = nullptr);
    
    // Check if two emotions are adjacent
    UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
    static bool AreEmotionsAdjacent(const FGameplayTag& EmotionTag1, const FGameplayTag& EmotionTag2, float MaxDistance = 0.3f, UEmotionLibrary* EmotionLibrary = nullptr);
    
    // Get the combined emotion from two emotions
    UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
    static FGameplayTag GetCombinedEmotion(const FGameplayTag& EmotionTag1, const FGameplayTag& EmotionTag2, UEmotionLibrary* EmotionLibrary = nullptr);
    
    // Get the VA coordinate for an emotion
    UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
    static FVector2D GetEmotionVACoordinate(const FGameplayTag& EmotionTag, UEmotionLibrary* EmotionLibrary = nullptr);
    
    // Get emotions within a radius of a VA coordinate
    UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
    static TArray<UEmotionData*> GetEmotionsInRadius(const FVector2D& VACoordinate, float Radius, UEmotionLibrary* EmotionLibrary = nullptr);
    
    // Calculate the distance between two emotions in VA space
    UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
    static float GetEmotionDistance(const FGameplayTag& EmotionTag1, const FGameplayTag& EmotionTag2, UEmotionLibrary* EmotionLibrary = nullptr);
    
    // Apply an emotional stimulus to a component
    UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
    static void ApplyEmotionalStimulus(UEmotionComponent* EmotionComponent, const FGameplayTag& EmotionTag, float Intensity);
    
    // Get all active emotions from an emotion state
    UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
    static TArray<FActiveEmotion> GetActiveEmotions(UEmotionState* EmotionState);
    
    // Get the VA coordinate of an emotion state
    UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
    static FVector2D GetStateVACoordinate(UEmotionState* EmotionState);
    
    // Set the VA coordinate of an emotion state directly
    UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
    static void SetStateVACoordinate(UEmotionState* EmotionState, const FVector2D& NewVACoordinate);
    
    // Find the closest emotion to a VA coordinate
    UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
    static UEmotionData* FindClosestEmotion(const FVector2D& VACoordinate, UEmotionLibrary* EmotionLibrary = nullptr);
};
