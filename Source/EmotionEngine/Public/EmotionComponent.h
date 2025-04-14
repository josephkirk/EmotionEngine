#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "EmotionState.h"
#include "EmotionData.h"
#include "Emotion.h"
#include "EmotionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEmotionChanged, const FGameplayTag&, EmotionTag, float, Intensity);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnEmotionalInfluence, AActor*, Influencer, const FGameplayTag&, EmotionTag, float, Intensity);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnVACoordinateChanged, const FVector2D&, NewVACoordinate);

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

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Called when the component is destroyed
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// Add an emotion with intensity (0-100)
	UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
	void AddEmotion(const FGameplayTag& EmotionTag, float Intensity);

	// Remove an emotion
	UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
	void RemoveEmotion(const FGameplayTag& EmotionTag);

	// Set intensity for an emotion (0-100)
	UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
	void SetEmotionIntensity(const FGameplayTag& EmotionTag, float Intensity);

	// Get intensity for any emotion tag
	UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
	float GetEmotionIntensity(const FGameplayTag& EmotionTag) const;

	// Check if the component has a specific emotion tag
	UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
	bool HasEmotionTag(const FGameplayTag& EmotionTag) const;

	// Get all emotion tags (active, range, and combined)
	UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
	FGameplayTagContainer GetAllEmotionTags() const;

	// Get all active emotions
	UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
	TArray<FActiveEmotion> GetActiveEmotions() const;

	// Get dominant emotion (highest intensity)
	UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
	void GetDominantEmotion(FGameplayTag& OutEmotionTag, float& OutIntensity) const;

	// Get the current Valence-Arousal coordinate
	UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
	FVector2D GetVACoordinate() const;

	// Set the Valence-Arousal coordinate directly (usually not needed as it's calculated from active emotions)
	UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
	void SetVACoordinate(const FVector2D& NewVACoordinate);

	// Get the influence radius in VA space
	UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
	float GetInfluenceRadius() const;

	// Set the influence radius in VA space
	UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
	void SetInfluenceRadius(float NewRadius);

	// Find emotions within a certain radius in the VA space
	UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
	TArray<UEmotionData*> FindEmotionsInRadius(float Radius) const;

	// Event triggered when an emotion changes
	UPROPERTY(BlueprintAssignable, Category = "EmotionSystem")
	FOnEmotionChanged OnEmotionChanged;

	// Event triggered when the VA coordinate changes
	UPROPERTY(BlueprintAssignable, Category = "EmotionSystem")
	FOnVACoordinateChanged OnVACoordinateChanged;

	// Event triggered when an external actor influences this component's emotions
	UPROPERTY(BlueprintAssignable, Category = "EmotionSystem")
	FOnEmotionalInfluence OnEmotionalInfluence;

	// Receive an emotional influence from another actor
	UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
	bool ReceiveEmotionalInfluence(AActor* Influencer, const FGameplayTag& EmotionTag, float Intensity, bool bAdditive = true);

	// Apply an emotional stimulus directly to this component
	UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
	void ApplyEmotionalStimulus(const FGameplayTag& EmotionTag, float Intensity);

	// Check if this component can be influenced by the given actor
	UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
	bool CanReceiveInfluenceFrom(AActor* Influencer) const;

	// Get the emotional susceptibility to influences (multiplier for incoming influences)
	UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
	float GetEmotionalSusceptibility() const { return EmotionalSusceptibility; }

	// Set the emotional susceptibility
	UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
	void SetEmotionalSusceptibility(float NewSusceptibility);

	// Get the owner's display name for debugging
	FString GetOwnerName() const;

protected:
	// The emotion library to use (if not specified, will use default from game instance)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EmotionSystem")
	TObjectPtr<UEmotionLibrary> EmotionLibrary;

	// How susceptible this actor is to emotional influences (multiplier for incoming influences)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EmotionSystem", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float EmotionalSusceptibility;

	// Spring stiffness for VA coordinate movement (higher = faster response to emotion changes)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EmotionSystem", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float SpringStiffness;

	// Damping factor for VA coordinate movement (higher = less oscillation)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EmotionSystem", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float DampingFactor;

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

	// Notify listeners that the VA coordinate has changed
	void BroadcastVACoordinateChanged(const FVector2D& NewVACoordinate);

	// Notify listeners that an emotional influence was received
	void BroadcastEmotionalInfluence(AActor* Influencer, const FGameplayTag& EmotionTag, float Intensity);

private:
	// The emotional state managed by this component
	UPROPERTY()
	TObjectPtr<UEmotionState> EmotionState;

	// Initialize the emotion state if not already done
	void InitializeEmotionState();
};
