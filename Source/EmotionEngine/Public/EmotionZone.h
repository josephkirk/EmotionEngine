#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Emotion.h"
#include "EmotionZone.generated.h"

/**
 * Defines a range in polar coordinates with minimum and maximum radius and angle range.
 */
USTRUCT(BlueprintType)
struct EMOTIONENGINE_API FPolarCoordinateRange
{
    GENERATED_BODY()

public:
    // The minimum radius from the origin (0.0 to 1.0)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EmotionSystem", meta = (ClampMin = "0.0", ClampMax = "1.0"))
    float MinRadius = 0.0f;
    
    // The maximum radius from the origin (0.0 to 1.0)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EmotionSystem", meta = (ClampMin = "0.0", ClampMax = "1.0"))
    float MaxRadius = 1.0f;
    
    // The starting angle in degrees (0 to 360)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EmotionSystem", meta = (ClampMin = "0.0", ClampMax = "360.0"))
    float StartAngle = 0.0f;
    
    // The ending angle in degrees (0 to 360)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EmotionSystem", meta = (ClampMin = "0.0", ClampMax = "360.0"))
    float EndAngle = 360.0f;
    
    /**
     * Checks if the given coordinate is within this polar coordinate range
     * @param Coordinate - The coordinate as a 2D vector to check
     * @return True if the coordinate is within this range, false otherwise
     */
    FORCEINLINE bool ContainsCoordinate(const FVector2D& Coordinate) const;
    
    /**
     * Calculates how strongly a given coordinate is within this range (0.0 to 1.0)
     * 0.0 means outside the range, 1.0 means at the center of the range
     * @param Coordinate - The coordinate as a 2D vector to check
     * @return The strength value between 0.0 and 1.0
     */
    FORCEINLINE float GetStrengthForCoordinate(const FVector2D& Coordinate) const;
};

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
    FORCEINLINE bool ContainsCoordinate(const FVACoordinate& Coordinate) const
    {
        return CoordinateRange.ContainsCoordinate(Coordinate.GetCoordinate());
    }
    
    /**
     * Checks if the given VA coordinate is within this emotion zone
     * @param Coordinate - The VA coordinate as a 2D vector to check
     * @return True if the coordinate is within this zone, false otherwise
     */
    FORCEINLINE bool ContainsCoordinate(const FVector2D& Coordinate) const
    {
        return CoordinateRange.ContainsCoordinate(Coordinate);
    }
    
    /**
     * Calculates how strongly a given coordinate is within this zone (0.0 to 1.0)
     * 0.0 means outside the zone, 1.0 means at the center of the zone
     * @param Coordinate - The VA coordinate to check
     * @return The strength value between 0.0 and 1.0
     */
    FORCEINLINE float GetStrengthForCoordinate(const FVACoordinate& Coordinate) const
    {
        return CoordinateRange.GetStrengthForCoordinate(Coordinate.GetCoordinate());
    }
    
    /**
     * Calculates how strongly a given coordinate is within this zone (0.0 to 1.0)
     * 0.0 means outside the zone, 1.0 means at the center of the zone
     * @param Coordinate - The VA coordinate as a 2D vector to check
     * @return The strength value between 0.0 and 1.0
     */
    FORCEINLINE float GetStrengthForCoordinate(const FVector2D& Coordinate) const
    {
        return CoordinateRange.GetStrengthForCoordinate(Coordinate);
    }
};
