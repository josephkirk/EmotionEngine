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
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Core_Joy);
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Core_Trust);
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Core_Fear);
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Core_Surprise);
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Core_Sadness);
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Core_Disgust);
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Core_Anger);
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Core_Anticipation);

	// Core Emotion intensities (higher)
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Range_Ecstasy);      // Intense Joy
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Range_Admiration);   // Intense Trust
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Range_Terror);       // Intense Fear
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Range_Amazement);    // Intense Surprise
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Range_Grief);        // Intense Sadness
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Range_Loathing);     // Intense Disgust
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Range_Rage);         // Intense Anger
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Range_Vigilance);    // Intense Anticipation

	// Core Emotion intensities (lower)
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Range_Serenity);     // Mild Joy
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Range_Acceptance);   // Mild Trust
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Range_Apprehension); // Mild Fear
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Range_Distraction);  // Mild Surprise
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Range_Pensiveness);  // Mild Sadness
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Range_Boredom);      // Mild Disgust
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Range_Annoyance);    // Mild Anger
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Range_Interest);     // Mild Anticipation

	// Combined emotions (primary pairs)
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Combined_Love);         // Joy + Trust
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Combined_Guilt);         // Joy + Fear
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Combined_Delight);         // Joy + Suprise
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Combined_Optimism);     // Joy + Anticipation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Combined_Morbidness);     // Joy + Disgust
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Combined_Submission);   // Trust + Fear
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Combined_Sentimentality);   // Trust + Sadness
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Combined_Hope);   // Trust + Anticipation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Combined_Dominance);   // Trust + Anger
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Combined_Awe);          // Fear + Surprise
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Combined_Anxiety);          // Fear + Anticipation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Combined_Despair);          // Fear + Sadness
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Combined_Shame);          // Fear + Disgust
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Combined_Disapproval);  // Surprise + Sadness
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Combined_Unbelief);  // Surprise + Disgust
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Combined_Outrage);  // Surprise + Anger
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Combined_Remorse);      // Sadness + Disgust
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Combined_Envy);      // Sadness + Anger
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Combined_Pessimism);      // Sadness + Anticipation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Combined_Contempt);     // Disgust + Anger
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Combined_Cynicism);      // Digust + Anticipation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Combined_Aggressiveness); // Anger + Anticipation
	
	// Combined emotions range
	// Love
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Range_Rapture);     // Love High
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Range_Affection);     // Love Low

	// Guilt
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Range_Remorse);     // Guilt High
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Range_Compunction);     // Guilt Low

	// Delight
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Range_Glee);     // Delight High
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Range_Contentment);     // Delight Low

	// Optimism
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Range_Exuberance);     // Optimism High
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Range_Hopefulness);     // Optimism Low

	// Morbidness
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Range_Ghastliness);     // Morbidness High
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Range_Somberness);     // Morbidness Low

	// Submission
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Range_Servility);     // Submission High
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Range_Acquiescence);     // Submission Low

	// Sentimentality
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Range_Mawkishness);     // Sentimentality High
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Range_Wishfulness);     // Sentimentality Low

	// Hope
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Range_Faith);     // Hope High
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Range_Optimistic);     // Hope Low

	// Dominance
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Range_Powerlust);     // Dominance High
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Range_Authority);     // Dominance Low

	// Awe
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Range_Reverence);     // Awe High
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Range_Curiosity);     // Awe Low

	// Anxiety
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Range_Worry);     // Anxiety High
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Range_Nervousness);     // Anxiety Low

	// Despair
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Range_Dread);     // Despair High
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Range_Gloom);     // Despair Low

	// Shame
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Range_SelfLoathing);     // Shame High
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Range_Embarassment);     // Shame Low

	// Disapproval
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Range_Comdemnation);     // Disapproval High
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Range_Doubt);     // Disapproval Low

	// Unbelief
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Range_Incredulity);     // Unbelief High
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Range_Dismissal);     // Unbelief Low

	// Outrage
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Range_Indignation);     // Outrage High
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Range_Irritation);     // Outrage Low

	// Remorse
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Range_Repentance);     // Remorse High
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Range_Regret);     // Remorse Low

	// Envy
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Range_Spite);     // Envy High
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Range_Jealousy);     // Envy Low

	// Perssimism
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Range_Resignation);     // Perssimism High
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Range_Discouragement);     // Perssimism Low

	// Contempt
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Range_Scorn);     // Contempt High
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Range_Disdain);     // Contempt Low

	// Cynicism
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Range_Misanthropy);     // Cynicism High
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Range_Skepticism);     // Cynicism Low

	// Aggressiveness
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Range_Ruthlessness);     // Aggressiveness High
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Range_Contention);     // Aggressiveness Low

	// Joy variations (Secondary)
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Joyful);       // Joy variation, Lean toward Surprise
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Interested);   // Joy variation, Lean toward Surprise
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Proud);        // Joy variation, Lean toward Surprise
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Accepted);     // Joy variation, Lean toward Surprise
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Powerful);     // Joy variation, Lean toward Sadness
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Peaceful);     // Joy variation, Lean toward Sadness
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Intimate);     // Joy variation, Lean toward Sadness
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Optimistic);   // Joy variation, Lean toward Sadness

	// Joy variations (Tertiary)
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Amused);       // Joy.Interested variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Inquisitive);  // Joy.Interested variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Important);    // Joy.Proud variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Confidence);   // Joy.Proud variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Courageous);   // Joy.Powerful variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Provocative);  // Joy.Powerful variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Respected);    // Joy.Accepted variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Fulfilled);    // Joy.Accepted variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Hopeful);      // Joy.Peaceful variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Playful);      // Joy.Intimate variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Sensitive);    // Joy.Intimate variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Loving);       // Joy.Peaceful variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Inspired);     // Joy.Optimistic variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Open);         // Joy.Optimistic variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Ecstatic);     // Joy.Joyful variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Liberated);    // Joy.Joyful variation

	// Surprise variations (Secondary)
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Startled);     // Surprise variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Confused);     // Surprise variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Amazed);       // Surprise variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Excited);      // Surprise variation
	// Surprise variations (Tertiary)
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Shocked);      // Surprise variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Dismayed);     // Surprise variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Disillusioned); // Surprise variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Perplexed); 
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Astonished);   // Surprise variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Awe);          // Surprise.Amazed variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Eager);      // Surprise.Amazed variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Energetic);      // Surprise.Amazed variation

	// Fear variations (Secondary)
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Scared);       // Fear variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Anxious);      // Fear variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Insecure);     // Fear variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Submissive);   // Fear variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Rejected);     // Fear variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Inadequate);   // Fear variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Worried);      // Fear variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Frightened);   // Fear variation

	// Fear variations (Tertiary)
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Terrified);    // Fear.Frightened variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Overwhelmed);  // Fear.Worried variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Inferior);     // Fear.Inadequate variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Worthless);    // Fear.Inadequate variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Insignificant); // Fear.Inadequate variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Alienated);    // Fear.Rejected variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Humiliated);   // Fear.Rejected variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Wounded);      // Fear.Rejected variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Embarrassed);  // Fear.Insecure variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Ridiculed);    // Fear.Insecure variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Disrespected); // Fear.Insecure variation

	// Anger variations (Secondary)
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Mad);          // Anger variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Irritated);    // Anger variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Frustrated);   // Anger variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Distant);      // Anger variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Critical);     // Anger variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Hostile);      // Anger variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Aggressive);   // Anger variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Provoked);     // Anger variation

	// Anger variations (Tertiary)
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Enraged);      // Anger.Mad variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Hateful);      // Anger.Hostile variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Threatened);   // Anger.Provoked variation

	// Disgust variations (Secondary)
	//UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Combined_Disapproval);  // Disgust variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Disappointed); // Disgust variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Awful);        // Disgust variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Avoidance);    // Disgust variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Hesitant);     // Disgust variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Judgmental);   // Disgust variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Revolted);     // Disgust variation
	//UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Core_Loathing);     // Disgust variation

	// Disgust variations (Tertiary)
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Skeptical);    // Disgust.Judgmental variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Suspicious);   // Disgust.Judgmental variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Withdrawn);    // Disgust.Avoidance variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Aversion);     // Disgust.Avoidance variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Repelled);     // Disgust.Revolted variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Repugnant);    // Disgust.Revolted variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Detestable);   // Disgust.Loathing variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Revulsion);    // Disgust.Loathing variation

	// Sad variations (Secondary)
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Lonely);       // Sad variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Vulnerable);   // Sad variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Depressed);    // Sad variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Hurt);         // Sad variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Guilty);       // Sad variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Despair);      // Sad variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Bored);        // Sad variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Empty);        // Sad variation

	// Sad variations (Tertiary)
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Isolated);     // Sad.Lonely variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Abandoned);    // Sad.Lonely variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Powerless);    // Sad.Vulnerable variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Victimized);   // Sad.Vulnerable variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Ashamed);      // Sad.Guilty variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Remorseful);   // Sad.Guilty variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Ignored);      // Sad.Hurt variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Diminished);   // Sad.Hurt variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Apathetic);    // Sad.Bored variation
	EMOTIONENGINE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emotion_Variation_Indifferent);  // Sad.Bored variation
	/**
	 * Helper function to register all emotion tags with the GameplayTags system
	 */

	EMOTIONENGINE_API extern const TMap<FGameplayTag, FGameplayTagContainer> EmotionTagMap;
	void RegisterEmotionTags();
}
