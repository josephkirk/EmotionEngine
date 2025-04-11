#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "GameplayTagContainer.h"
#include "EmotionSubsystem.generated.h"

class UEmotionComponent;

/**
 * Subsystem for tracking and querying EmotionComponents with emotion tags
 */
UCLASS()
class EMOTIONENGINE_API UEmotionSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	// Begin USubsystem
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	// End USubsystem

	// Register an EmotionComponent with the subsystem
	void RegisterEmotionComponent(UEmotionComponent* Component);

	// Unregister an EmotionComponent from the subsystem
	void UnregisterEmotionComponent(UEmotionComponent* Component);

	// Notify the subsystem that an emotion has changed in a component
	void NotifyEmotionChanged(UEmotionComponent* Component, const FGameplayTag& EmotionTag, float Intensity);

	// Get all EmotionComponents in the world
	UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
	TArray<UEmotionComponent*> GetAllEmotionComponents() const;

	// Find all EmotionComponents with a specific emotion tag
	UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
	TArray<UEmotionComponent*> FindComponentsWithEmotionTag(const FGameplayTag& EmotionTag) const;

	// Find all EmotionComponents with any of the emotion tags in the container
	UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
	TArray<UEmotionComponent*> FindComponentsWithAnyEmotionTags(const FGameplayTagContainer& EmotionTags) const;

	// Find all EmotionComponents with all of the emotion tags in the container
	UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
	TArray<UEmotionComponent*> FindComponentsWithAllEmotionTags(const FGameplayTagContainer& EmotionTags) const;

	// Find the closest EmotionComponent with a specific emotion tag
	UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
	UEmotionComponent* FindClosestComponentWithEmotionTag(const FGameplayTag& EmotionTag, const FVector& Location, float MaxDistance = 0.0f) const;

	// Find all EmotionComponents within a radius that have a specific emotion tag
	UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
	TArray<UEmotionComponent*> FindComponentsWithEmotionTagInRadius(const FGameplayTag& EmotionTag, const FVector& Location, float Radius) const;

	// Get components sorted by emotion intensity (highest first)
	UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
	TArray<UEmotionComponent*> GetComponentsSortedByEmotionIntensity(const FGameplayTag& EmotionTag) const;

	// Debug function to log all registered components and their emotions
	UFUNCTION(BlueprintCallable, Category = "EmotionSystem|Debug")
	void DebugLogAllEmotions() const;

private:
	// All registered EmotionComponents
	TArray<TWeakObjectPtr<UEmotionComponent>> RegisteredComponents;

	// Helper function to filter components by tag
	TArray<UEmotionComponent*> FilterComponentsByTag(TFunctionRef<bool(UEmotionComponent*)> Predicate) const;
};
