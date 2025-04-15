#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "EmotionData.h"
#include "Emotion.h"
#include "EmotionState.generated.h"

// Forward declare UEmotionLibrary
class UEmotionLibrary;

/**
 * Struct to track an active emotion in the emotion state
 */
USTRUCT(BlueprintType)
struct EMOTIONENGINE_API FActiveEmotion
{
    GENERATED_USTRUCT_BODY()
public:
    // The emotion data asset
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="EmotionSystem")
    TObjectPtr<UEmotionDefinition> EmotionData;
    
    // Current intensity of this emotion (0.0 to 100.0)
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="EmotionSystem")
    float Intensity;
    
    // Time this emotion was last updated
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="EmotionSystem")
    float LastUpdateTime;
    
    FActiveEmotion() : EmotionData(nullptr), Intensity(0.0f), LastUpdateTime(0.0f) {}
    
    FActiveEmotion(UEmotionDefinition* InEmotionData, float InIntensity, float InTime)
        : EmotionData(InEmotionData), Intensity(InIntensity), LastUpdateTime(InTime) {}
};

/**
 * Manages the emotional state of an actor, including active emotions and VA coordinates
 */
UCLASS(BlueprintType)
class EMOTIONENGINE_API UEmotionState : public UObject
{
    GENERATED_BODY()

public:
    UEmotionState();
    
    // Called every frame to update emotion state
    UFUNCTION(BlueprintCallable, Category="EmotionSystem")
    void Tick(float DeltaTime);
    
    // Initialize the state with the Emotion Library
    UFUNCTION(BlueprintCallable, Category="EmotionSystem")
    void Initialize(UEmotionLibrary* InEmotionLibrary);

    // The gameplay tags representing all emotion in the state, include range and combined emotions
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="EmotionSystem")
    FGameplayTagContainer EmotionTags;
    
    // Current Valence-Arousal coordinate of the emotional state
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="EmotionSystem")
    FVector2D VACoordinate;
    
    // Radius of influence in the VA space
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="EmotionSystem", meta=(ClampMin="0.0"))
    float InfluenceRadius;

    // Get an emotion tag intensity
    UFUNCTION(BlueprintCallable, Category="EmotionSystem")
    float GetIntensity(const FGameplayTag& InTag) const;

    // Add emotion to the active emotions list
    UFUNCTION(BlueprintCallable, Category="EmotionSystem")
    void AddEmotion(const FGameplayTag& InTag, float InIntensity);

    // Remove emotion from the active emotions list
    UFUNCTION(BlueprintCallable, Category="EmotionSystem")
    void RemoveEmotion(const FGameplayTag& InTag);

    // Set intensity for an emotion
    UFUNCTION(BlueprintCallable, Category="EmotionSystem")
    void SetIntensity(const FGameplayTag& InTag, float InIntensity);
    
    // Get all active emotions
    UFUNCTION(BlueprintCallable, Category="EmotionSystem")
    TArray<FActiveEmotion> GetActiveEmotions() const;
    
    // Get the dominant emotion (highest intensity)
    UFUNCTION(BlueprintCallable, Category="EmotionSystem")
    void GetDominantEmotion(FGameplayTag& OutEmotionTag, float& OutIntensity) const;
    
    // Find emotions within a certain radius in the VA space
    UFUNCTION(BlueprintCallable, Category="EmotionSystem")
    TArray<UEmotionDefinition*> FindEmotionsInRadius(float Radius) const;

private:
    UPROPERTY()
    TObjectPtr<UEmotionLibrary> EmotionLibraryInstance;

    // Map of active emotions (tag -> active emotion struct)
    UPROPERTY()
    TMap<FGameplayTag, FActiveEmotion> ActiveEmotions;
    
    // Update the VA coordinate based on active emotions using spring model
    void UpdateVACoordinate(float DeltaTime);
    
    // Apply decay to all active emotions
    void ApplyDecay(float DeltaTime);
    
    // Update emotion tags based on active emotions
    void UpdateEmotionTags();
    
    // Handle opposite emotions (adding to one reduces the other)
    // Handle opposite emotions (adding to one reduces the other)
    // Currently disabled but kept for future use
    void HandleOppositeEmotions(const FGameplayTag& InTag, float InIntensity);
    
    // Check for and process emotion combinations
    void ProcessEmotionCombinations();
};