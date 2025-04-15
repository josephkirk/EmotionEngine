#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayTagContainer.h"
#include "EmotionComponent.h"
#include "EmotionData.h"
#include "EmotionFunctionLibrary.generated.h"

/**
 * Blueprint Function Library for the EmotionEngine system
 * Provides designer-friendly utility functions for working with emotions and the EmotionEngine components
 */
UCLASS()
class EMOTIONENGINE_API UEmotionFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * Find an EmotionComponent on an actor
	 * @param Actor The actor to search for an EmotionComponent
	 * @return The found EmotionComponent, or nullptr if none exists
	 */
	UFUNCTION(BlueprintPure, Category = "EmotionSystem")
	static UEmotionComponent* FindEmotionComponent(AActor* Actor);

	/**
	 * Apply emotion with distance-based falloff to multiple targets
	 * @param Influencer The actor influencing emotions
	 * @param Origin The center point for the radius check
	 * @param Targets Array of target actors to affect
	 * @param EmotionTag The emotion tag to apply
	 * @param BaseIntensity The base intensity of the emotion (0.0 to 100.0)
	 * @param InnerRadius Radius within which full intensity is applied
	 * @param OuterRadius Maximum radius of effect (intensity falls off to zero)
	 * @param bAdditive Whether to add to existing emotion (true) or set it directly (false)
	 * @param bRequiresLineOfSight Whether actors need to be visible from the origin
	 * @return Number of actors affected
	 */
	UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
	static int32 ApplyEmotionWithFalloff(
		AActor* Influencer,
		const FVector& Origin,
		const TArray<AActor*>& Targets,
		const FGameplayTag& EmotionTag,
		float BaseIntensity,
		float InnerRadius,
		float OuterRadius,
		bool bAdditive = true,
		bool bRequiresLineOfSight = false);

	/**
	 * Apply an emotion to a target actor using an influencer
	 * @param Influencer The actor influencing emotions
	 * @param TargetActor The actor to affect emotionally
	 * @param EmotionTag The emotion tag to apply
	 * @param Intensity The intensity of the emotion (0.0 to 100.0)
	 * @param bAdditive Whether to add to existing emotion (true) or set it directly (false)
	 * @return True if the emotion was successfully applied
	 */
	UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
	static bool ApplyEmotionToTarget(
		AActor* Influencer,
		AActor* TargetActor,
		const FGameplayTag& EmotionTag,
		float Intensity,
		bool bAdditive = true);

	/**
	 * Get the dominant emotion from an actor
	 * @param Actor The actor to get the dominant emotion from
	 * @param OutEmotionTag The output emotion tag
	 * @param OutIntensity The output intensity
	 * @return True if a dominant emotion was found
	 */
	UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
	static bool GetActorDominantEmotion(
		AActor* Actor,
		FGameplayTag& OutEmotionTag,
		float& OutIntensity);

	/**
	 * Check if an actor has a specific emotion tag
	 * @param Actor The actor to check
	 * @param EmotionTag The emotion tag to check for
	 * @return True if the actor has the emotion tag
	 */
	UFUNCTION(BlueprintPure, Category = "EmotionSystem")
	static bool ActorHasEmotionTag(
		AActor* Actor,
		const FGameplayTag& EmotionTag);

	/**
	 * Get the Valence-Arousal coordinate of an actor
	 * @param Actor The actor to get the VA coordinate from
	 * @return The VA coordinate, or (0,0) if no emotion component found
	 */
	UFUNCTION(BlueprintPure, Category = "EmotionSystem")
	static FVector2D GetActorVACoordinate(AActor* Actor);

	/**
	 * Find actors with a specific emotion within a radius
	 * @param WorldContext The world context
	 * @param Origin The center point for the radius check
	 * @param Radius The radius to search within
	 * @param EmotionTag The emotion tag to search for (optional)
	 * @param MinIntensity The minimum intensity required (0.0 to 100.0)
	 * @return Array of actors matching the criteria
	 */
	UFUNCTION(BlueprintCallable, Category = "EmotionSystem", meta = (WorldContext = "WorldContextObject"))
	static TArray<AActor*> FindActorsWithEmotionInRadius(
		const UObject* WorldContextObject,
		const FVector& Origin,
		float Radius,
		const FGameplayTag& EmotionTag,
		float MinIntensity = 0.0f);

	/**
	 * Find the closest emotion to a VA coordinate
	 * @param VACoordinate The Valence-Arousal coordinate to search from
	 * @param EmotionLibrary Optional emotion library to use (uses default if null)
	 * @return The closest emotion data, or nullptr if none found
	 */
	UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
	static UEmotionDefinition* FindClosestEmotionToCoordinate(
		const FVector2D& VACoordinate,
		UEmotionLibrary* EmotionLibrary = nullptr);

	/**
	 * Check if two emotions can combine
	 * @param EmotionTag1 The first emotion tag
	 * @param EmotionTag2 The second emotion tag
	 * @param EmotionLibrary Optional emotion library to use (uses default if null)
	 * @return True if the emotions can combine
	 */
	UFUNCTION(BlueprintPure, Category = "EmotionSystem")
	static bool CanEmotionsCombine(
		const FGameplayTag& EmotionTag1,
		const FGameplayTag& EmotionTag2,
		UEmotionLibrary* EmotionLibrary = nullptr);

	/**
	 * Apply an emotional stimulus to all actors in a radius
	 * @param WorldContext The world context
	 * @param Influencer The actor influencing emotions
	 * @param Origin The center point for the radius check
	 * @param Radius The radius to affect
	 * @param EmotionTag The emotion tag to apply
	 * @param Intensity The intensity of the emotion (0.0 to 100.0)
	 * @param bRequiresLineOfSight Whether actors need to be visible from the origin
	 * @return Number of actors affected
	 */
	UFUNCTION(BlueprintCallable, Category = "EmotionSystem", meta = (WorldContext = "WorldContextObject"))
	static int32 ApplyEmotionalStimulusInRadius(
		const UObject* WorldContextObject,
		AActor* Influencer,
		const FVector& Origin,
		float Radius,
		const FGameplayTag& EmotionTag,
		float Intensity,
		bool bRequiresLineOfSight = false);

private:
	// Helper function to check line of sight between two points
	static bool HasLineOfSight(const UWorld* World, const FVector& Start, const FVector& End);
};
