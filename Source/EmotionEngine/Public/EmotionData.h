#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "Emotion.h"
#include "Interfaces/Interface_AssetUserData.h"
#include "UObject/Object.h"
#include "EditorFramework/AssetImportData.h"
#include "EmotionData.generated.h"

class UEmotionDefinition;
class UEmotionLibrary;

/**
 * Struct for mapping emotion combinations to result emotions
 */
USTRUCT(BlueprintType)
struct EMOTIONENGINE_API FCombineEmotionMapping
{
    GENERATED_USTRUCT_BODY()
public:
    // The emotions that trigger this combination when present together
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EmotionSystem", meta = (Categories = "Emotion"))
    FGameplayTagContainer TriggerEmotions;

    // Emotion Result from the combination, we only accept Combined Emotion Type here.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EmotionSystem", meta = (Categories = "Emotion"))
    TObjectPtr<UEmotionDefinition> ResultEmotion;
};

/** 
 * Emotion Tendency is mapping of coefficients to input emotions intensity
 * This is used mainly to express how personality affects certain emotions more than others
 */
UCLASS(BlueprintType)
class EMOTIONENGINE_API UEmotionalTendency : public UDataAsset
{
    GENERATED_BODY()
public:
    // Emotion tag map to a float value (default 1.0) 
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EmotionSystem", meta = (Categories = "Emotion"))
    TMap<FGameplayTag, float> EmotionTendencies;

    // Display name for this emotion tendencies
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EmotionSystem")
    FText DisplayName;
    
    // Description of this emotion tendencies
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EmotionSystem", meta = (MultiLine = true))
    FText Description;
};

/** 
 * Combine Emotion Mapping is mapping of how 2 or more emotion combinations create a new emotion
 */
UCLASS(BlueprintType)
class EMOTIONENGINE_API UCombinedEmotionMapping : public UDataAsset
{
    GENERATED_BODY()
public:
    // Array of emotion combinations and their results
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EmotionSystem", meta = (Categories = "Emotion"))
    TArray<FCombineEmotionMapping> CombinedEmotions;
};

/**
 * Data asset containing information about a single emotion
 */
UCLASS(BlueprintType)
class EMOTIONENGINE_API UEmotionDefinition : public UDataAsset
{
    GENERATED_BODY()

public:
    UEmotionDefinition();
        
    // The emotion this data asset represents
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EmotionSystem")
    FEmotion Emotion;
    
#if WITH_EDITORONLY_DATA
    /** Importing data and options used for this emotion */
    UPROPERTY(Category = ImportSettings, VisibleAnywhere, Instanced)
    TObjectPtr<class UAssetImportData> AssetImportData;
#endif
#if WITH_EDITOR
    // ~ Override UObject Interface
    virtual void PostInitProperties() override;
    // ~ End Override UObject Interface
#endif

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
    TObjectPtr<UTexture2D> Icon;
    
    // Get all emotion tags associated with this emotion (main tag + triggered range and variation tags)
    UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
    FGameplayTagContainer GetAllEmotionTags() const;
    
    // Update emotion intensity and return any newly triggered emotion tags
    UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
    FGameplayTagContainer UpdateIntensity(float DeltaIntensity);
    
    // Get Emotion Coordinate
    UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
    FVector2D GetEmotionCoordinate() const;
    
    // Apply decay to emotion intensity based on time passed
    UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
    void ApplyDecay(float DeltaTime);
    
    // Check if this emotion is opposite to the given emotion tag
    UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
    bool IsOppositeEmotion(const FGameplayTag& EmotionTag) const;
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
    TArray<TObjectPtr<class UEmotionDefinition>> Emotions;
    
    // Core emotions (the primary emotions in Plutchik's wheel), only accept Core Emotion Type
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EmotionSystem")
    TArray<TObjectPtr<class UEmotionDefinition>> CoreEmotions;

    // Emotion combinations mappings
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EmotionSystem")
    TArray<TObjectPtr<class UCombinedEmotionMapping>> CombineEmotions;
    
    // Emotional Tendencies (or coefficient) affect input intensity of emotions in this library
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EmotionSystem")
    TObjectPtr<class UEmotionalTendency> EmotionalTendency;

    // Get an emotion data by its tag
    UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
    UEmotionDefinition* GetEmotionByTag(const FGameplayTag& EmotionTag) const;
    
    // Get all emotions that are opposites of the given emotion
    UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
    TArray<UEmotionDefinition*> GetOppositeEmotions(const FGameplayTag& EmotionTag) const;
    
    // Get all emotions that are adjacent to the given emotion (closest in VACoordinate)
    UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
    TArray<UEmotionDefinition*> GetAdjacentEmotions(const FGameplayTag& EmotionTag, float MaxDistance = 0.3f) const;
    
    // Get the result of combining two emotions
    UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
    UEmotionDefinition* GetCombinedEmotion(const FGameplayTag& EmotionTag1, const FGameplayTag& EmotionTag2) const;
    
    // Find emotions within a certain radius in the VA space
    UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
    TArray<UEmotionDefinition*> FindEmotionsInRadius(const FVector2D& VACoordinate, float Radius) const;
};
