// Copyright Epic Games, Inc. All Rights Reserved.

#include "EmotionTags.h"
#include "GameplayTagsManager.h"

// Define all emotion tags
namespace EmotionGameplayTags
{
	// Core emotions
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Joy, "Emotion.Core.Joy");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Trust, "Emotion.Core.Trust");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Fear, "Emotion.Core.Fear");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Surprise, "Emotion.Core.Surprise");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Sadness, "Emotion.Core.Sadness");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Disgust, "Emotion.Core.Disgust");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Anger, "Emotion.Core.Anger");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Anticipation, "Emotion.Core.Anticipation");

	// High intensity emotions
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Ecstasy, "Emotion.Range.High.Joy.Ecstasy");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Admiration, "Emotion.Range.High.Trust.Admiration");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Terror, "Emotion.Range.High.Fear.Terror");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Amazement, "Emotion.Range.High.Surprise.Amazement");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Grief, "Emotion.Range.High.Sadness.Grief");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Loathing, "Emotion.Range.High.Disgust.Loathing");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Rage, "Emotion.Range.High.Anger.Rage");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Vigilance, "Emotion.Range.High.Anticipation.Vigilance");

	// Low intensity emotions
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Serenity, "Emotion.Range.Low.Joy.Serenity");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Acceptance, "Emotion.Range.Low.Trust.Acceptance");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Apprehension, "Emotion.Range.Low.Fear.Apprehension");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Distraction, "Emotion.Range.Low.Surprise.Distraction");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Pensiveness, "Emotion.Range.Low.Sadness.Pensiveness");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Boredom, "Emotion.Range.Low.Disgust.Boredom");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Annoyance, "Emotion.Range.Low.Anger.Annoyance");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Interest, "Emotion.Range.Low.Anticipation.Interest");

	// Combined emotions
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Love, "Emotion.Combined.Love");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Submission, "Emotion.Combined.Submission");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Awe, "Emotion.Combined.Awe");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Disapproval, "Emotion.Combined.Disapproval");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Remorse, "Emotion.Combined.Remorse");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Contempt, "Emotion.Combined.Contempt");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Aggressiveness, "Emotion.Combined.Aggressiveness");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Optimism, "Emotion.Combined.Optimism");

	// Joy variations (Secondary)
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Joyful, "Emotion.Variation.Joy.Joyful");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Interested, "Emotion.Variation.Joy.Interested");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Proud, "Emotion.Variation.Joy.Proud");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Accepted, "Emotion.Variation.Joy.Accepted");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Powerful, "Emotion.Variation.Joy.Powerful");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Peaceful, "Emotion.Variation.Joy.Peaceful");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Intimate, "Emotion.Variation.Joy.Intimate");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Optimistic, "Emotion.Variation.Joy.Optimistic");

	// Joy variations (Tertiary)
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Amused, "Emotion.Variation.Joy.Interested.Amused");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Inquisitive, "Emotion.Variation.Joy.Interested.Inquisitive");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Important, "Emotion.Variation.Joy.Proud.Important");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Confidence, "Emotion.Variation.Joy.Proud.Confidence");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Courageous, "Emotion.Variation.Joy.Powerful.Courageous");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Provocative, "Emotion.Variation.Joy.Powerful.Provocative");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Respected, "Emotion.Variation.Joy.Accepted.Respected");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Fulfilled, "Emotion.Variation.Joy.Accepted.Fulfilled");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Hopeful, "Emotion.Variation.Joy.Peaceful.Hopeful");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Playful, "Emotion.Variation.Joy.Intimate.Playful");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Sensitive, "Emotion.Variation.Joy.Intimate.Sensitive");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Loving, "Emotion.Variation.Joy.Peaceful.Loving");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Inspired, "Emotion.Variation.Joy.Optimistic.Inspired");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Open, "Emotion.Variation.Joy.Optimistic.Open");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Ecstatic, "Emotion.Variation.Joy.Joyful.Ecstatic");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Liberated, "Emotion.Variation.Joy.Joyful.Liberated");

	// Surprise variations (Secondary)
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Startled, "Emotion.Variation.Surprise.Startled");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Confused, "Emotion.Variation.Surprise.Confused");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Amazed, "Emotion.Variation.Surprise.Amazed");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Astonished, "Emotion.Variation.Surprise.Astonished");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Shocked, "Emotion.Variation.Surprise.Shocked");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Dismayed, "Emotion.Variation.Surprise.Dismayed");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Disillusioned, "Emotion.Variation.Surprise.Disillusioned");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Perplexed, "Emotion.Variation.Surprise.Perplexed");

	// Surprise variations (Tertiary)
	//UE_DEFINE_GAMEPLAY_TAG(Emotion_Awe, "Emotion.Surprise.Amazed.Awe");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Excited, "Emotion.Variation.Surprise.Amazed.Excited");

	// Fear variations (Secondary)
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Scared, "Emotion.Variation.Fear.Scared");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Anxious, "Emotion.Variation.Fear.Anxious");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Insecure, "Emotion.Variation.Fear.Insecure");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Submissive, "Emotion.Variation.Fear.Submissive");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Rejected, "Emotion.Variation.Fear.Rejected");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Inadequate, "Emotion.Variation.Fear.Inadequate");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Worried, "Emotion.Variation.Fear.Worried");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Frightened, "Emotion.Variation.Fear.Frightened");

	// Fear variations (Tertiary)
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Terrified, "Emotion.Variation.Fear.Frightened.Terrified");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Overwhelmed, "Emotion.Variation.Fear.Worried.Overwhelmed");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Inferior, "Emotion.Variation.Fear.Inadequate.Inferior");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Worthless, "Emotion.Variation.Fear.Inadequate.Worthless");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Insignificant, "Emotion.Variation.Fear.Inadequate.Insignificant");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Alienated, "Emotion.Variation.Fear.Rejected.Alienated");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Humiliated, "Emotion.Variation.Fear.Rejected.Humiliated");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Wounded, "Emotion.Variation.Fear.Rejected.Wounded");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Embarrassed, "Emotion.Variation.Fear.Insecure.Embarrassed");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Ridiculed, "Emotion.Variation.Fear.Insecure.Ridiculed");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Disrespected, "Emotion.Variation.Fear.Insecure.Disrespected");

	// Anger variations (Secondary)
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Mad, "Emotion.Variation.Anger.Mad");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Irritated, "Emotion.Variation.Anger.Irritated");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Frustrated, "Emotion.Variation.Anger.Frustrated");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Distant, "Emotion.Variation.Anger.Distant");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Critical, "Emotion.Variation.Anger.Critical");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Hostile, "Emotion.Variation.Anger.Hostile");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Aggressive, "Emotion.Variation.Anger.Aggressive");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Provoked, "Emotion.Variation.Anger.Provoked");

	// Anger variations (Tertiary)
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Enraged, "Emotion.Variation.Anger.Mad.Enraged");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Hateful, "Emotion.Variation.Anger.Hostile.Hateful");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Threatened, "Emotion.Variation.Anger.Provoked.Threatened");

	// Disgust variations (Secondary)
	//UE_DEFINE_GAMEPLAY_TAG(Emotion_Disapproval, "Emotion.Disgust.Disapproval");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Disappointed, "Emotion.Variation.Disgust.Disappointed");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Awful, "Emotion.Variation.Disgust.Awful");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Avoidance, "Emotion.Variation.Disgust.Avoidance");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Hesitant, "Emotion.Variation.Disgust.Hesitant");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Judgmental, "Emotion.Variation.Disgust.Judgmental");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Revolted, "Emotion.Variation.Disgust.Revolted");
	//UE_DEFINE_GAMEPLAY_TAG(Emotion_Loathing, "Emotion.Disgust.Loathing");

	// Disgust variations (Tertiary)
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Skeptical, "Emotion.Variation.Disgust.Judgmental.Skeptical");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Suspicious, "Emotion.Variation.Disgust.Judgmental.Suspicious");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Withdrawn, "Emotion.Variation.Disgust.Avoidance.Withdrawn");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Aversion, "Emotion.Variation.Disgust.Avoidance.Aversion");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Repelled, "Emotion.Variation.Disgust.Revolted.Repelled");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Repugnant, "Emotion.Variation.Disgust.Revolted.Repugnant");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Detestable, "Emotion.Variation.Disgust.Loathing.Detestable");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Revulsion, "Emotion.Variation.Disgust.Loathing.Revulsion");

	// Sad variations (Secondary)
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Lonely, "Emotion.Variation.Sad.Lonely");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Vulnerable, "Emotion.Variation.Sad.Vulnerable");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Depressed, "Emotion.Variation.Sad.Depressed");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Hurt, "Emotion.Variation.Sad.Hurt");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Guilty, "Emotion.Variation.Sad.Guilty");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Despair, "Emotion.Variation.Sad.Despair");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Bored, "Emotion.Variation.Sad.Bored");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Empty, "Emotion.Variation.Sad.Empty");

	// Sad variations (Tertiary)
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Isolated, "Emotion.Variation.Sad.Lonely.Isolated");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Abandoned, "Emotion.Variation.Sad.Lonely.Abandoned");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Powerless, "Emotion.Variation.Sad.Vulnerable.Powerless");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Victimized, "Emotion.Variation.Sad.Vulnerable.Victimized");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Ashamed, "Emotion.Variation.Sad.Guilty.Ashamed");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Remorseful, "Emotion.Variation.Sad.Guilty.Remorseful");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Ignored, "Emotion.Variation.Sad.Hurt.Ignored");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Diminished, "Emotion.Variation.Sad.Hurt.Diminished");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Apathetic, "Emotion.Variation.Sad.Bored.Apathetic");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Indifferent, "Emotion.Variation.Sad.Bored.Indifferent");
	void RegisterEmotionTags()
	{
		// The tags are already registered through the UE_DEFINE_GAMEPLAY_TAG macro
		// This function is provided as a hook for any additional registration that might be needed in the future
	}
}
