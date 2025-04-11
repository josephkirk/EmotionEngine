#include "EmotionSubsystem.h"
#include "EmotionComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

void UEmotionSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	// Initialize the subsystem
	UE_LOG(LogTemp, Log, TEXT("EmotionSubsystem initialized"));
}

void UEmotionSubsystem::Deinitialize()
{
	// Clear all registered components
	RegisteredComponents.Empty();
	
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
	}
}

TArray<UEmotionComponent*> UEmotionSubsystem::GetAllEmotionComponents() const
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
			
			const FGameplayTagContainer& Tags = Component->GetAllEmotionTags();
			for (const FGameplayTag& Tag : Tags)
			{
				const float Intensity = Component->GetEmotionIntensity(Tag);
				UE_LOG(LogTemp, Log, TEXT("  * %s: %.2f"), *Tag.ToString(), Intensity);
			}
		}
	}
	
	UE_LOG(LogTemp, Log, TEXT("======================================"));
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
