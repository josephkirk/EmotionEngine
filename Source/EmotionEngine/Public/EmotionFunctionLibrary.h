#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayTagContainer.h"
#include "EmotionComponent.h"
#include "EmotionFunctionLibrary.generated.h"

/**
 * Blueprint Function Library for the EmotionEngine system
 * Provides utility functions for working with emotions and the EmotionEngine components
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
	 * @param BaseIntensity The base intensity of the emotion (-1.0 to 1.0)
	 * @param InnerRadius Radius within which full intensity is applied
	 * @param OuterRadius Maximum radius of effect (intensity falls off to zero)
	 * @param bAdditive Whether to add to existing emotion (true) or set it directly (false)
	 * @param bRequiresLineOfSight Whether actors need to be visible from the origin
	 * @return Number of actors affected
	 */
	UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
	static int32 AffectsEmotionsWithFalloffs(
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
	 * @param Intensity The intensity of the emotion (-1.0 to 1.0)
	 * @param bAdditive Whether to add to existing emotion (true) or set it directly (false)
	 * @return True if the emotion was successfully applied
	 */
	UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
	static bool AffectEmotionOnTarget(
		AActor* Influencer,
		AActor* TargetActor,
		const FGameplayTag& EmotionTag,
		float Intensity,
		bool bAdditive = true);

private:
	// Helper function to check line of sight between two points
	static bool HasLineOfSight(const UWorld* World, const FVector& Start, const FVector& End);
};
