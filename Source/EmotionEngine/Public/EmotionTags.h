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

	// Joy variations (Secondary)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Joyful);       // Joy variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Interested);   // Joy variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Proud);        // Joy variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Accepted);     // Joy variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Powerful);     // Joy variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Peaceful);     // Joy variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Intimate);     // Joy variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Optimistic);   // Joy variation

	// Joy variations (Tertiary)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Amused);       // Joy.Interested variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Inquisitive);  // Joy.Interested variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Important);    // Joy.Proud variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Confidence);   // Joy.Proud variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Courageous);   // Joy.Powerful variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Provocative);  // Joy.Powerful variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Respected);    // Joy.Accepted variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Fulfilled);    // Joy.Accepted variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Hopeful);      // Joy.Peaceful variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Playful);      // Joy.Intimate variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Sensitive);    // Joy.Intimate variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Loving);       // Joy.Peaceful variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Inspired);     // Joy.Optimistic variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Open);         // Joy.Optimistic variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Ecstatic);     // Joy.Joyful variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Liberated);    // Joy.Joyful variation

	// Surprise variations
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Awe);          // Surprise variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Astonished);   // Surprise variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Perplexed);    // Surprise variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Disillusioned); // Surprise variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Dismayed);     // Surprise variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Shocked);      // Surprise variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Confused);     // Surprise variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Amazed);       // Surprise variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Excited);      // Surprise variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Startled);     // Surprise variation

	// Fear variations
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Terrified);    // Fear variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Frightened);   // Fear variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Overwhelmed);  // Fear variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Worried);      // Fear variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Inadequate);   // Fear variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Inferior);     // Fear variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Worthless);    // Fear variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Insignificant); // Fear variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Alienated);    // Fear variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Rejected);     // Fear variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Submissive);   // Fear variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Insecure);     // Fear variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Anxious);      // Fear variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Scared);       // Fear variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Humiliated);   // Fear variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Wounded);      // Fear variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Embarrassed);  // Fear variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Ridiculed);    // Fear variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Disrespected); // Fear variation

	// Anger variations
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Enraged);      // Anger variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Provoked);     // Anger variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Hostile);      // Anger variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Irritated);    // Anger variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Frustrated);   // Anger variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Aggressive);   // Anger variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Mad);          // Anger variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Hateful);      // Anger variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Threatened);   // Anger variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Distant);      // Anger variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Critical);     // Anger variation

	// Disgust variations
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Disapproval);  // Disgust variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Disappointed); // Disgust variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Awful);        // Disgust variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Avoidance);    // Disgust variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Aversion);     // Disgust variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Hesitant);     // Disgust variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Revolted);     // Disgust variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Repugnant);    // Disgust variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Loathing);     // Disgust variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Judgmental);   // Disgust variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Skeptical);    // Disgust variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Suspicious);   // Disgust variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Withdrawn);    // Disgust variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Repelled);     // Disgust variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Detestable);   // Disgust variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Revulsion);    // Disgust variation

	// Sad variations
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Lonely);       // Sad variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Vulnerable);   // Sad variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Despair);      // Sad variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Guilty);       // Sad variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Depressed);    // Sad variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Hurt);         // Sad variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Bored);        // Sad variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Apathetic);    // Sad variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Indifferent);  // Sad variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Diminished);   // Sad variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Empty);        // Sad variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Abandoned);    // Sad variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Isolated);     // Sad variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Powerless);    // Sad variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Victimized);   // Sad variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Ignored);      // Sad variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Ashamed);      // Sad variation
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Remorseful);   // Sad variation
	/**
	 * Helper function to register all emotion tags with the GameplayTags system
	 */
	void RegisterEmotionTags();
}
