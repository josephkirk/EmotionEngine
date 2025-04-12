# Emotion Engine

An Unreal Engine plugin that provides a robust emotion system based on Plutchik's Wheel of Emotions for AI characters and gameplay mechanics.

## Overview

The Emotion Engine plugin implements a complete emotion system based on the psychological model of Plutchik's Wheel of Emotions. This plugin provides a framework for creating emotionally nuanced AI characters, NPCs, or any gameplay elements that can benefit from emotional states. The system includes components for managing individual entity emotions and a subsystem for tracking and querying emotional entities throughout the game world.

## Features

- Complete implementation of Plutchik's Wheel of Emotions using Unreal Engine's GameplayTag system
- Support for all core emotions: Joy, Trust, Fear, Surprise, Sadness, Disgust, Anger, Anticipation
- Intensity variations for each emotion (high and low intensity states)
- Combined emotions representing adjacent pairs on Plutchik's wheel
- Emotion state management system
- EmotionComponent for attaching emotions to any actor
- EmotionSubsystem for tracking and querying emotional entities
- EmotionInteractionInterface for objects to affect emotions of other actors
- EmotionInfluencer base class for creating emotion-affecting objects
- Spatial queries for finding entities with specific emotions
- Event-based notification system for emotion changes
- Support for emotional influence with distance-based falloff
- Configurable emotional susceptibility and immunity
- Blueprint-friendly API
- Easy integration with AI behavior trees and other systems

## Installation

1. Clone or copy the plugin to your project's `Plugins` directory
2. Enable the plugin in your project through the Plugins menu in the Unreal Editor
3. Add "EmotionEngine" to your project's dependencies in the build.cs file:

```csharp
PublicDependencyModuleNames.AddRange(
    new string[]
    {
        "Core",
        "EmotionEngine",
        // ... other dependencies
    }
);
```

## Plutchik's Wheel of Emotions

Robert Plutchik's psychoevolutionary theory of emotion proposes eight primary emotions arranged in opposing pairs:

- Joy vs. Sadness
- Trust vs. Disgust
- Fear vs. Anger
- Surprise vs. Anticipation

The model also accounts for variations in intensity and combinations of emotions:

- Each primary emotion has high and low intensity variants (e.g., Joy ranges from Serenity to Ecstasy)
- Adjacent emotions can combine to form more complex emotions (e.g., Joy + Trust = Love)

## Usage

### Accessing Emotion Tags

```cpp
// Include the necessary header
#include "EmotionTags.h"

// Access tags using the namespace
void MyFunction()
{
    // Use core emotion tags
    FGameplayTag joyTag = EmotionGameplayTags::Emotion_Joy;
    FGameplayTag fearTag = EmotionGameplayTags::Emotion_Fear;
    
    // Use intensity variants
    FGameplayTag ecstasyTag = EmotionGameplayTags::Emotion_Ecstasy; // High intensity Joy
    FGameplayTag serenityTag = EmotionGameplayTags::Emotion_Serenity; // Low intensity Joy
    
    // Use combined emotions
    FGameplayTag loveTag = EmotionGameplayTags::Emotion_Love; // Joy + Trust
}
```

### Using the EmotionComponent

```cpp
// Include the necessary headers
#include "EmotionComponent.h"
#include "EmotionTags.h"

// In your actor class
UEmotionComponent* EmotionComponent;

// In your actor's constructor
EmotionComponent = CreateDefaultSubobject<UEmotionComponent>(TEXT("EmotionComponent"));

// Add emotions to your actor
EmotionComponent->AddCoreEmotion(EmotionGameplayTags::Emotion_Joy, 0.7f);
EmotionComponent->AddCoreEmotion(EmotionGameplayTags::Emotion_Fear, 0.3f);

// Get the intensity of an emotion
float joyIntensity = EmotionComponent->GetEmotionIntensity(EmotionGameplayTags::Emotion_Joy);

// Change the intensity of an existing emotion
EmotionComponent->SetEmotionIntensity(EmotionGameplayTags::Emotion_Joy, 0.9f);

// Remove an emotion
EmotionComponent->RemoveCoreEmotion(EmotionGameplayTags::Emotion_Fear);

// Get the dominant emotion
FGameplayTag dominantEmotion;
float dominantIntensity;
EmotionComponent->GetDominantEmotion(dominantEmotion, dominantIntensity);

// Listen for emotion changes
EmotionComponent->OnEmotionChanged.AddDynamic(this, &YourClass::OnEmotionChanged);

// Emotion change callback
void YourClass::OnEmotionChanged(const FGameplayTag& EmotionTag, float Intensity)
{
    // React to emotion changes
}
```

### Using the EmotionSubsystem

```cpp
// Include the necessary headers
#include "EmotionSubsystem.h"
#include "EmotionTags.h"

// Get the subsystem from the world
UWorld* World = GetWorld();
UEmotionSubsystem* EmotionSubsystem = World->GetSubsystem<UEmotionSubsystem>();

// Find all actors with a specific emotion
TArray<UEmotionComponent*> AngryActors = 
    EmotionSubsystem->FindComponentsWithEmotionTag(EmotionGameplayTags::Emotion_Anger);

// Find the closest actor with a specific emotion
FVector MyLocation = GetActorLocation();
UEmotionComponent* ClosestAngryActor = 
    EmotionSubsystem->FindClosestComponentWithEmotionTag(EmotionGameplayTags::Emotion_Anger, MyLocation);

// Find all actors with a specific emotion within a radius
TArray<UEmotionComponent*> NearbyHappyActors = 
    EmotionSubsystem->FindComponentsWithEmotionTagInRadius(EmotionGameplayTags::Emotion_Joy, MyLocation, 1000.0f);

// Get actors sorted by emotion intensity (highest first)
TArray<UEmotionComponent*> SortedByFear = 
    EmotionSubsystem->GetComponentsSortedByEmotionIntensity(EmotionGameplayTags::Emotion_Fear);
```

### Using the Emotion Interaction Interface

```cpp
// Include the necessary headers
#include "EmotionInteractionInterface.h"
#include "EmotionComponent.h"

// Implement the interface in your class
class MYGAME_API AEmotionalObject : public AActor, public IEmotionInteractionInterface
{
    GENERATED_BODY()
    
    // Implement the interface methods
    virtual bool ApplyEmotionToTarget_Implementation(AActor* TargetActor, 
        const FGameplayTag& EmotionTag, float Intensity, bool bAdditive) override;
    virtual int32 ApplyEmotionInRadius_Implementation(const FVector& Origin, float Radius, 
        const FGameplayTag& EmotionTag, float Intensity, bool bAdditive, bool bRequiresLineOfSight) override;
    virtual float GetEmotionalInfluenceStrength_Implementation() const override;
    virtual FGameplayTagContainer GetAvailableEmotions_Implementation() const override;
};

// Example implementation
bool AEmotionalObject::ApplyEmotionToTarget_Implementation(AActor* TargetActor, 
    const FGameplayTag& EmotionTag, float Intensity, bool bAdditive)
{
    // Find the emotion component on the target
    UEmotionComponent* EmotionComp = TargetActor->FindComponentByClass<UEmotionComponent>();
    if (EmotionComp)
    {
        // Apply the emotion influence
        return EmotionComp->ReceiveEmotionalInfluence(this, EmotionTag, Intensity, bAdditive);
    }
    return false;
}
```

### Using the EmotionInfluencer Base Class

```cpp
// Include the necessary header
#include "EmotionInfluencer.h"

// Create a derived class
class MYGAME_API AMyEmotionalObject : public AEmotionInfluencer
{
    GENERATED_BODY()
    
    AMyEmotionalObject()
    {
        // Set up available emotions
        AvailableEmotions.AddTag(EmotionGameplayTags::Emotion_Joy);
        AvailableEmotions.AddTag(EmotionGameplayTags::Emotion_Fear);
        
        // Set influence strength
        EmotionalInfluenceStrength = 1.5f;
    }
    
    // Trigger an emotional effect
    void TriggerEmotionalEffect()
    {
        // Apply to a specific target
        AActor* Target = GetSomeTargetActor();
        ApplyEmotionToTarget(Target, EmotionGameplayTags::Emotion_Joy, 0.8f, true);
        
        // Apply to all actors in radius
        ApplyEmotionInRadius(GetActorLocation(), 500.0f, 
            EmotionGameplayTags::Emotion_Fear, 0.6f, true, true);
            
        // Apply with distance-based falloff
        ApplyEmotionWithFalloff(Target, EmotionGameplayTags::Emotion_Joy, 1.0f, 1000.0f);
    }
};
```

### Managing Emotion States Directly

```cpp
// Include the necessary header
#include "EmotionState.h"

// Create an emotion state and add emotions
FEmotionState myCharacterEmotionState;

// Add core emotions with intensity values (0.0 to 1.0)
myCharacterEmotionState.AddCoreEmotionTag(EmotionGameplayTags::Emotion_Joy, 0.7f);
myCharacterEmotionState.AddCoreEmotionTag(EmotionGameplayTags::Emotion_Fear, 0.3f);

// Get the intensity of an emotion
float joyIntensity = myCharacterEmotionState.GetIntensity(EmotionGameplayTags::Emotion_Joy); // Returns 0.7

// Change the intensity of an existing emotion
myCharacterEmotionState.SetIntensity(EmotionGameplayTags::Emotion_Joy, 0.9f);

// Remove an emotion
myCharacterEmotionState.RemoveCoreEmotionTag(EmotionGameplayTags::Emotion_Fear);
```

## Blueprint Usage

The plugin provides Blueprint-friendly components and functions:

### Using EmotionComponent in Blueprints

1. Add the EmotionComponent to any actor through the Components panel
2. Use the AddCoreEmotion, SetEmotionIntensity, and RemoveCoreEmotion functions to manage emotions
3. Get emotion intensities with GetEmotionIntensity
4. Bind to the OnEmotionChanged event to react to emotion changes
5. Use the GetDominantEmotion function to find the strongest emotion
6. Configure EmotionalSusceptibility to control how strongly the actor is affected by influences
7. Set up ImmuneEmotions to make the actor immune to specific emotion types

### Using EmotionSubsystem in Blueprints

1. Get the EmotionSubsystem from the current world
2. Use FindComponentsWithEmotionTag to find actors with specific emotions
3. Use FindClosestComponentWithEmotionTag for proximity-based emotion queries
4. Use FindComponentsWithEmotionTagInRadius for area-based emotion queries
5. Use GetComponentsSortedByEmotionIntensity to sort actors by emotion strength

### Creating Emotion Influencers in Blueprints

1. Create a new Blueprint based on the EmotionInfluencer class
2. Configure the AvailableEmotions and EmotionalInfluenceStrength properties
3. Call ApplyEmotionToTarget to affect a specific actor's emotions
4. Call ApplyEmotionInRadius to affect all actors within a radius
5. Use ApplyEmotionWithFalloff for distance-based emotional effects
6. Implement custom logic to trigger emotional effects based on game events

### Emotion-Driven AI

1. Use emotion tags and intensities to drive behavior in AI behavior trees
2. Create emotion-based conditions for AI decision making
3. Trigger animations based on emotional states
4. Implement emotional contagion between NPCs using the subsystem

## License

This plugin is available under the MIT License. See the LICENSE file for details.

## Credits

- Based on Robert Plutchik's psychoevolutionary theory of emotion
- Developed for Unreal Engine 5.x
