#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Emotion.h"
#include "PolarCoordinate.h"
#include "EmotionZone.generated.h"

/**
 * EmotionZone defines a region in the Valence-Arousal space that represents a specific emotion or emotional state.
 * It uses polar coordinates (radius range and angle range) to define its boundaries.
 */
USTRUCT(BlueprintType)
struct EMOTIONENGINE_API FEmotionZone
{
    GENERATED_BODY()

public:
    // The gameplay tag that identifies this emotion zone
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EmotionSystem", meta = (Categories = "Emotion"))
    FGameplayTag EmotionTag;
    
    // The polar coordinate range that defines this emotion zone
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EmotionSystem")
    FPolarCoordinateRange CoordinateRange;
    
    // Optional description of the emotion zone
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EmotionSystem")
    FText Description;
    
    /**
     * Checks if the given VA coordinate is within this emotion zone
     * @param Coordinate - The VA coordinate to check
     * @return True if the coordinate is within this zone, false otherwise
     */
    FORCEINLINE bool ContainCartersianCoordinate(const FPolarCoordinate& Coordinate) const
    {
        return CoordinateRange.ContainCartersianCoordinate(Coordinate.GetCartesianCoordinate());
    }
    
    /**
     * Calculates how strongly a given coordinate is within this zone (0.0 to 1.0)
     * 0.0 means outside the zone, 1.0 means at the center of the zone
     * @param Coordinate - The VA coordinate to check
     * @return The strength value between 0.0 and 1.0
     */
    FORCEINLINE float GetStrengthForCartesianCoordinate(const FPolarCoordinate& Coordinate) const
    {
        return CoordinateRange.GetStrengthForCartesianCoordinate(Coordinate.GetCartesianCoordinate());
    }

};
