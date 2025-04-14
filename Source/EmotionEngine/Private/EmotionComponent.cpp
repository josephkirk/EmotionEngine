#include "EmotionComponent.h"
#include "EmotionSubsystem.h"
#include "Kismet/GameplayStatics.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(EmotionComponent)

// Sets default values for this component's properties
UEmotionComponent::UEmotionComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame
	PrimaryComponentTick.bCanEverTick = true;
	EmotionState = CreateDefaultSubobject<UEmotionState>(TEXT("EmotionState"));
	
	// Default values
	EmotionalSusceptibility = 1.0f;
	SpringStiffness = 2.0f;
	DampingFactor = 0.5f;
}

// Called when the game starts
void UEmotionComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// Initialize the emotion state
	InitializeEmotionState();
	
	// Register with the EmotionSubsystem
	if (UWorld* World = GetWorld())
	{
		if (UEmotionSubsystem* EmotionSubsystem = World->GetSubsystem<UEmotionSubsystem>())
		{
			EmotionSubsystem->RegisterEmotionComponent(this);
		}
	}
}

// Called every frame
void UEmotionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// Update the emotion state
	if (EmotionState)
	{
		EmotionState->Tick(DeltaTime);
		
		// Get the previous VA coordinate for change detection
		FVector2D PreviousVA = EmotionState->VACoordinate;
		
		// If VA coordinate changed significantly, broadcast the change
		if (!PreviousVA.Equals(EmotionState->VACoordinate, 0.01f))
		{
			BroadcastVACoordinateChanged(EmotionState->VACoordinate);
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

void UEmotionComponent::AddEmotion(const FGameplayTag& EmotionTag, float Intensity)
{
	// Ensure the emotion state is initialized
	InitializeEmotionState();
	
	// Store previous intensity for change detection
	float PreviousIntensity = EmotionState->GetIntensity(EmotionTag);
	
	// Add the emotion to the state
	EmotionState->AddEmotion(EmotionTag, Intensity);
	
	// Notify listeners if intensity changed
	if (!FMath::IsNearlyEqual(PreviousIntensity, EmotionState->GetIntensity(EmotionTag)))
	{
		BroadcastEmotionChanged(EmotionTag, EmotionState->GetIntensity(EmotionTag));
	}
}

void UEmotionComponent::RemoveEmotion(const FGameplayTag& EmotionTag)
{
	// Ensure the emotion state is initialized
	InitializeEmotionState();
	
	// Store previous intensity for change detection
	float PreviousIntensity = EmotionState->GetIntensity(EmotionTag);
	
	// Only broadcast if the emotion actually existed
	bool bShouldBroadcast = (PreviousIntensity > 0.0f);
	
	// Remove the emotion from the state
	EmotionState->RemoveEmotion(EmotionTag);
	
	// Notify listeners if the emotion was removed
	if (bShouldBroadcast)
	{
		BroadcastEmotionChanged(EmotionTag, 0.0f);
	}
}

void UEmotionComponent::SetEmotionIntensity(const FGameplayTag& EmotionTag, float Intensity)
{
	// Ensure the emotion state is initialized
	InitializeEmotionState();
	
	// Store previous intensity for change detection
	float PreviousIntensity = EmotionState->GetIntensity(EmotionTag);
	
	// Set the intensity in the emotion state
	EmotionState->SetIntensity(EmotionTag, Intensity);
	
	// Notify listeners if intensity changed
	if (!FMath::IsNearlyEqual(PreviousIntensity, EmotionState->GetIntensity(EmotionTag)))
	{
		BroadcastEmotionChanged(EmotionTag, EmotionState->GetIntensity(EmotionTag));
	}
}

float UEmotionComponent::GetEmotionIntensity(const FGameplayTag& EmotionTag) const
{
	if (!EmotionState)
	{
		return 0.0f;
	}
	return EmotionState->GetIntensity(EmotionTag);
}

bool UEmotionComponent::HasEmotionTag(const FGameplayTag& EmotionTag) const
{
	if (!EmotionState)
	{
		return false;
	}
	return EmotionState->EmotionTags.HasTag(EmotionTag);
}

FGameplayTagContainer UEmotionComponent::GetAllEmotionTags() const
{
	if (!EmotionState)
	{
		return FGameplayTagContainer();
	}
	return EmotionState->EmotionTags;
}

TArray<FActiveEmotion> UEmotionComponent::GetActiveEmotions() const
{
	if (!EmotionState)
	{
		return TArray<FActiveEmotion>();
	}
	return EmotionState->GetActiveEmotions();
}

void UEmotionComponent::GetDominantEmotion(FGameplayTag& OutEmotionTag, float& OutIntensity) const
{
	if (!EmotionState)
	{
		OutEmotionTag = FGameplayTag::EmptyTag;
		OutIntensity = 0.0f;
		return;
	}
	
	EmotionState->GetDominantEmotion(OutEmotionTag, OutIntensity);
}

FVector2D UEmotionComponent::GetVACoordinate() const
{
	if (!EmotionState)
	{
		return FVector2D::ZeroVector;
	}
	return EmotionState->VACoordinate;
}

void UEmotionComponent::SetVACoordinate(const FVector2D& NewVACoordinate)
{
	// Ensure the emotion state is initialized
	InitializeEmotionState();
	
	// Store previous coordinate for change detection
	FVector2D PreviousVA = EmotionState->VACoordinate;
	
	// Set the new coordinate
	EmotionState->VACoordinate = NewVACoordinate;
	
	// Notify listeners if coordinate changed
	if (!PreviousVA.Equals(NewVACoordinate, 0.01f))
	{
		BroadcastVACoordinateChanged(NewVACoordinate);
	}
}

float UEmotionComponent::GetInfluenceRadius() const
{
	if (!EmotionState)
	{
		return 0.0f;
	}
	return EmotionState->InfluenceRadius;
}

void UEmotionComponent::SetInfluenceRadius(float NewRadius)
{
	// Ensure the emotion state is initialized
	InitializeEmotionState();
	
	// Set the new radius
	EmotionState->InfluenceRadius = FMath::Max(0.0f, NewRadius);
}

TArray<UEmotionData*> UEmotionComponent::FindEmotionsInRadius(float Radius) const
{
	if (!EmotionState)
	{
		return TArray<UEmotionData*>();
	}
	return EmotionState->FindEmotionsInRadius(Radius);
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

void UEmotionComponent::BroadcastVACoordinateChanged(const FVector2D& NewVACoordinate)
{
	// Broadcast the VA coordinate change event
	OnVACoordinateChanged.Broadcast(NewVACoordinate);
}

void UEmotionComponent::BroadcastEmotionalInfluence(AActor* Influencer, const FGameplayTag& EmotionTag, float Intensity)
{
	// Broadcast the emotional influence event
	OnEmotionalInfluence.Broadcast(Influencer, EmotionTag, Intensity);
}

bool UEmotionComponent::ReceiveEmotionalInfluence(AActor* Influencer, const FGameplayTag& EmotionTag, float Intensity, bool bAdditive)
{
	// Validate parameters
	if (!Influencer || !EmotionTag.IsValid())
	{
		return false;
	}
	
	// Check if this component can be influenced by the given actor
	if (!CanReceiveInfluenceFrom(Influencer))
	{
		return false;
	}
	
	// Check if this component is immune to the given emotion
	if (ImmuneEmotions.HasTag(EmotionTag))
	{
		return false;
	}
	
	// Apply susceptibility modifier
	float ModifiedIntensity = Intensity * EmotionalSusceptibility;
	
	// Apply the emotion
	if (bAdditive)
	{
		// Get current intensity and add to it
		float CurrentIntensity = GetEmotionIntensity(EmotionTag);
		SetEmotionIntensity(EmotionTag, CurrentIntensity + ModifiedIntensity);
	}
	else
	{
		// Set directly if not additive
		SetEmotionIntensity(EmotionTag, ModifiedIntensity);
	}
	
	// Broadcast that this component received an influence
	BroadcastEmotionalInfluence(Influencer, EmotionTag, ModifiedIntensity);
	
	return true;
}

void UEmotionComponent::ApplyEmotionalStimulus(const FGameplayTag& EmotionTag, float Intensity)
{
	// Ensure the emotion state is initialized
	InitializeEmotionState();
	
	// Apply the emotion directly without influence checks
	AddEmotion(EmotionTag, Intensity);
}

void UEmotionComponent::SetEmotionalSusceptibility(float NewSusceptibility)
{
	EmotionalSusceptibility = FMath::Max(0.0f, NewSusceptibility);
}

bool UEmotionComponent::CanReceiveInfluenceFrom(AActor* Influencer) const
{
	if (!Influencer)
	{
		return false;
	}
	
	// Check if the influencer is in the blocked list
	for (TSubclassOf<AActor> BlockedClass : BlockedInfluencers)
	{
		if (BlockedClass && Influencer->IsA(BlockedClass))
		{
			return false;
		}
	}
	
	// If allowed list is empty, all non-blocked actors are allowed
	if (AllowedInfluencers.Num() == 0)
	{
		return true;
	}
	
	// Check if the influencer is in the allowed list
	for (TSubclassOf<AActor> AllowedClass : AllowedInfluencers)
	{
		if (AllowedClass && Influencer->IsA(AllowedClass))
		{
			return true;
		}
	}
	
	// Not in allowed list
	return false;
}

void UEmotionComponent::InitializeEmotionState()
{
	if (!EmotionState)
	{
		EmotionState = NewObject<UEmotionState>(this, TEXT("EmotionState"));
	}
	
	if (EmotionState && EmotionLibrary)
	{
		EmotionState->Initialize(EmotionLibrary);
	}
	else if (EmotionState)
	{
		// Try to find a default emotion library from the game instance or other global source
		if (UWorld* World = GetWorld())
		{
			if (UEmotionSubsystem* EmotionSubsystem = World->GetSubsystem<UEmotionSubsystem>())
			{
				// Assuming the subsystem has a method to get a default emotion library
				// This would need to be implemented in the EmotionSubsystem class
				// UEmotionLibrary* DefaultLibrary = EmotionSubsystem->GetDefaultEmotionLibrary();
				// if (DefaultLibrary)
				// {
				//     EmotionState->Initialize(DefaultLibrary);
				// }
			}
		}
	}
}
