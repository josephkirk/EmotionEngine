#include "EmotionFunctionLibrary.h"
#include "EmotionComponent.h"
#include "EmotionInteractionInterface.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "EmotionSystemLibrary.h"

UEmotionComponent* UEmotionFunctionLibrary::FindEmotionComponent(AActor* Actor)
{
	if (!Actor)
	{
		return nullptr;
	}
	
	return Actor->FindComponentByClass<UEmotionComponent>();
}

int32 UEmotionFunctionLibrary::ApplyEmotionWithFalloff(
	AActor* Influencer,
	const FVector& Origin,
	const TArray<AActor*>& Targets,
	const FGameplayTag& EmotionTag,
	float BaseIntensity,
	float InnerRadius,
	float OuterRadius,
	bool bAdditive,
	bool bRequiresLineOfSight)
{
	if (!Influencer || !EmotionTag.IsValid() || Targets.Num() == 0 || OuterRadius <= 0.0f)
	{
		return 0;
	}

	// Make sure inner radius is not larger than outer radius
	InnerRadius = FMath::Min(InnerRadius, OuterRadius);
	
	// Get influence strength from the influencer if it implements the interface
	float InfluenceStrength = 1.0f;
	if (Influencer->Implements<UEmotionInteractionInterface>())
	{
		InfluenceStrength = IEmotionInteractionInterface::Execute_GetEmotionalInfluenceStrength(Influencer);
	}

	UWorld* World = Influencer->GetWorld();
	int32 AffectedCount = 0;

	// Apply emotion to each target with distance-based falloff
	for (AActor* Target : Targets)
	{
		if (!Target || Target == Influencer)
		{
			continue;
		}

		UEmotionComponent* EmotionComp = FindEmotionComponent(Target);
		if (!EmotionComp)
		{
			continue;
		}

		// Check if the target can receive influence from this influencer
		if (!EmotionComp->CanReceiveInfluenceFrom(Influencer))
		{
			continue;
		}

		// Calculate distance and check if within range
		const FVector TargetLocation = Target->GetActorLocation();
		const float Distance = FVector::Distance(Origin, TargetLocation);
		
		if (Distance > OuterRadius)
		{
			continue;
		}

		// Check line of sight if required
		if (bRequiresLineOfSight && !HasLineOfSight(World, Origin, TargetLocation))
		{
			continue;
		}

		// Calculate intensity with falloff
		float FinalIntensity = BaseIntensity * InfluenceStrength;
		
		// Apply falloff if beyond inner radius
		if (Distance > InnerRadius)
		{
			// Linear falloff from inner radius to outer radius
			const float FalloffRange = OuterRadius - InnerRadius;
			const float DistanceFromInner = Distance - InnerRadius;
			const float FalloffFactor = 1.0f - FMath::Clamp(DistanceFromInner / FalloffRange, 0.0f, 1.0f);
			FinalIntensity *= FalloffFactor;
		}

		// Apply the emotion to the target
		if (EmotionComp->ReceiveEmotionalInfluence(Influencer, EmotionTag, FinalIntensity, bAdditive))
		{
			AffectedCount++;
		}
	}

	return AffectedCount;
}

bool UEmotionFunctionLibrary::ApplyEmotionToTarget(
	AActor* Influencer,
	AActor* TargetActor,
	const FGameplayTag& EmotionTag,
	float Intensity,
	bool bAdditive)
{
	if (!Influencer || !TargetActor || !EmotionTag.IsValid())
	{
		return false;
	}

	// Get influence strength from the influencer if it implements the interface
	float InfluenceStrength = 1.0f;
	if (Influencer->Implements<UEmotionInteractionInterface>())
	{
		InfluenceStrength = IEmotionInteractionInterface::Execute_GetEmotionalInfluenceStrength(Influencer);
	}

	// Find the emotion component on the target
	UEmotionComponent* EmotionComp = FindEmotionComponent(TargetActor);
	if (!EmotionComp)
	{
		return false;
	}

	// Apply the emotion with the influencer's strength
	return EmotionComp->ReceiveEmotionalInfluence(Influencer, EmotionTag, Intensity * InfluenceStrength, bAdditive);
}

bool UEmotionFunctionLibrary::GetActorDominantEmotion(
	AActor* Actor,
	FGameplayTag& OutEmotionTag,
	float& OutIntensity)
{
	OutEmotionTag = FGameplayTag();
	OutIntensity = 0.0f;
	
	if (!Actor)
	{
		return false;
	}
	
	UEmotionComponent* EmotionComp = FindEmotionComponent(Actor);
	if (!EmotionComp)
	{
		return false;
	}
	
	EmotionComp->GetDominantEmotion(OutEmotionTag, OutIntensity);
	return OutEmotionTag.IsValid();
}

bool UEmotionFunctionLibrary::ActorHasEmotionTag(
	AActor* Actor,
	const FGameplayTag& EmotionTag)
{
	if (!Actor || !EmotionTag.IsValid())
	{
		return false;
	}
	
	UEmotionComponent* EmotionComp = FindEmotionComponent(Actor);
	if (!EmotionComp)
	{
		return false;
	}
	
	return EmotionComp->HasEmotionTag(EmotionTag);
}

FVector2D UEmotionFunctionLibrary::GetActorVACoordinate(AActor* Actor)
{
	if (!Actor)
	{
		return FVector2D::ZeroVector;
	}
	
	UEmotionComponent* EmotionComp = FindEmotionComponent(Actor);
	if (!EmotionComp)
	{
		return FVector2D::ZeroVector;
	}
	
	return EmotionComp->GetVACoordinate();
}

TArray<AActor*> UEmotionFunctionLibrary::FindActorsWithEmotionInRadius(
	const UObject* WorldContextObject,
	const FVector& Origin,
	float Radius,
	const FGameplayTag& EmotionTag,
	float MinIntensity)
{
	TArray<AActor*> Result;
	
	if (!WorldContextObject || Radius <= 0.0f)
	{
		return Result;
	}
	
	UWorld* World = WorldContextObject->GetWorld();
	if (!World)
	{
		return Result;
	}
	
	// Get all actors with emotion components in the level
	TArray<AActor*> AllActors;
	UGameplayStatics::GetAllActorsOfClass(World, AActor::StaticClass(), AllActors);
	
	for (AActor* Actor : AllActors)
	{
		if (!Actor)
		{
			continue;
		}
		
		UEmotionComponent* EmotionComp = FindEmotionComponent(Actor);
		if (!EmotionComp)
		{
			continue;
		}
		
		// Check distance
		const float Distance = FVector::Distance(Origin, Actor->GetActorLocation());
		if (Distance > Radius)
		{
			continue;
		}
		
		// If an emotion tag is specified, check if the actor has it with sufficient intensity
		if (EmotionTag.IsValid())
		{
			const float Intensity = EmotionComp->GetEmotionIntensity(EmotionTag);
			if (Intensity < MinIntensity)
			{
				continue;
			}
		}
		
		Result.Add(Actor);
	}
	
	return Result;
}

UEmotionData* UEmotionFunctionLibrary::FindClosestEmotionToCoordinate(
	const FVector2D& VACoordinate,
	UEmotionLibrary* EmotionLibrary)
{
	// Use the EmotionSystemLibrary to find the closest emotion
	return UEmotionSystemLibrary::FindClosestEmotion(VACoordinate, EmotionLibrary);
}

bool UEmotionFunctionLibrary::CanEmotionsCombine(
	const FGameplayTag& EmotionTag1,
	const FGameplayTag& EmotionTag2,
	UEmotionLibrary* EmotionLibrary)
{
	if (!EmotionTag1.IsValid() || !EmotionTag2.IsValid())
	{
		return false;
	}
	
	// Get the library or default
	UEmotionLibrary* Library = UEmotionSystemLibrary::GetLibraryOrDefault(EmotionLibrary);
	if (!Library)
	{
		return false;
	}
	
	// Check if there's a combined emotion result
	FGameplayTag CombinedTag = UEmotionSystemLibrary::GetCombinedEmotion(EmotionTag1, EmotionTag2, Library);
	return CombinedTag.IsValid();
}

int32 UEmotionFunctionLibrary::ApplyEmotionalStimulusInRadius(
	const UObject* WorldContextObject,
	AActor* Influencer,
	const FVector& Origin,
	float Radius,
	const FGameplayTag& EmotionTag,
	float Intensity,
	bool bRequiresLineOfSight)
{
	if (!WorldContextObject || !Influencer || !EmotionTag.IsValid() || Radius <= 0.0f)
	{
		return 0;
	}
	
	UWorld* World = WorldContextObject->GetWorld();
	if (!World)
	{
		return 0;
	}
	
	// Get all actors with emotion components in the level
	TArray<AActor*> AllActors;
	UGameplayStatics::GetAllActorsOfClass(World, AActor::StaticClass(), AllActors);
	
	TArray<AActor*> TargetsInRadius;
	
	for (AActor* Actor : AllActors)
	{
		if (!Actor || Actor == Influencer)
		{
			continue;
		}
		
		UEmotionComponent* EmotionComp = FindEmotionComponent(Actor);
		if (!EmotionComp)
		{
			continue;
		}
		
		// Check distance
		const float Distance = FVector::Distance(Origin, Actor->GetActorLocation());
		if (Distance <= Radius)
		{
			TargetsInRadius.Add(Actor);
		}
	}
	
	// Apply emotion to all targets in radius
	return ApplyEmotionWithFalloff(
		Influencer,
		Origin,
		TargetsInRadius,
		EmotionTag,
		Intensity,
		0.0f, // Inner radius of 0 means full intensity at the center
		Radius,
		true, // Additive
		bRequiresLineOfSight);
}

bool UEmotionFunctionLibrary::HasLineOfSight(const UWorld* World, const FVector& Start, const FVector& End)
{
	if (!World)
	{
		return false;
	}

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.bTraceComplex = false;
	QueryParams.AddIgnoredActor(World->GetFirstPlayerController()->GetPawn());

	// Trace from start to end, checking for blocking hits
	bool bHit = World->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, QueryParams);

	// If we hit something, check if it's the end point (target)
	if (bHit)
	{
		// If the hit is very close to the end point, consider it a hit on the target
		if (FVector::Distance(HitResult.Location, End) < 50.0f)
		{
			return true;
		}
		return false; // Hit something else, no line of sight
	}

	return true; // No hit, clear line of sight
}
