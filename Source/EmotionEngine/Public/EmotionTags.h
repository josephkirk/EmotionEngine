// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * Gameplay tags for Plutchik's Wheel of Emotions
 */
namespace EmotionGameplayTags
{
	// Core emotions from Plutchik's Wheel
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Joy);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Trust);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Fear);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Surprise);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Sadness);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Disgust);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Anger);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Anticipation);

	// Emotion intensities (higher)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Ecstasy);      // Intense Joy
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Admiration);   // Intense Trust
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Terror);       // Intense Fear
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Amazement);    // Intense Surprise
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Grief);        // Intense Sadness
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Loathing);     // Intense Disgust
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Rage);         // Intense Anger
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Vigilance);    // Intense Anticipation

	// Emotion intensities (lower)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Serenity);     // Mild Joy
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Acceptance);   // Mild Trust
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Apprehension); // Mild Fear
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Distraction);  // Mild Surprise
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Pensiveness);  // Mild Sadness
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Boredom);      // Mild Disgust
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Annoyance);    // Mild Anger
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Interest);     // Mild Anticipation

	// Combined emotions (primary pairs)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Love);         // Joy + Trust
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Submission);   // Trust + Fear
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Awe);          // Fear + Surprise
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Disapproval);  // Surprise + Sadness
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Remorse);      // Sadness + Disgust
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Contempt);     // Disgust + Anger
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Aggressiveness); // Anger + Anticipation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Optimism);     // Anticipation + Joy

	/**
	 * Helper function to register all emotion tags with the GameplayTags system
	 */
	void RegisterEmotionTags();
}
