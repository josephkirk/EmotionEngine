#pragma once

#include "CoreMinimal.h"
#include "EmotionType.generated.h"

UENUM(BlueprintType)
namespace EEmotionType
{
	enum Type : int
	{
		Core UMETA(Hidden, DisplayName = "Core Emotion"),

		Combined UMETA(DisplayName = "Combined Emotion")

        Ranged UMETA(DisplayName = "Range Emotion")

        Variant UMETA(DisplayName = "Variation Emotion")
	};
}