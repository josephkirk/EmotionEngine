#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EmotionInteractionInterface.h"
#include "EmotionInfluencer.generated.h"

class UEmotionComponent;

USTRUCT(BlueprintType)
struct EMOTIONENGINE_API FEmotionStimulusContext
{
    GENERATED_USTRUCT_BODY()
public:
    // The context tags for this stimulus (e.g., Combat.Damage, Dialogue.Compliment, Environment.Danger)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EmotionSystem", meta = (Categories = "EmotionStimulus"))
    FGameplayTagContainer ContextTags;
    
    // The source of the stimulus (who/what is causing it)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EmotionSystem")
    AActor* SourceActor;
    
    // Optional intensity modifier based on context
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EmotionSystem", meta = (ClampMin = "0.0", UIMin = "0.0"))
    float ContextIntensityModifier;
    
    FEmotionStimulusContext()
        : SourceActor(nullptr)
        , ContextIntensityModifier(1.0f)
    {}
};

/**
 * Base class for objects that can influence emotions of other actors as emotional stimuli
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
	virtual FGameplayTagContainer GetStimulusContext_Implementation() const override;
	virtual AActor* GetStimulusSource_Implementation() const override;
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

	// Set the stimulus context for this influencer
	UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
	virtual void SetStimulusContext(const FEmotionStimulusContext& NewContext);

	// Apply a specific emotional stimulus to a target
	UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
	virtual bool ApplyStimulusToTarget(AActor* TargetActor, const FGameplayTag& EmotionTag, float Intensity, const FEmotionStimulusContext& Context, bool bAdditive = true);

	// Apply a specific emotional stimulus in a radius
	UFUNCTION(BlueprintCallable, Category = "EmotionSystem")
	virtual int32 ApplyStimulusInRadius(const FVector& Origin, float Radius, const FGameplayTag& EmotionTag, float Intensity, const FEmotionStimulusContext& Context, bool bAdditive = true, bool bRequiresLineOfSight = false);

protected:
	// The strength of emotional influence this stimulus has (multiplier for intensity)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EmotionSystem", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float EmotionalInfluenceStrength;

	// The emotions this stimulus can trigger
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EmotionSystem", meta = (Categories = "Emotion.Core"))
	FGameplayTagContainer AvailableEmotions;

	// The context of this emotional stimulus
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EmotionSystem")
	FEmotionStimulusContext StimulusContext;

	// Check line of sight between two points
	bool HasLineOfSight(const FVector& Start, const FVector& End) const;
};
