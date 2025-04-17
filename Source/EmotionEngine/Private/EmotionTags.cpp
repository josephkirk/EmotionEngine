// Copyright Epic Games, Inc. All Rights Reserved.

#include "EmotionTags.h"
#include "GameplayTagsManager.h"

// Define all emotion tags
namespace EmotionGameplayTags
{
	// Core emotions
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Core_Joy, "Emotion.Core.Joy");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Core_Trust, "Emotion.Core.Trust");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Core_Fear, "Emotion.Core.Fear");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Core_Surprise, "Emotion.Core.Surprise");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Core_Sadness, "Emotion.Core.Sadness");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Core_Disgust, "Emotion.Core.Disgust");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Core_Anger, "Emotion.Core.Anger");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Core_Anticipation, "Emotion.Core.Anticipation");

	// High intensity emotions
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Core_Ecstasy, "Emotion.Range.High.Joy.Ecstasy");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Core_Admiration, "Emotion.Range.High.Trust.Admiration");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Core_Terror, "Emotion.Range.High.Fear.Terror");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Core_Amazement, "Emotion.Range.High.Surprise.Amazement");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Core_Grief, "Emotion.Range.High.Sadness.Grief");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Core_Loathing, "Emotion.Range.High.Disgust.Loathing");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Core_Rage, "Emotion.Range.High.Anger.Rage");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Core_Vigilance, "Emotion.Range.High.Anticipation.Vigilance");

	// Low intensity emotions
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Core_Serenity, "Emotion.Range.Low.Joy.Serenity");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Core_Acceptance, "Emotion.Range.Low.Trust.Acceptance");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Core_Apprehension, "Emotion.Range.Low.Fear.Apprehension");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Core_Distraction, "Emotion.Range.Low.Surprise.Distraction");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Core_Pensiveness, "Emotion.Range.Low.Sadness.Pensiveness");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Core_Boredom, "Emotion.Range.Low.Disgust.Boredom");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Core_Annoyance, "Emotion.Range.Low.Anger.Annoyance");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Core_Interest, "Emotion.Range.Low.Anticipation.Interest");

	// Combined emotions
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Combined_Love, "Emotion.Combined.Love");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Combined_Submission, "Emotion.Combined.Submission");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Combined_Awe, "Emotion.Combined.Awe");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Combined_Disapproval, "Emotion.Combined.Disapproval");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Combined_Remorse, "Emotion.Combined.Remorse");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Combined_Contempt, "Emotion.Combined.Contempt");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Combined_Aggressiveness, "Emotion.Combined.Aggressiveness");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Combined_Optimism, "Emotion.Combined.Optimism");

	// Joy variations (Secondary) When Main Emotion's Intensity is 35-75 
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Joyful, "Emotion.Variation.Joy.Joyful"); // Lean toward Surprise
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Interested, "Emotion.Variation.Joy.Interested"); // Lean toward Surprise
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Proud, "Emotion.Variation.Joy.Proud"); // Lean toward Surprise
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Accepted, "Emotion.Variation.Joy.Accepted"); // Lean toward Surprise
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Powerful, "Emotion.Variation.Joy.Powerful"); // Lean toward Sadness
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Peaceful, "Emotion.Variation.Joy.Peaceful"); // Lean toward Sadness
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Intimate, "Emotion.Variation.Joy.Intimate"); // Lean toward Sadness
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Optimistic, "Emotion.Variation.Joy.Optimistic"); // Lean toward Sadness

	// Joy variations (Tertiary) When Main Emotion's Intensity is 0-35
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Liberated, "Emotion.Variation.Joy.Joyful.Liberated");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Ecstatic, "Emotion.Variation.Joy.Joyful.Ecstatic");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Amused, "Emotion.Variation.Joy.Interested.Amused");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Inquisitive, "Emotion.Variation.Joy.Interested.Inquisitive");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Important, "Emotion.Variation.Joy.Proud.Important");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Confidence, "Emotion.Variation.Joy.Proud.Confidence");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Courageous, "Emotion.Variation.Joy.Powerful.Courageous");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Provocative, "Emotion.Variation.Joy.Powerful.Provocative");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Respected, "Emotion.Variation.Joy.Accepted.Respected");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Fulfilled, "Emotion.Variation.Joy.Accepted.Fulfilled");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Hopeful, "Emotion.Variation.Joy.Peaceful.Hopeful");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Playful, "Emotion.Variation.Joy.Intimate.Playful");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Sensitive, "Emotion.Variation.Joy.Intimate.Sensitive");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Loving, "Emotion.Variation.Joy.Peaceful.Loving");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Inspired, "Emotion.Variation.Joy.Optimistic.Inspired");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Open, "Emotion.Variation.Joy.Optimistic.Open");

	// Surprise variations (Secondary) When Main Emotion's Intensity is 35-75
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Startled, "Emotion.Variation.Surprise.Startled");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Confused, "Emotion.Variation.Surprise.Confused");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Amazed, "Emotion.Variation.Surprise.Amazed");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Excited, "Emotion.Variation.Surprise.Excited");

	// Surprise variations (Tertiary) When Main Emotion's Intensity is 0-35
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Shocked, "Emotion.Variation.Surprise.Startled.Shocked");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Dismayed, "Emotion.Variation.Surprise.Startled.Dismayed");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Disillusioned, "Emotion.Variation.Surprise.Confused.Disillusioned");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Perplexed, "Emotion.Variation.Surprise.Confused.Perplexed");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Astonished, "Emotion.Variation.Surprise.Amazed.Astonished");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Awe, "Emotion.Variation.Surprise.Amazed.Awe");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Eager, "Emotion.Variation.Surprise.Excited.Eager");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Energetic, "Emotion.Variation.Surprise.Excited.Energetic");
	
	// Fear variations (Secondary)
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Scared, "Emotion.Variation.Fear.Scared");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Anxious, "Emotion.Variation.Fear.Anxious");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Insecure, "Emotion.Variation.Fear.Insecure");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Submissive, "Emotion.Variation.Fear.Submissive");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Rejected, "Emotion.Variation.Fear.Rejected");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Inadequate, "Emotion.Variation.Fear.Inadequate");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Worried, "Emotion.Variation.Fear.Worried");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Frightened, "Emotion.Variation.Fear.Frightened");

	// Fear variations (Tertiary)
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Terrified, "Emotion.Variation.Fear.Frightened.Terrified");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Overwhelmed, "Emotion.Variation.Fear.Worried.Overwhelmed");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Inferior, "Emotion.Variation.Fear.Inadequate.Inferior");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Worthless, "Emotion.Variation.Fear.Inadequate.Worthless");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Insignificant, "Emotion.Variation.Fear.Inadequate.Insignificant");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Alienated, "Emotion.Variation.Fear.Rejected.Alienated");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Humiliated, "Emotion.Variation.Fear.Rejected.Humiliated");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Wounded, "Emotion.Variation.Fear.Rejected.Wounded");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Embarrassed, "Emotion.Variation.Fear.Insecure.Embarrassed");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Ridiculed, "Emotion.Variation.Fear.Insecure.Ridiculed");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Disrespected, "Emotion.Variation.Fear.Insecure.Disrespected");

	// Anger variations (Secondary)
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Mad, "Emotion.Variation.Anger.Mad");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Irritated, "Emotion.Variation.Anger.Irritated");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Frustrated, "Emotion.Variation.Anger.Frustrated");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Distant, "Emotion.Variation.Anger.Distant");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Critical, "Emotion.Variation.Anger.Critical");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Hostile, "Emotion.Variation.Anger.Hostile");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Aggressive, "Emotion.Variation.Anger.Aggressive");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Provoked, "Emotion.Variation.Anger.Provoked");

	// Anger variations (Tertiary)
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Enraged, "Emotion.Variation.Anger.Mad.Enraged");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Hateful, "Emotion.Variation.Anger.Hostile.Hateful");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Threatened, "Emotion.Variation.Anger.Provoked.Threatened");

	// Disgust variations (Secondary)
	//UE_DEFINE_GAMEPLAY_TAG(Emotion_Combined_Disapproval, "Emotion.Variation.Disgust.Disapproval");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Disappointed, "Emotion.Variation.Disgust.Disappointed");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Awful, "Emotion.Variation.Disgust.Awful");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Avoidance, "Emotion.Variation.Disgust.Avoidance");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Hesitant, "Emotion.Variation.Disgust.Hesitant");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Judgmental, "Emotion.Variation.Disgust.Judgmental");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Revolted, "Emotion.Variation.Disgust.Revolted");
	//UE_DEFINE_GAMEPLAY_TAG(Emotion_Core_Loathing, "Emotion.Variation.Disgust.Loathing");

	// Disgust variations (Tertiary)
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Skeptical, "Emotion.Variation.Disgust.Judgmental.Skeptical");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Suspicious, "Emotion.Variation.Disgust.Judgmental.Suspicious");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Withdrawn, "Emotion.Variation.Disgust.Avoidance.Withdrawn");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Aversion, "Emotion.Variation.Disgust.Avoidance.Aversion");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Repelled, "Emotion.Variation.Disgust.Revolted.Repelled");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Repugnant, "Emotion.Variation.Disgust.Revolted.Repugnant");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Detestable, "Emotion.Variation.Disgust.Loathing.Detestable");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Revulsion, "Emotion.Variation.Disgust.Loathing.Revulsion");

	// Sad variations (Secondary)
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Lonely, "Emotion.Variation.Sad.Lonely");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Vulnerable, "Emotion.Variation.Sad.Vulnerable");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Depressed, "Emotion.Variation.Sad.Depressed");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Hurt, "Emotion.Variation.Sad.Hurt");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Guilty, "Emotion.Variation.Sad.Guilty");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Despair, "Emotion.Variation.Sad.Despair");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Bored, "Emotion.Variation.Sad.Bored");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Empty, "Emotion.Variation.Sad.Empty");

	// Sad variations (Tertiary)
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Isolated, "Emotion.Variation.Sad.Lonely.Isolated");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Abandoned, "Emotion.Variation.Sad.Lonely.Abandoned");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Powerless, "Emotion.Variation.Sad.Vulnerable.Powerless");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Victimized, "Emotion.Variation.Sad.Vulnerable.Victimized");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Ashamed, "Emotion.Variation.Sad.Guilty.Ashamed");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Remorseful, "Emotion.Variation.Sad.Guilty.Remorseful");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Ignored, "Emotion.Variation.Sad.Hurt.Ignored");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Diminished, "Emotion.Variation.Sad.Hurt.Diminished");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Apathetic, "Emotion.Variation.Sad.Bored.Apathetic");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Indifferent, "Emotion.Variation.Sad.Bored.Indifferent");
	void RegisterEmotionTags()
	{
		// The tags are already registered through the UE_DEFINE_GAMEPLAY_TAG macro
		// This function is provided as a hook for any additional registration that might be needed in the future
	}
}
