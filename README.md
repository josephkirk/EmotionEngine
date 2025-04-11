# Emotion Engine

An Unreal Engine plugin that provides a robust emotion system based on Plutchik's Wheel of Emotions for AI characters and gameplay mechanics.

## Overview

The Emotion Engine plugin implements a complete emotion system based on the psychological model of Plutchik's Wheel of Emotions. This plugin provides a framework for creating emotionally nuanced AI characters, NPCs, or any gameplay elements that can benefit from emotional states.

## Features

- Complete implementation of Plutchik's Wheel of Emotions using Unreal Engine's GameplayTag system
- Support for all core emotions: Joy, Trust, Fear, Surprise, Sadness, Disgust, Anger, Anticipation
- Intensity variations for each emotion (high and low intensity states)
- Combined emotions representing adjacent pairs on Plutchik's wheel
- Emotion state management system
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

### Managing Emotion States

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

The plugin provides Blueprint-friendly functions to work with emotion states:

1. Create an Emotion State variable in your character or AI controller
2. Use the AddCoreEmotionTag, SetIntensity, and RemoveCoreEmotionTag functions to manage emotions
3. Get emotion intensities with GetIntensity
4. Use emotion tags to drive behavior in AI behavior trees or animation blueprints

## License

This plugin is available under the MIT License. See the LICENSE file for details.

## Credits

- Based on Robert Plutchik's psychoevolutionary theory of emotion
- Developed for Unreal Engine 5.x
