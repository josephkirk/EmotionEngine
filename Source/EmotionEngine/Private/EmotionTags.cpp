// Copyright Epic Games, Inc. All Rights Reserved.

#include "EmotionTags.h"
#include "GameplayTagsManager.h"

// Define all emotion tags
namespace EmotionGameplayTags
{
	// Core emotions
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Joy, "Emotion.Joy");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Trust, "Emotion.Trust");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Fear, "Emotion.Fear");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Surprise, "Emotion.Surprise");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Sadness, "Emotion.Sadness");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Disgust, "Emotion.Disgust");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Anger, "Emotion.Anger");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Anticipation, "Emotion.Anticipation");

	// High intensity emotions
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Ecstasy, "Emotion.Joy.Ecstasy");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Admiration, "Emotion.Trust.Admiration");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Terror, "Emotion.Fear.Terror");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Amazement, "Emotion.Surprise.Amazement");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Grief, "Emotion.Sadness.Grief");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Loathing, "Emotion.Disgust.Loathing");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Rage, "Emotion.Anger.Rage");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Vigilance, "Emotion.Anticipation.Vigilance");

	// Low intensity emotions
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Serenity, "Emotion.Joy.Serenity");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Acceptance, "Emotion.Trust.Acceptance");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Apprehension, "Emotion.Fear.Apprehension");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Distraction, "Emotion.Surprise.Distraction");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Pensiveness, "Emotion.Sadness.Pensiveness");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Boredom, "Emotion.Disgust.Boredom");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Annoyance, "Emotion.Anger.Annoyance");
	UE_DEFINE_GAMEPLAY_TAG(Emotion_Interest, "Emotion.Anticipation.Interest");

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
