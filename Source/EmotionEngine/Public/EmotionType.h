#pragma once

#include "CoreMinimal.h"
#include "EmotionType.generated.h"

UENUM(BlueprintType)
enum class EEmotionType: uint8
{
	Core UMETA(Hidden, DisplayName = "Core Emotion"),

	Combined UMETA(DisplayName = "Combined Emotion"),

    Ranged UMETA(DisplayName = "Range Emotion"),

    Variant UMETA(DisplayName = "Variation Emotion")
};
