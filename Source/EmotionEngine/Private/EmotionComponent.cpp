#include "EmotionComponent.h"
#include "EmotionSubsystem.h"

// Sets default values for this component's properties
UEmotionComponent::UEmotionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UEmotionComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// Register with the EmotionSubsystem
	if (UWorld* World = GetWorld())
	{
		if (UEmotionSubsystem* EmotionSubsystem = World->GetSubsystem<UEmotionSubsystem>())
		{
			EmotionSubsystem->RegisterEmotionComponent(this);
		}
	}
}

void UEmotionComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// Unregister from the EmotionSubsystem
	if (UWorld* World = GetWorld())
	{
		if (UEmotionSubsystem* EmotionSubsystem = World->GetSubsystem<UEmotionSubsystem>())
		{
			EmotionSubsystem->UnregisterEmotionComponent(this);
		}
	}
	
	Super::EndPlay(EndPlayReason);
}

void UEmotionComponent::AddCoreEmotion(const FGameplayTag& EmotionTag, float Intensity)
{
	// Store previous intensity for change detection
	float PreviousIntensity = EmotionState.GetIntensity(EmotionTag);
	
	// Add the emotion to the state
	EmotionState.AddCoreEmotionTag(EmotionTag, Intensity);
	
	// Notify listeners if intensity changed
	if (!FMath::IsNearlyEqual(PreviousIntensity, Intensity))
	{
		BroadcastEmotionChanged(EmotionTag, Intensity);
	}
}

void UEmotionComponent::RemoveCoreEmotion(const FGameplayTag& EmotionTag)
{
	// Store previous intensity for change detection
	float PreviousIntensity = EmotionState.GetIntensity(EmotionTag);
	
	// Only broadcast if the emotion actually existed
	bool bShouldBroadcast = (PreviousIntensity != 0.0f);
	
	// Remove the emotion from the state
	EmotionState.RemoveCoreEmotionTag(EmotionTag);
	
	// Notify listeners if the emotion was removed
	if (bShouldBroadcast)
	{
		BroadcastEmotionChanged(EmotionTag, 0.0f);
	}
}

void UEmotionComponent::SetEmotionIntensity(const FGameplayTag& EmotionTag, float Intensity)
{
	// Store previous intensity for change detection
	float PreviousIntensity = EmotionState.GetIntensity(EmotionTag);
	
	// Set the intensity in the emotion state
	EmotionState.SetIntensity(EmotionTag, Intensity);
	
	// Notify listeners if intensity changed
	if (!FMath::IsNearlyEqual(PreviousIntensity, Intensity))
	{
		BroadcastEmotionChanged(EmotionTag, Intensity);
	}
}

float UEmotionComponent::GetEmotionIntensity(const FGameplayTag& EmotionTag) const
{
	return EmotionState.GetIntensity(EmotionTag);
}

bool UEmotionComponent::HasEmotionTag(const FGameplayTag& EmotionTag) const
{
	return EmotionState.EmotionTags.HasTag(EmotionTag);
}

FGameplayTagContainer UEmotionComponent::GetAllEmotionTags() const
{
	return EmotionState.EmotionTags;
}

void UEmotionComponent::GetDominantEmotion(FGameplayTag& OutEmotionTag, float& OutIntensity) const
{
	OutEmotionTag = FGameplayTag::EmptyTag;
	OutIntensity = 0.0f;
	
	// Iterate through all emotion tags to find the one with highest intensity
	for (const FGameplayTag& Tag : EmotionState.EmotionTags)
	{
		float TagIntensity = EmotionState.GetIntensity(Tag);
		if (TagIntensity > OutIntensity)
		{
			OutEmotionTag = Tag;
			OutIntensity = TagIntensity;
		}
	}
}

FString UEmotionComponent::GetOwnerName() const
{
	if (AActor* OwningActor = GetOwner())
	{
		return OwningActor->GetName();
	}
	return TEXT("Unknown");
}

void UEmotionComponent::BroadcastEmotionChanged(const FGameplayTag& EmotionTag, float Intensity)
{
	// Broadcast the emotion change event
	OnEmotionChanged.Broadcast(EmotionTag, Intensity);
	
	// Also notify the subsystem about the change
	if (UWorld* World = GetWorld())
	{
		if (UEmotionSubsystem* EmotionSubsystem = World->GetSubsystem<UEmotionSubsystem>())
		{
			EmotionSubsystem->NotifyEmotionChanged(this, EmotionTag, Intensity);
		}
	}
}
