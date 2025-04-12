#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "EmotionState.h"
#include "EmotionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEmotionChanged, const FGameplayTag&, EmotionTag, float, Intensity);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnEmotionalInfluence, AActor*, Influencer, const FGameplayTag&, EmotionTag, float, Intensity);

/**
 * Component that manages an actor's emotional state using the EmotionEngine system
 */
UCLASS(ClassGroup=(EmotionEngine), meta=(BlueprintSpawnableComponent))
class EMOTIONENGINE_API UEmotionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEmotionComponent(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called when the component is destroyed
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

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

	// Event triggered when an external actor influences this component's emotions
	UPROPERTY(BlueprintAssignable, Category = "EmotionSystem")
	FOnEmotionalInfluence OnEmotionalInfluence;

	// Receive an emotional influence from another actor
	UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
	bool ReceiveEmotionalInfluence(AActor* Influencer, const FGameplayTag& EmotionTag, float Intensity, bool bAdditive = true);

	// Check if this component can be influenced by the given actor
	UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
	bool CanReceiveInfluenceFrom(AActor* Influencer) const;

	// Get the emotional susceptibility to influences (multiplier for incoming influences)
	UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
	float GetEmotionalSusceptibility() const { return EmotionalSusceptibility; }

	// Get the owner's display name for debugging
	FString GetOwnerName() const;

protected:
	// The current emotion state of the actor
	/*UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EmotionSystem")
	UEmotionState* EmotionState;*/

	// How susceptible this actor is to emotional influences (multiplier for incoming influences)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EmotionSystem", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float EmotionalSusceptibility;

	// Tags for emotions this actor is immune to (will not be affected by these)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EmotionSystem", meta = (Categories = "Emotion"))
	FGameplayTagContainer ImmuneEmotions;

	// Actors that are allowed to influence this component's emotions (empty = all allowed)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EmotionSystem")
	TArray<TSubclassOf<AActor>> AllowedInfluencers;

	// Actors that are blocked from influencing this component's emotions
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EmotionSystem")
	TArray<TSubclassOf<AActor>> BlockedInfluencers;

	// Notify listeners that an emotion has changed
	void BroadcastEmotionChanged(const FGameplayTag& EmotionTag, float Intensity);

	// Notify listeners that an emotional influence was received
	void BroadcastEmotionalInfluence(AActor* Influencer, const FGameplayTag& EmotionTag, float Intensity);

private:
	UPROPERTY()
	TObjectPtr<UEmotionState> EmotionState;
};
