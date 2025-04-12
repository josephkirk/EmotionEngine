// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
#include "GameplayTagContainer.h"

/**
 * Gameplay tags for Plutchik's Wheel of Emotions
 */
namespace EmotionGameplayTags
{
	// Core emotions from Plutchik's Wheel
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Joy);
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Trust);
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Fear);
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Surprise);
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Sadness);
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Disgust);
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Anger);
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Anticipation);

	// Emotion intensities (higher)
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Ecstasy);      // Intense Joy
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Admiration);   // Intense Trust
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Terror);       // Intense Fear
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Amazement);    // Intense Surprise
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Grief);        // Intense Sadness
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Loathing);     // Intense Disgust
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Rage);         // Intense Anger
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Vigilance);    // Intense Anticipation

	// Emotion intensities (lower)
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Serenity);     // Mild Joy
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Acceptance);   // Mild Trust
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Apprehension); // Mild Fear
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Distraction);  // Mild Surprise
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Pensiveness);  // Mild Sadness
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Boredom);      // Mild Disgust
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Annoyance);    // Mild Anger
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Interest);     // Mild Anticipation

	// Combined emotions (primary pairs)
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Love);         // Joy + Trust
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Submission);   // Trust + Fear
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Awe);          // Fear + Surprise
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Disapproval);  // Surprise + Sadness
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Remorse);      // Sadness + Disgust
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Contempt);     // Disgust + Anger
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Aggressiveness); // Anger + Anticipation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Optimism);     // Anticipation + Joy

	// Joy variations (Secondary)
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Joyful);       // Joy variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Interested);   // Joy variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Proud);        // Joy variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Accepted);     // Joy variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Powerful);     // Joy variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Peaceful);     // Joy variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Intimate);     // Joy variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Optimistic);   // Joy variation

	// Joy variations (Tertiary)
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Amused);       // Joy.Interested variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Inquisitive);  // Joy.Interested variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Important);    // Joy.Proud variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Confidence);   // Joy.Proud variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Courageous);   // Joy.Powerful variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Provocative);  // Joy.Powerful variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Respected);    // Joy.Accepted variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Fulfilled);    // Joy.Accepted variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Hopeful);      // Joy.Peaceful variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Playful);      // Joy.Intimate variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Sensitive);    // Joy.Intimate variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Loving);       // Joy.Peaceful variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Inspired);     // Joy.Optimistic variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Open);         // Joy.Optimistic variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Ecstatic);     // Joy.Joyful variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Liberated);    // Joy.Joyful variation

	// Surprise variations (Secondary)
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Startled);     // Surprise variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Confused);     // Surprise variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Amazed);       // Surprise variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Astonished);   // Surprise variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Shocked);      // Surprise variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Dismayed);     // Surprise variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Disillusioned); // Surprise variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Perplexed);    // Surprise variation

	// Surprise variations (Tertiary)
	//UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Awe);          // Surprise.Amazed variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Excited);      // Surprise.Amazed variation

	// Fear variations (Secondary)
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Scared);       // Fear variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Anxious);      // Fear variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Insecure);     // Fear variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Submissive);   // Fear variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Rejected);     // Fear variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Inadequate);   // Fear variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Worried);      // Fear variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Frightened);   // Fear variation

	// Fear variations (Tertiary)
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Terrified);    // Fear.Frightened variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Overwhelmed);  // Fear.Worried variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Inferior);     // Fear.Inadequate variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Worthless);    // Fear.Inadequate variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Insignificant); // Fear.Inadequate variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Alienated);    // Fear.Rejected variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Humiliated);   // Fear.Rejected variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Wounded);      // Fear.Rejected variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Embarrassed);  // Fear.Insecure variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Ridiculed);    // Fear.Insecure variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Disrespected); // Fear.Insecure variation

	// Anger variations (Secondary)
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Mad);          // Anger variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Irritated);    // Anger variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Frustrated);   // Anger variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Distant);      // Anger variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Critical);     // Anger variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Hostile);      // Anger variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Aggressive);   // Anger variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Provoked);     // Anger variation

	// Anger variations (Tertiary)
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Enraged);      // Anger.Mad variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Hateful);      // Anger.Hostile variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Threatened);   // Anger.Provoked variation

	// Disgust variations (Secondary)
	//UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Disapproval);  // Disgust variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Disappointed); // Disgust variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Awful);        // Disgust variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Avoidance);    // Disgust variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Hesitant);     // Disgust variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Judgmental);   // Disgust variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Revolted);     // Disgust variation
	//UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Loathing);     // Disgust variation

	// Disgust variations (Tertiary)
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Skeptical);    // Disgust.Judgmental variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Suspicious);   // Disgust.Judgmental variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Withdrawn);    // Disgust.Avoidance variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Aversion);     // Disgust.Avoidance variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Repelled);     // Disgust.Revolted variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Repugnant);    // Disgust.Revolted variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Detestable);   // Disgust.Loathing variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Revulsion);    // Disgust.Loathing variation

	// Sad variations (Secondary)
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Lonely);       // Sad variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Vulnerable);   // Sad variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Depressed);    // Sad variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Hurt);         // Sad variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Guilty);       // Sad variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Despair);      // Sad variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Bored);        // Sad variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Empty);        // Sad variation

	// Sad variations (Tertiary)
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Isolated);     // Sad.Lonely variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Abandoned);    // Sad.Lonely variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Powerless);    // Sad.Vulnerable variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Victimized);   // Sad.Vulnerable variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Ashamed);      // Sad.Guilty variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Remorseful);   // Sad.Guilty variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Ignored);      // Sad.Hurt variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Diminished);   // Sad.Hurt variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Apathetic);    // Sad.Bored variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Indifferent);  // Sad.Bored variation
	/**
	 * Helper function to register all emotion tags with the GameplayTags system
	 */

	EMOTIONENGINE_API extern const TMap<FGameplayTag, FGameplayTagContainer> EmotionTagMap;
	void RegisterEmotionTags();
}
