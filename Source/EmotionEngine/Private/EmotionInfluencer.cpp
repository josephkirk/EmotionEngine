#include "EmotionInfluencer.h"
#include "EmotionComponent.h"
#include "EmotionSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
AEmotionInfluencer::AEmotionInfluencer()
{
	// Set this actor to call Tick() every frame
	PrimaryActorTick.bCanEverTick = false;

	// Default values
	EmotionalInfluenceStrength = 1.0f;
	
	// Initialize stimulus context
	StimulusContext.SourceActor = this;
	StimulusContext.ContextIntensityModifier = 1.0f;
}

bool AEmotionInfluencer::ApplyEmotionToTarget_Implementation(AActor* TargetActor, const FGameplayTag& EmotionTag, float Intensity, bool bAdditive)
{
	if (!TargetActor || !EmotionTag.IsValid())
	{
		return false;
	}

	// Check if this emotion is available to be triggered
	if (!AvailableEmotions.IsEmpty() && !AvailableEmotions.HasTag(EmotionTag))
	{
		return false;
	}

	// Find the emotion component on the target
	UEmotionComponent* EmotionComponent = FindEmotionComponent(TargetActor);
	if (!EmotionComponent)
	{
		return false;
	}

	// Apply influence strength modifier and context modifier
	float ModifiedIntensity = Intensity * EmotionalInfluenceStrength * StimulusContext.ContextIntensityModifier;

	// Use the ReceiveEmotionalInfluence method to properly handle the stimulus
	return EmotionComponent->ReceiveEmotionalInfluence(StimulusContext.SourceActor ? StimulusContext.SourceActor : this, EmotionTag, ModifiedIntensity, bAdditive);
}

int32 AEmotionInfluencer::ApplyEmotionInRadius_Implementation(const FVector& Origin, float Radius, const FGameplayTag& EmotionTag, float Intensity, bool bAdditive, bool bRequiresLineOfSight)
{
	if (!EmotionTag.IsValid() || Radius <= 0.0f)
	{
		return 0;
	}

	// Check if this emotion is available to be triggered
	if (!AvailableEmotions.IsEmpty() && !AvailableEmotions.HasTag(EmotionTag))
	{
		return 0;
	}

	// Get the emotion subsystem
	UWorld* World = GetWorld();
	if (!World)
	{
		return 0;
	}

	UEmotionSubsystem* EmotionSubsystem = World->GetSubsystem<UEmotionSubsystem>();
	if (!EmotionSubsystem)
	{
		return 0;
	}

	// Get all emotion components in the world
	TArray<UEmotionComponent*> AllComponents = EmotionSubsystem->GetAllEmotionComponents();

	// Count of affected actors
	int32 AffectedCount = 0;

	// Apply emotion to each component within radius
	for (UEmotionComponent* Component : AllComponents)
	{
		if (!Component || !Component->GetOwner())
		{
			continue;
		}

		AActor* TargetActor = Component->GetOwner();
		FVector TargetLocation = TargetActor->GetActorLocation();

		// Check if within radius
		float DistanceSquared = FVector::DistSquared(Origin, TargetLocation);
		if (DistanceSquared <= FMath::Square(Radius))
		{
			// Check line of sight if required
			if (bRequiresLineOfSight && !HasLineOfSight(Origin, TargetLocation))
			{
				continue;
			}

			// Calculate intensity falloff based on distance
			float Distance = FMath::Sqrt(DistanceSquared);
			float FalloffFactor = 1.0f - FMath::Clamp(Distance / Radius, 0.0f, 1.0f);
			float ScaledIntensity = Intensity * FalloffFactor;

			// Apply the emotion
			if (ApplyEmotionToTarget(TargetActor, EmotionTag, ScaledIntensity, bAdditive))
			{
				AffectedCount++;
			}
		}
	}

	// Optional: Draw debug sphere to visualize the radius
	#if WITH_EDITOR
	if (World->IsPlayInEditor())
	{
		DrawDebugSphere(World, Origin, Radius, 16, FColor::Yellow, false, 1.0f);
	}
	#endif

	return AffectedCount;
}

float AEmotionInfluencer::GetEmotionalInfluenceStrength_Implementation() const
{
	return EmotionalInfluenceStrength;
}

FGameplayTagContainer AEmotionInfluencer::GetAvailableEmotions_Implementation() const
{
	return AvailableEmotions;
}

FGameplayTagContainer AEmotionInfluencer::GetStimulusContext_Implementation() const
{
	return StimulusContext.ContextTags;
}

AActor* AEmotionInfluencer::GetStimulusSource_Implementation() const
{
	return StimulusContext.SourceActor ? StimulusContext.SourceActor : const_cast<AEmotionInfluencer*>(this);
}

void AEmotionInfluencer::SetStimulusContext(const FEmotionStimulusContext& NewContext)
{
	StimulusContext = NewContext;
	
	// If no source actor is specified, use this influencer as the source
	if (!StimulusContext.SourceActor)
	{
		StimulusContext.SourceActor = this;
	}
}

bool AEmotionInfluencer::ApplyStimulusToTarget(AActor* TargetActor, const FGameplayTag& EmotionTag, float Intensity, const FEmotionStimulusContext& Context, bool bAdditive)
{
	if (!TargetActor || !EmotionTag.IsValid())
	{
		return false;
	}
	
	// Store the original context
	FEmotionStimulusContext OriginalContext = StimulusContext;
	
	// Set the new context temporarily
	SetStimulusContext(Context);
	
	// Apply the emotion with the new context
	bool Result = ApplyEmotionToTarget(TargetActor, EmotionTag, Intensity, bAdditive);
	
	// Restore the original context
	SetStimulusContext(OriginalContext);
	
	return Result;
}

int32 AEmotionInfluencer::ApplyStimulusInRadius(const FVector& Origin, float Radius, const FGameplayTag& EmotionTag, float Intensity, const FEmotionStimulusContext& Context, bool bAdditive, bool bRequiresLineOfSight)
{
	if (!EmotionTag.IsValid() || Radius <= 0.0f)
	{
		return 0;
	}
	
	// Store the original context
	FEmotionStimulusContext OriginalContext = StimulusContext;
	
	// Set the new context temporarily
	SetStimulusContext(Context);
	
	// Apply the emotion in radius with the new context
	int32 Result = ApplyEmotionInRadius(Origin, Radius, EmotionTag, Intensity, bAdditive, bRequiresLineOfSight);
	
	// Restore the original context
	SetStimulusContext(OriginalContext);
	
	return Result;
}

UEmotionComponent* AEmotionInfluencer::FindEmotionComponent(AActor* Actor)
{
	if (!Actor)
	{
		return nullptr;
	}

	return Actor->FindComponentByClass<UEmotionComponent>();
}

bool AEmotionInfluencer::ApplyEmotionWithFalloff(AActor* TargetActor, const FGameplayTag& EmotionTag, float Intensity, float MaxDistance)
{
	if (!TargetActor || !EmotionTag.IsValid() || MaxDistance <= 0.0f)
	{
		return false;
	}

	// Calculate distance between this influencer and the target
	float Distance = FVector::Distance(GetActorLocation(), TargetActor->GetActorLocation());
	
	// If beyond max distance, no effect
	if (Distance > MaxDistance)
	{
		return false;
	}

	// Calculate falloff based on distance
	float FalloffFactor = 1.0f - FMath::Clamp(Distance / MaxDistance, 0.0f, 1.0f);
	float ScaledIntensity = Intensity * FalloffFactor;

	// Apply the emotion with scaled intensity
	return ApplyEmotionToTarget(TargetActor, EmotionTag, ScaledIntensity, true);
}

int32 AEmotionInfluencer::TriggerAllEmotionsInRadius(float Radius, float Intensity, bool bAdditive)
{
	if (AvailableEmotions.IsEmpty() || Radius <= 0.0f)
	{
		return 0;
	}

	int32 TotalAffected = 0;
	FVector Origin = GetActorLocation();

	// Apply each available emotion
	for (const FGameplayTag& EmotionTag : AvailableEmotions)
	{
		TotalAffected += ApplyEmotionInRadius(Origin, Radius, EmotionTag, Intensity, bAdditive, false);
	}

	return TotalAffected;
}

bool AEmotionInfluencer::HasLineOfSight(const FVector& Start, const FVector& End) const
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return false;
	}

	// Perform line trace to check visibility
	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.bTraceComplex = false;

	bool bHit = World->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, QueryParams);

	// If nothing was hit, or the hit location is very close to the end point, we have line of sight
	if (!bHit || (HitResult.Location - End).IsNearlyZero(1.0f))
	{
		return true;
	}

	return false;
}
