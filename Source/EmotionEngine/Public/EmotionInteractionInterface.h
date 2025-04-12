#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayTagContainer.h"
#include "EmotionInteractionInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEmotionInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for objects that can affect the emotions of actors with EmotionComponents
 * Implement this interface in any class that should be able to trigger emotional responses
 */
class EMOTIONENGINE_API IEmotionInteractionInterface
{
	GENERATED_BODY()

public:
	/**
	 * Apply an emotional effect to a target actor
	 * @param TargetActor The actor to affect emotionally
	 * @param EmotionTag The emotion tag to apply
	 * @param Intensity The intensity of the emotion (-1.0 to 1.0)
	 * @param bAdditive Whether to add to existing emotion (true) or set it directly (false)
	 * @return True if the emotion was successfully applied
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "EmotionSystem")
	bool ApplyEmotionToTarget(AActor* TargetActor, const FGameplayTag& EmotionTag, float Intensity, bool bAdditive);

	/**
	 * Apply an emotional effect to all actors within a radius
	 * @param Origin The center point for the radius check
	 * @param Radius The radius to affect actors within
	 * @param EmotionTag The emotion tag to apply
	 * @param Intensity The intensity of the emotion (-1.0 to 1.0)
	 * @param bAdditive Whether to add to existing emotion (true) or set it directly (false)
	 * @param bRequiresLineOfSight Whether actors need to be visible from the origin
	 * @return Number of actors affected
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "EmotionSystem")
	int32 ApplyEmotionInRadius(const FVector& Origin, float Radius, const FGameplayTag& EmotionTag, float Intensity, bool bAdditive, bool bRequiresLineOfSight);

	/**
	 * Get the emotional influence strength of this object
	 * Higher values mean this object has more influence when affecting emotions
	 * @return The influence strength (default 1.0)
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "EmotionSystem")
	float GetEmotionalInfluenceStrength() const;

	/**
	 * Get the emotions this object can trigger
	 * @return Container of emotion tags this object can apply
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "EmotionSystem")
	FGameplayTagContainer GetAvailableEmotions() const;
};
