#include "EmotionSubsystem.h"
#include "EmotionComponent.h"
#include "EmotionSystemLibrary.h"
#include "EmotionData.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(EmotionSubsystem)

void UEmotionSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	// Initialize the subsystem
	UE_LOG(LogTemp, Log, TEXT("EmotionSubsystem initialized"));
	
	// Initialize the default emotion library
	DefaultEmotionLibrary = UEmotionSystemLibrary::GetDefaultEmotionLibrary();
}

void UEmotionSubsystem::Deinitialize()
{
	// Clear all registered components
	RegisteredComponents.Empty();
	DefaultEmotionLibrary = nullptr;
	
	UE_LOG(LogTemp, Log, TEXT("EmotionSubsystem deinitialized"));
	
	Super::Deinitialize();
}

void UEmotionSubsystem::RegisterEmotionComponent(UEmotionComponent* Component)
{
	if (Component)
	{
		// Add to the registered components array if not already present
		TWeakObjectPtr<UEmotionComponent> WeakComponent(Component);
		if (!RegisteredComponents.Contains(WeakComponent))
		{
			RegisteredComponents.Add(WeakComponent);
			UE_LOG(LogTemp, Verbose, TEXT("Registered EmotionComponent for %s"), *Component->GetOwnerName());
		}
	}
}

void UEmotionSubsystem::UnregisterEmotionComponent(UEmotionComponent* Component)
{
	if (Component)
	{
		// Remove from the registered components array
		TWeakObjectPtr<UEmotionComponent> WeakComponent(Component);
		if (RegisteredComponents.Remove(WeakComponent) > 0)
		{
			UE_LOG(LogTemp, Verbose, TEXT("Unregistered EmotionComponent for %s"), *Component->GetOwnerName());
		}
	}
}

void UEmotionSubsystem::NotifyEmotionChanged(UEmotionComponent* Component, const FGameplayTag& EmotionTag, float Intensity)
{
	// This function can be used to react to emotion changes globally
	// For now, just log the change
	if (Component)
	{
		UE_LOG(LogTemp, Verbose, TEXT("%s emotion changed: %s = %.2f"), 
			*Component->GetOwnerName(), *EmotionTag.ToString(), Intensity);
		
		// Here you could implement global reactions to emotion changes
		// For example, notify nearby components of strong emotions
		// or trigger environmental effects based on collective emotions
	}
}

TArray<UEmotionComponent*> UEmotionSubsystem::GetAllEmotionComponents() const
{
	return GetValidComponents();
}

TArray<UEmotionComponent*> UEmotionSubsystem::GetValidComponents() const
{
	TArray<UEmotionComponent*> Result;
	
	// Convert weak pointers to regular pointers, filtering out invalid ones
	for (const TWeakObjectPtr<UEmotionComponent>& WeakComponent : RegisteredComponents)
	{
		if (WeakComponent.IsValid())
		{
			Result.Add(WeakComponent.Get());
		}
	}
	
	return Result;
}

TArray<UEmotionComponent*> UEmotionSubsystem::FindComponentsWithEmotionTag(const FGameplayTag& EmotionTag) const
{
	return FilterComponentsByTag([EmotionTag](UEmotionComponent* Component) {
		return Component->HasEmotionTag(EmotionTag);
	});
}

TArray<UEmotionComponent*> UEmotionSubsystem::FindComponentsWithAnyEmotionTags(const FGameplayTagContainer& EmotionTags) const
{
	return FilterComponentsByTag([&EmotionTags](UEmotionComponent* Component) {
		return Component->GetAllEmotionTags().HasAny(EmotionTags);
	});
}

TArray<UEmotionComponent*> UEmotionSubsystem::FindComponentsWithAllEmotionTags(const FGameplayTagContainer& EmotionTags) const
{
	return FilterComponentsByTag([&EmotionTags](UEmotionComponent* Component) {
		return Component->GetAllEmotionTags().HasAll(EmotionTags);
	});
}

UEmotionComponent* UEmotionSubsystem::FindClosestComponentWithEmotionTag(const FGameplayTag& EmotionTag, const FVector& Location, float MaxDistance) const
{
	UEmotionComponent* ClosestComponent = nullptr;
	float ClosestDistanceSq = (MaxDistance > 0.0f) ? (MaxDistance * MaxDistance) : MAX_FLT;
	
	TArray<UEmotionComponent*> ComponentsWithTag = FindComponentsWithEmotionTag(EmotionTag);
	
	for (UEmotionComponent* Component : ComponentsWithTag)
	{
		if (Component && Component->GetOwner())
		{
			const FVector OwnerLocation = Component->GetOwner()->GetActorLocation();
			const float DistanceSq = FVector::DistSquared(Location, OwnerLocation);
			
			if (DistanceSq < ClosestDistanceSq)
			{
				ClosestComponent = Component;
				ClosestDistanceSq = DistanceSq;
			}
		}
	}
	
	return ClosestComponent;
}

TArray<UEmotionComponent*> UEmotionSubsystem::FindComponentsWithEmotionTagInRadius(const FGameplayTag& EmotionTag, const FVector& Location, float Radius) const
{
	TArray<UEmotionComponent*> Result;
	const float RadiusSq = Radius * Radius;
	
	TArray<UEmotionComponent*> ComponentsWithTag = FindComponentsWithEmotionTag(EmotionTag);
	
	for (UEmotionComponent* Component : ComponentsWithTag)
	{
		if (Component && Component->GetOwner())
		{
			const FVector OwnerLocation = Component->GetOwner()->GetActorLocation();
			const float DistanceSq = FVector::DistSquared(Location, OwnerLocation);
			
			if (DistanceSq <= RadiusSq)
			{
				Result.Add(Component);
			}
		}
	}
	
	return Result;
}

TArray<UEmotionComponent*> UEmotionSubsystem::GetComponentsSortedByEmotionIntensity(const FGameplayTag& EmotionTag) const
{
	TArray<UEmotionComponent*> ComponentsWithTag = FindComponentsWithEmotionTag(EmotionTag);
	
	// Sort by intensity (highest first)
	ComponentsWithTag.Sort([EmotionTag](const UEmotionComponent& A, const UEmotionComponent& B) {
		return A.GetEmotionIntensity(EmotionTag) > B.GetEmotionIntensity(EmotionTag);
	});
	
	return ComponentsWithTag;
}

TArray<UEmotionComponent*> UEmotionSubsystem::FindComponentsInVARadius(const FVector2D& VACoordinate, float Radius) const
{
	TArray<UEmotionComponent*> Result;
	const float RadiusSq = Radius * Radius;
	
	TArray<UEmotionComponent*> AllComponents = GetValidComponents();
	
	for (UEmotionComponent* Component : AllComponents)
	{
		if (Component)
		{
			const FVector2D ComponentVA = Component->GetVACoordinate();
			const float DistanceSq = FVector2D::DistSquared(VACoordinate, ComponentVA);
			
			if (DistanceSq <= RadiusSq)
			{
				Result.Add(Component);
			}
		}
	}
	
	return Result;
}

UEmotionComponent* UEmotionSubsystem::FindClosestComponentToVACoordinate(const FVector2D& VACoordinate) const
{
	UEmotionComponent* ClosestComponent = nullptr;
	float ClosestDistanceSq = MAX_FLT;
	
	TArray<UEmotionComponent*> AllComponents = GetValidComponents();
	
	for (UEmotionComponent* Component : AllComponents)
	{
		if (Component)
		{
			const FVector2D ComponentVA = Component->GetVACoordinate();
			const float DistanceSq = FVector2D::DistSquared(VACoordinate, ComponentVA);
			
			if (DistanceSq < ClosestDistanceSq)
			{
				ClosestComponent = Component;
				ClosestDistanceSq = DistanceSq;
			}
		}
	}
	
	return ClosestComponent;
}

void UEmotionSubsystem::ApplyEmotionalInfluenceInRadius(AActor* Influencer, const FGameplayTag& EmotionTag, float Intensity, 
	const FVector& Location, float Radius, bool bAdditive)
{
	if (!Influencer || Intensity <= 0.0f || Radius <= 0.0f)
	{
		return;
	}
	
	TArray<UEmotionComponent*> AllComponents = GetValidComponents();
	const float RadiusSq = Radius * Radius;
	
	for (UEmotionComponent* Component : AllComponents)
	{
		if (Component && Component->GetOwner())
		{
			// Skip the influencer's own component if it has one
			if (Component->GetOwner() == Influencer)
			{
				continue;
			}
			
			const FVector OwnerLocation = Component->GetOwner()->GetActorLocation();
			const float DistanceSq = FVector::DistSquared(Location, OwnerLocation);
			
			if (DistanceSq <= RadiusSq)
			{
				// Calculate intensity falloff based on distance
				const float Distance = FMath::Sqrt(DistanceSq);
				const float DistanceRatio = 1.0f - FMath::Clamp(Distance / Radius, 0.0f, 1.0f);
				const float ScaledIntensity = Intensity * DistanceRatio;
				
				// Apply the influence
				Component->ReceiveEmotionalInfluence(Influencer, EmotionTag, ScaledIntensity, bAdditive);
			}
		}
	}
}

void UEmotionSubsystem::ApplyEmotionalInfluenceToTag(AActor* Influencer, const FGameplayTag& TargetTag, 
	const FGameplayTag& EmotionTag, float Intensity, bool bAdditive)
{
	if (!Influencer || Intensity <= 0.0f)
	{
		return;
	}
	
	TArray<UEmotionComponent*> ComponentsWithTag = FindComponentsWithEmotionTag(TargetTag);
	
	for (UEmotionComponent* Component : ComponentsWithTag)
	{
		if (Component && Component->GetOwner() != Influencer)
		{
			Component->ReceiveEmotionalInfluence(Influencer, EmotionTag, Intensity, bAdditive);
		}
	}
}

UEmotionLibrary* UEmotionSubsystem::GetDefaultEmotionLibrary() const
{
	return DefaultEmotionLibrary;
}

void UEmotionSubsystem::SetDefaultEmotionLibrary(UEmotionLibrary* NewLibrary)
{
	DefaultEmotionLibrary = NewLibrary;
}

void UEmotionSubsystem::DebugLogAllEmotions() const
{
	UE_LOG(LogTemp, Log, TEXT("===== EmotionSubsystem Debug Log ====="));
	UE_LOG(LogTemp, Log, TEXT("Registered Components: %d"), RegisteredComponents.Num());
	
	for (const TWeakObjectPtr<UEmotionComponent>& WeakComponent : RegisteredComponents)
	{
		if (WeakComponent.IsValid())
		{
			UEmotionComponent* Component = WeakComponent.Get();
			UE_LOG(LogTemp, Log, TEXT("- %s:"), *Component->GetOwnerName());
			
			// Log VA coordinate
			FVector2D VACoord = Component->GetVACoordinate();
			UE_LOG(LogTemp, Log, TEXT("  VA Coordinate: (%.2f, %.2f)"), VACoord.X, VACoord.Y);
			UE_LOG(LogTemp, Log, TEXT("  Influence Radius: %.2f"), Component->GetInfluenceRadius());
			
			// Log active emotions
			UE_LOG(LogTemp, Log, TEXT("  Active Emotions:"));
			TArray<FActiveEmotion> ActiveEmotions = Component->GetActiveEmotions();
			for (const FActiveEmotion& ActiveEmotion : ActiveEmotions)
			{
				if (ActiveEmotion.EmotionData)
				{
					UE_LOG(LogTemp, Log, TEXT("    * %s: %.2f"), 
						*ActiveEmotion.EmotionData->Emotion.Tag.ToString(), ActiveEmotion.Intensity);
				}
			}
			
			// Log all emotion tags
			UE_LOG(LogTemp, Log, TEXT("  All Emotion Tags:"));
			const FGameplayTagContainer& Tags = Component->GetAllEmotionTags();
			for (const FGameplayTag& Tag : Tags)
			{
				const float Intensity = Component->GetEmotionIntensity(Tag);
				UE_LOG(LogTemp, Log, TEXT("    * %s: %.2f"), *Tag.ToString(), Intensity);
			}
		}
	}
	
	UE_LOG(LogTemp, Log, TEXT("======================================"));
}

void UEmotionSubsystem::DebugVisualizeVACoordinates(float Duration) const
{
	// Only valid in a world context
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}
	
	// Create a 2D grid in the world to visualize VA space
	const FVector GridOrigin(0.0f, 0.0f, 100.0f); // Arbitrary position in the world
	const float GridSize = 200.0f; // Size of the grid in world units
	
	// Draw the grid axes
	DrawDebugLine(World, GridOrigin, GridOrigin + FVector(GridSize, 0.0f, 0.0f), FColor::Red, false, Duration, 0, 2.0f);
	DrawDebugLine(World, GridOrigin, GridOrigin + FVector(0.0f, GridSize, 0.0f), FColor::Green, false, Duration, 0, 2.0f);
	
	// Draw grid labels
	DrawDebugString(World, GridOrigin + FVector(GridSize, 0.0f, 0.0f), TEXT("Valence +"), nullptr, FColor::White, Duration);
	DrawDebugString(World, GridOrigin - FVector(GridSize / 2.0f, 0.0f, 0.0f), TEXT("Valence -"), nullptr, FColor::White, Duration);
	DrawDebugString(World, GridOrigin + FVector(0.0f, GridSize, 0.0f), TEXT("Arousal +"), nullptr, FColor::White, Duration);
	DrawDebugString(World, GridOrigin - FVector(0.0f, GridSize / 2.0f, 0.0f), TEXT("Arousal -"), nullptr, FColor::White, Duration);
	
	// Draw each component's VA coordinate as a sphere
	for (const TWeakObjectPtr<UEmotionComponent>& WeakComponent : RegisteredComponents)
	{
		if (WeakComponent.IsValid())
		{
			UEmotionComponent* Component = WeakComponent.Get();
			FVector2D VACoord = Component->GetVACoordinate();
			
			// Map VA coordinate (-1,1) to grid space
			FVector WorldPos = GridOrigin + FVector(VACoord.X * GridSize / 2.0f, VACoord.Y * GridSize / 2.0f, 0.0f);
			
			// Determine color based on dominant emotion
			FGameplayTag DominantTag;
			float DominantIntensity;
			Component->GetDominantEmotion(DominantTag, DominantIntensity);
			
			// TODO: Rework this to use emotion data's color instead
			FColor SphereColor = FColor::White;
			if (DominantTag == FGameplayTag::RequestGameplayTag(TEXT("Emotion.Joy")))
			{
				SphereColor = FColor::Yellow;
			}
			else if (DominantTag == FGameplayTag::RequestGameplayTag(TEXT("Emotion.Sadness")))
			{
				SphereColor = FColor::Blue;
			}
			else if (DominantTag == FGameplayTag::RequestGameplayTag(TEXT("Emotion.Anger")))
			{
				SphereColor = FColor::Red;
			}
			else if (DominantTag == FGameplayTag::RequestGameplayTag(TEXT("Emotion.Fear")))
			{
				SphereColor = FColor::Purple;
			}
			
			// Size based on influence radius
			float SphereSize = Component->GetInfluenceRadius() * 10.0f;
			SphereSize = FMath::Clamp(SphereSize, 5.0f, 50.0f);
			
			// Draw the sphere
			DrawDebugSphere(World, WorldPos, SphereSize, 8, SphereColor, false, Duration, 0, 1.0f);
			
			// Draw a label with the owner's name
			DrawDebugString(World, WorldPos, Component->GetOwnerName(), nullptr, FColor::White, Duration);
		}
	}
}

TArray<UEmotionComponent*> UEmotionSubsystem::FilterComponentsByTag(TFunctionRef<bool(UEmotionComponent*)> Predicate) const
{
	TArray<UEmotionComponent*> Result;
	
	for (const TWeakObjectPtr<UEmotionComponent>& WeakComponent : RegisteredComponents)
	{
		if (WeakComponent.IsValid())
		{
			UEmotionComponent* Component = WeakComponent.Get();
			if (Predicate(Component))
			{
				Result.Add(Component);
			}
		}
	}
	
	return Result;
}
