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
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Ecstasy, "Emotion.Range.Joy.Ecstasy");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Admiration, "Emotion.Range.Trust.Admiration");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Terror, "Emotion.Range.Fear.Terror");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Amazement, "Emotion.Range.Surprise.Amazement");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Grief, "Emotion.Range.Sadness.Grief");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Loathing, "Emotion.Range.Disgust.Loathing");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Rage, "Emotion.Range.Anger.Rage");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Vigilance, "Emotion.Range.Anticipation.Vigilance");

	// Low intensity emotions
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Serenity, "Emotion.Range.Joy.Serenity");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Acceptance, "Emotion.Range.Trust.Acceptance");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Apprehension, "Emotion.Range.Fear.Apprehension");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Distraction, "Emotion.Range.Surprise.Distraction");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Pensiveness, "Emotion.Range.Sadness.Pensiveness");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Boredom, "Emotion.Range.Disgust.Boredom");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Annoyance, "Emotion.Range.Anger.Annoyance");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Interest, "Emotion.Range.Anticipation.Interest");

	// Combined emotions
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Love, "Emotion.Combined.Love");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Submission, "Emotion.Combined.Submission");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Awe, "Emotion.Combined.Awe");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Disapproval, "Emotion.Combined.Disapproval");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Remorse, "Emotion.Combined.Remorse");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Contempt, "Emotion.Combined.Contempt");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Aggressiveness, "Emotion.Combined.Aggressiveness");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Optimism, "Emotion.Combined.Optimism");

	void RegisterEmotionTags()
	{
		// The tags are already registered through the UE_DEFINE_GAMEPLAY_TAG macro
		// This function is provided as a hook for any additional registration that might be needed in the future
	}
}
