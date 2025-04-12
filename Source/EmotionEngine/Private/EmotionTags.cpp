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
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Joyful, "Emotion.Joy.Joyful");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Interested, "Emotion.Joy.Interested");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Proud, "Emotion.Joy.Proud");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Accepted, "Emotion.Joy.Accepted");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Powerful, "Emotion.Joy.Powerful");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Peaceful, "Emotion.Joy.Peaceful");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Intimate, "Emotion.Joy.Intimate");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Optimistic, "Emotion.Joy.Optimistic");

	// Joy variations (Tertiary)
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Amused, "Emotion.Joy.Interested.Amused");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Inquisitive, "Emotion.Joy.Interested.Inquisitive");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Important, "Emotion.Joy.Proud.Important");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Confidence, "Emotion.Joy.Proud.Confidence");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Courageous, "Emotion.Joy.Powerful.Courageous");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Provocative, "Emotion.Joy.Powerful.Provocative");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Respected, "Emotion.Joy.Accepted.Respected");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Fulfilled, "Emotion.Joy.Accepted.Fulfilled");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Hopeful, "Emotion.Joy.Peaceful.Hopeful");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Playful, "Emotion.Joy.Intimate.Playful");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Sensitive, "Emotion.Joy.Intimate.Sensitive");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Loving, "Emotion.Joy.Peaceful.Loving");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Inspired, "Emotion.Joy.Optimistic.Inspired");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Open, "Emotion.Joy.Optimistic.Open");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Ecstatic, "Emotion.Joy.Joyful.Ecstatic");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Liberated, "Emotion.Joy.Joyful.Liberated");

	// Surprise variations
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Awe, "Emotion.Surprise.Awe");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Astonished, "Emotion.Surprise.Astonished");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Perplexed, "Emotion.Surprise.Perplexed");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Disillusioned, "Emotion.Surprise.Disillusioned");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Dismayed, "Emotion.Surprise.Dismayed");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Shocked, "Emotion.Surprise.Shocked");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Confused, "Emotion.Surprise.Confused");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Amazed, "Emotion.Surprise.Amazed");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Excited, "Emotion.Surprise.Excited");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Startled, "Emotion.Surprise.Startled");

	// Fear variations
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Terrified, "Emotion.Fear.Terrified");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Frightened, "Emotion.Fear.Frightened");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Overwhelmed, "Emotion.Fear.Overwhelmed");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Worried, "Emotion.Fear.Worried");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Inadequate, "Emotion.Fear.Inadequate");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Inferior, "Emotion.Fear.Inferior");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Worthless, "Emotion.Fear.Worthless");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Insignificant, "Emotion.Fear.Insignificant");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Alienated, "Emotion.Fear.Alienated");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Rejected, "Emotion.Fear.Rejected");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Submissive, "Emotion.Fear.Submissive");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Insecure, "Emotion.Fear.Insecure");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Anxious, "Emotion.Fear.Anxious");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Scared, "Emotion.Fear.Scared");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Humiliated, "Emotion.Fear.Humiliated");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Wounded, "Emotion.Fear.Wounded");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Embarrassed, "Emotion.Fear.Embarrassed");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Ridiculed, "Emotion.Fear.Ridiculed");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Disrespected, "Emotion.Fear.Disrespected");

	// Anger variations
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Enraged, "Emotion.Anger.Enraged");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Provoked, "Emotion.Anger.Provoked");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Hostile, "Emotion.Anger.Hostile");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Irritated, "Emotion.Anger.Irritated");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Frustrated, "Emotion.Anger.Frustrated");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Aggressive, "Emotion.Anger.Aggressive");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Mad, "Emotion.Anger.Mad");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Hateful, "Emotion.Anger.Hateful");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Threatened, "Emotion.Anger.Threatened");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Distant, "Emotion.Anger.Distant");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Critical, "Emotion.Anger.Critical");

	// Disgust variations
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Disapproval, "Emotion.Disgust.Disapproval");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Disappointed, "Emotion.Disgust.Disappointed");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Awful, "Emotion.Disgust.Awful");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Avoidance, "Emotion.Disgust.Avoidance");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Aversion, "Emotion.Disgust.Aversion");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Hesitant, "Emotion.Disgust.Hesitant");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Revolted, "Emotion.Disgust.Revolted");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Repugnant, "Emotion.Disgust.Repugnant");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Loathing, "Emotion.Disgust.Loathing");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Judgmental, "Emotion.Disgust.Judgmental");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Skeptical, "Emotion.Disgust.Skeptical");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Suspicious, "Emotion.Disgust.Suspicious");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Withdrawn, "Emotion.Disgust.Withdrawn");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Repelled, "Emotion.Disgust.Repelled");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Detestable, "Emotion.Disgust.Detestable");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Revulsion, "Emotion.Disgust.Revulsion");

	// Sad variations
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Lonely, "Emotion.Sad.Lonely");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Vulnerable, "Emotion.Sad.Vulnerable");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Despair, "Emotion.Sad.Despair");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Guilty, "Emotion.Sad.Guilty");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Depressed, "Emotion.Sad.Depressed");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Hurt, "Emotion.Sad.Hurt");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Bored, "Emotion.Sad.Bored");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Apathetic, "Emotion.Sad.Apathetic");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Indifferent, "Emotion.Sad.Indifferent");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Diminished, "Emotion.Sad.Diminished");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Empty, "Emotion.Sad.Empty");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Abandoned, "Emotion.Sad.Abandoned");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Isolated, "Emotion.Sad.Isolated");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Powerless, "Emotion.Sad.Powerless");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Victimized, "Emotion.Sad.Victimized");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Ignored, "Emotion.Sad.Ignored");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Ashamed, "Emotion.Sad.Ashamed");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Remorseful, "Emotion.Sad.Remorseful");
	void RegisterEmotionTags()
	{
		// The tags are already registered through the UE_DEFINE_GAMEPLAY_TAG macro
		// This function is provided as a hook for any additional registration that might be needed in the future
	}
}
