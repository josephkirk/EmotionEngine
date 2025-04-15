#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "GameplayTagContainer.h"
#include "EmotionSubsystem.generated.h"

class UEmotionComponent;
class UEmotionLibrary;
class UEmotionDefinition;

/**
 * Subsystem for tracking and querying EmotionComponents with emotion tags
 * Provides global access to emotion system functionality
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

	// Find all EmotionComponents within a VA coordinate radius
	UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
	TArray<UEmotionComponent*> FindComponentsInVARadius(const FVector2D& VACoordinate, float Radius) const;

	// Find the closest EmotionComponent to a VA coordinate
	UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
	UEmotionComponent* FindClosestComponentToVACoordinate(const FVector2D& VACoordinate) const;

	// Apply an emotional influence to all components in a radius
	UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
	void ApplyEmotionalInfluenceInRadius(AActor* Influencer, const FGameplayTag& EmotionTag, float Intensity, 
		const FVector& Location, float Radius, bool bAdditive = true);

	// Apply an emotional influence to all components with a specific tag
	UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
	void ApplyEmotionalInfluenceToTag(AActor* Influencer, const FGameplayTag& TargetTag, 
		const FGameplayTag& EmotionTag, float Intensity, bool bAdditive = true);

	// Get the default emotion library
	UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
	UEmotionLibrary* GetDefaultEmotionLibrary() const;

	// Set the default emotion library
	UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
	void SetDefaultEmotionLibrary(UEmotionLibrary* NewLibrary);

	// Debug function to log all registered components and their emotions
	UFUNCTION(BlueprintCallable, Category = "EmotionSystem|Debug")
	void DebugLogAllEmotions() const;

	// Debug function to visualize all components' VA coordinates
	UFUNCTION(BlueprintCallable, Category = "EmotionSystem|Debug")
	void DebugVisualizeVACoordinates(float Duration = 5.0f) const;

private:
	// All registered EmotionComponents
	UPROPERTY()
	TArray<TWeakObjectPtr<UEmotionComponent>> RegisteredComponents;

	// Default emotion library to use if none is specified
	UPROPERTY()
	TObjectPtr<UEmotionLibrary> DefaultEmotionLibrary;

	// Helper function to filter components by tag
	TArray<UEmotionComponent*> FilterComponentsByTag(TFunctionRef<bool(UEmotionComponent*)> Predicate) const;

	// Helper function to get valid components
	TArray<UEmotionComponent*> GetValidComponents() const;
};
