#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EmotionInteractionInterface.h"
#include "EmotionInfluencer.generated.h"

class UEmotionComponent;

/**
 * Base class for objects that can influence emotions of other actors
 * Implements the EmotionInteractionInterface with common functionality
 */
UCLASS(BlueprintType)
class EMOTIONENGINE_API AEmotionInfluencer : public AActor, public IEmotionInteractionInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEmotionInfluencer();

	// Begin IEmotionInteractionInterface
	virtual bool ApplyEmotionToTarget_Implementation(AActor* TargetActor, const FGameplayTag& EmotionTag, float Intensity, bool bAdditive) override;
	virtual int32 ApplyEmotionInRadius_Implementation(const FVector& Origin, float Radius, const FGameplayTag& EmotionTag, float Intensity, bool bAdditive, bool bRequiresLineOfSight) override;
	virtual float GetEmotionalInfluenceStrength_Implementation() const override;
	virtual FGameplayTagContainer GetAvailableEmotions_Implementation() const override;
	// End IEmotionInteractionInterface

	// Helper function to find an EmotionComponent on an actor
	UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
	static UEmotionComponent* FindEmotionComponent(AActor* Actor);

	// Apply emotion with distance-based falloff
	UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
	virtual bool ApplyEmotionWithFalloff(AActor* TargetActor, const FGameplayTag& EmotionTag, float Intensity, float MaxDistance);

	// Trigger all available emotions in radius
	UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
	virtual int32 TriggerAllEmotionsInRadius(float Radius, float Intensity, bool bAdditive);

protected:
	// The strength of emotional influence this object has (multiplier for intensity)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EmotionSystem", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float EmotionalInfluenceStrength;

	// The emotions this object can trigger
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EmotionSystem", meta = (Categories = "Emotion.Core"))
	FGameplayTagContainer AvailableEmotions;

	// Check line of sight between two points
	bool HasLineOfSight(const FVector& Start, const FVector& End) const;
};
