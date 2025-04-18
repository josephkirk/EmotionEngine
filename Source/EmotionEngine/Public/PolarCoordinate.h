#pragma once

#include "CoreMinimal.h"

USTRUCT(BlueprintType)
struct EMOTIONENGINE_API FPolarCoordinate
{
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EmotionSystem")
    float Angle = 0.0f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EmotionSystem")
    float Intensity = 1.0f;

    FORCEINLINE FVector2D GetCartesianCoordinate() const
    {
		return FVector2D(FMath::Cos(FMath::DegreesToRadians(Angle)), FMath::Sin(FMath::DegreesToRadians(Angle))) * Intensity;
	}
};

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
     FORCEINLINE bool ContainCartersianCoordinate(const FVector2D& Coordinate) const;
     
     /**
      * Calculates how strongly a given coordinate is within this range (0.0 to 1.0)
      * 0.0 means outside the range, 1.0 means at the center of the range
      * @param Coordinate - The coordinate as a 2D vector to check
      * @return The strength value between 0.0 and 1.0
      */
     FORCEINLINE float GetStrengthForCartesianCoordinate(const FVector2D& Coordinate) const;
 };