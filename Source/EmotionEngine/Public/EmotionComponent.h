#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "EmotionState.h"
#include "EmotionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEmotionChanged, const FGameplayTag&, EmotionTag, float, Intensity);

/**
 * Component that manages an actor's emotional state using the EmotionEngine system
 */
UCLASS(ClassGroup=(EmotionEngine), meta=(BlueprintSpawnableComponent))
class EMOTIONENGINE_API UEmotionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEmotionComponent();

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called when the component is destroyed
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// Get the current emotion state
	UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
	const FEmotionState& GetEmotionState() const { return EmotionState; }

	// Add a core emotion tag with intensity
	UFUNCTION(BlueprintCallable, Category = "EmotionSystem", meta = (Categories = "Emotion.Core"))
	void AddCoreEmotion(const FGameplayTag& EmotionTag, float Intensity);

	// Remove a core emotion tag
	UFUNCTION(BlueprintCallable, Category = "EmotionSystem", meta = (Categories = "Emotion.Core"))
	void RemoveCoreEmotion(const FGameplayTag& EmotionTag);

	// Set intensity for a core emotion tag
	UFUNCTION(BlueprintCallable, Category = "EmotionSystem", meta = (Categories = "Emotion.Core"))
	void SetEmotionIntensity(const FGameplayTag& EmotionTag, float Intensity);

	// Get intensity for any emotion tag (core, range, or combined)
	UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
	float GetEmotionIntensity(const FGameplayTag& EmotionTag) const;

	// Check if the component has a specific emotion tag
	UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
	bool HasEmotionTag(const FGameplayTag& EmotionTag) const;

	// Get all emotion tags (core, range, and combined)
	UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
	FGameplayTagContainer GetAllEmotionTags() const;

	// Get dominant emotion (highest intensity)
	UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
	void GetDominantEmotion(FGameplayTag& OutEmotionTag, float& OutIntensity) const;

	// Event triggered when an emotion changes
	UPROPERTY(BlueprintAssignable, Category = "EmotionSystem")
	FOnEmotionChanged OnEmotionChanged;

	// Get the owner's display name for debugging
	FString GetOwnerName() const;

protected:
	// The current emotion state of the actor
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EmotionSystem")
	FEmotionState EmotionState;

	// Notify listeners that an emotion has changed
	void BroadcastEmotionChanged(const FGameplayTag& EmotionTag, float Intensity);
};
