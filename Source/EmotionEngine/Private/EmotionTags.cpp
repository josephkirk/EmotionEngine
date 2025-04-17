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
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Range_Ecstasy, "Emotion.Range.High.Joy.Ecstasy");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Range_Admiration, "Emotion.Range.High.Trust.Admiration");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Range_Terror, "Emotion.Range.High.Fear.Terror");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Range_Amazement, "Emotion.Range.High.Surprise.Amazement");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Range_Grief, "Emotion.Range.High.Sadness.Grief");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Range_Loathing, "Emotion.Range.High.Disgust.Loathing");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Range_Rage, "Emotion.Range.High.Anger.Rage");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Range_Vigilance, "Emotion.Range.High.Anticipation.Vigilance");

	// Low intensity emotions
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Range_Serenity, "Emotion.Range.Low.Joy.Serenity");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Range_Acceptance, "Emotion.Range.Low.Trust.Acceptance");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Range_Apprehension, "Emotion.Range.Low.Fear.Apprehension");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Range_Distraction, "Emotion.Range.Low.Surprise.Distraction");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Range_Pensiveness, "Emotion.Range.Low.Sadness.Pensiveness");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Range_Boredom, "Emotion.Range.Low.Disgust.Boredom");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Range_Annoyance, "Emotion.Range.Low.Anger.Annoyance");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Range_Interest, "Emotion.Range.Low.Anticipation.Interest");

	// Combined emotions
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Combined_Love, "Emotion.Combined.Love");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Combined_Guilt, "Emotion.Combined.Guilt");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Combined_Delight, "Emotion.Combined.Delight");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Combined_Optimism, "Emotion.Combined.Optimism");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Combined_Morbidness, "Emotion.Combined.Morbidness");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Combined_Submission, "Emotion.Combined.Submission");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Combined_Sentimentality, "Emotion.Combined.Sentimentality");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Combined_Hope, "Emotion.Combined.Hope");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Combined_Dominance, "Emotion.Combined.Dominance");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Combined_Awe, "Emotion.Combined.Awe");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Combined_Anxiety, "Emotion.Combined.Anxiety");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Combined_Despair, "Emotion.Combined.Despair");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Combined_Shame, "Emotion.Combined.Shame");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Combined_Disapproval, "Emotion.Combined.Disapproval");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Combined_Unbelief, "Emotion.Combined.Unbelief");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Combined_Outrage, "Emotion.Combined.Outrage");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Combined_Remorse, "Emotion.Combined.Remorse");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Combined_Envy, "Emotion.Combined.Envy");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Combined_Pessimism, "Emotion.Combined.Pessimism");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Combined_Contempt, "Emotion.Combined.Contempt");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Combined_Cynicism, "Emotion.Combined.Cynicism");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Combined_Aggressiveness, "Emotion.Combined.Aggressiveness");

	// Combined emotions range
	// Love
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Range_Rapture, "Emotion.Range.High.Love.Rapture");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Range_Affection, "Emotion.Range.Low.Love.Affection");

	// Guilt
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Range_Remorse, "Emotion.Range.High.Guilt.Remorse");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Range_Compunction, "Emotion.Range.Low.Guilt.Compunction");

	// Delight
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Range_Glee, "Emotion.Range.High.Delight.Glee");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Range_Contentment, "Emotion.Range.Low.Delight.Contentment");

	// Optimism
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Range_Exuberance, "Emotion.Range.High.Optimism.Exuberance");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Range_Hopefulness, "Emotion.Range.Low.Optimism.Hopefulness");

	// Morbidness
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Range_Ghastliness, "Emotion.Range.High.Morbidness.Ghastliness");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Range_Somberness, "Emotion.Range.Low.Morbidness.Somberness");

	// Submission
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Range_Servility, "Emotion.Range.High.Submission.Servility");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Range_Acquiescence, "Emotion.Range.Low.Submission.Acquiescence");

	//Sentimentality
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Range_Mawkishness, "Emotion.Range.High.Sentimentality.Mawkishness");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Range_Wishfulness, "Emotion.Range.Low.Sentimentality.Wishfulness");

	// Hope
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Range_Faith, "Emotion.Range.High.Hope.Faith");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Range_Optimistic, "Emotion.Range.Low.Hope.Optimistic");

	// Dominance
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Range_Powerlust, "Emotion.Range.High.Dominance.Powerlust");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Range_Authority, "Emotion.Range.Low.Dominance.Authority");

	// Awe
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Range_Reverence, "Emotion.Range.High.Awe.Reverence");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Range_Curiosity, "Emotion.Range.Low.Awe.Curiosity");

	// Anxiety
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Range_Worry, "Emotion.Range.High.Anxiety.Worry");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Range_Nervousness, "Emotion.Range.Low.Anxiety.Nervousness");

	// Despair
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Range_Dread, "Emotion.Range.High.Despair.Dread");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Range_Gloom, "Emotion.Range.Low.Despair.Gloom");

	// Shame
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Range_SelfLoathing, "Emotion.Range.High.Sham.SelfLoathing");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Range_Embarassment, "Emotion.Range.Low.Sham.Embarassment");

	// Disapproval
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Range_Comdemnation, "Emotion.Range.High.Disapproval.Comdemnation");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Range_Doubt, "Emotion.Range.Low.Disapproval.Doubt");

	// Unbelief
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Range_Incredulity, "Emotion.Range.High.Unbelief.Incredulity");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Range_Dismissal, "Emotion.Range.Low.Unbelief.Dismissal");

	// Outrage
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Range_Indignation, "Emotion.Range.High.Outrage.Indignation");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Range_Irritation, "Emotion.Range.Low.Outrage.Irritation");

	// Remorse
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Range_Repentance, "Emotion.Range.High.Remorse.Repentance");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Range_Regret, "Emotion.Range.Low.Remorse.Regret");

	// Envy
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Range_Spite, "Emotion.Range.High.Envy.Spite");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Range_Jealousy, "Emotion.Range.Low.Envy.Jealousy");

	// Pessimism
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Range_Resignation, "Emotion.Range.High.Pessimism.Resignation");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Range_Discouragement, "Emotion.Range.Low.Pessimism.Discouragement");

	// Contempt
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Range_Scorn, "Emotion.Range.High.Contempt.Scorn");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Range_Disdain, "Emotion.Range.Low.Contempt.Disdain");

	// Cynicism
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Range_Misanthropy, "Emotion.Range.High.Cynicism.Misanthropy");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Range_Skepticism, "Emotion.Range.Low.Cynicism.Skepticism");

	// Aggressiveness
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Range_Ruthlessness, "Emotion.Range.High.Aggressiveness.Ruthlessness");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Range_Contention, "Emotion.Range.Low.Aggressiveness.Contention");

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
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Liberated, "Emotion.Variation.Joy.Joyful.Liberated"); // High
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Ecstatic, "Emotion.Variation.Joy.Joyful.Ecstatic"); // Low
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Amused, "Emotion.Variation.Joy.Interested.Amused"); // High
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Inquisitive, "Emotion.Variation.Joy.Interested.Inquisitive"); // Low
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Important, "Emotion.Variation.Joy.Proud.Important"); // High
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Confidence, "Emotion.Variation.Joy.Proud.Confidence"); // Low
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Courageous, "Emotion.Variation.Joy.Powerful.Courageous"); // High
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Provocative, "Emotion.Variation.Joy.Powerful.Provocative"); // Low
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Respected, "Emotion.Variation.Joy.Accepted.Respected"); // High
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Fulfilled, "Emotion.Variation.Joy.Accepted.Fulfilled"); // Low
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Hopeful, "Emotion.Variation.Joy.Peaceful.Hopeful"); // High
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Playful, "Emotion.Variation.Joy.Intimate.Playful"); // Low
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Sensitive, "Emotion.Variation.Joy.Intimate.Sensitive"); // High
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Loving, "Emotion.Variation.Joy.Peaceful.Loving"); // Low
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Inspired, "Emotion.Variation.Joy.Optimistic.Inspired"); // High
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Open, "Emotion.Variation.Joy.Optimistic.Open"); // Low

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
	
	// Trust Variation (Secondary)
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Secure, "Emotion.Variation.Trust.Secure");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Assured, "Emotion.Variation.Trust.Assured");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Confident, "Emotion.Variation.Trust.Confident");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Safe, "Emotion.Variation.Trust.Safe");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Supported, "Emotion.Variation.Trust.Supported");

	// Trust variations (Tertiary)
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Appreciated, "Emotion.Variation.Trust.Appreciated");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Valued, "Emotion.Variation.Trust.Valued");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Reliable, "Emotion.Variation.Trust.Reliable");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Faithful, "Emotion.Variation.Trust.Faithful");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Dependable, "Emotion.Variation.Trust.Dependable");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Admired, "Emotion.Variation.Trust.Admired");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Included, "Emotion.Variation.Trust.Included");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Protected, "Emotion.Variation.Trust.Protected");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Comforted, "Emotion.Variation.Trust.Comforted");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Belonging, "Emotion.Variation.Trust.Belonging");

	// Anticipation variations (Secondary)
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Expectant, "Emotion.Variation.Anticipation.Expectant");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Prepared, "Emotion.Variation.Anticipation.Prepared");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Alert, "Emotion.Variation.Anticipation.Alert");

	// Anticipation variations (Tertiary)
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Restless, "Emotion.Variation.Anticipation.Restless");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Impatient, "Emotion.Variation.Anticipation.Impatient");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Thrilled, "Emotion.Variation.Anticipation.Thrilled");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Fascinated, "Emotion.Variation.Anticipation.Fascinated");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Attentive, "Emotion.Variation.Anticipation.Attentive");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Variation_Vigilant, "Emotion.Variation.Anticipation.Vigilant");


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
