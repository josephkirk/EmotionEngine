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
     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EmotionSystem", meta = (ClampMin = "-360.0", ClampMax = "360.0"))
     float StartAngle = 0.0f;
     
     // The ending angle in degrees (0 to 360)
     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EmotionSystem", meta = (ClampMin = "-360.0", ClampMax = "360.0"))
     float EndAngle = 360.0f;
     
     /**
      * Checks if the given coordinate is within this polar coordinate range
      * @param Coordinate - The coordinate as a 2D vector to check
      * @return True if the coordinate is within this range, false otherwise
      */
     FORCEINLINE bool ContainCartersianCoordinate(const FVector2D& Coordinate) const;
     
     /**
      * Checks if the given polar coordinate is within this polar coordinate range
      * @param Coordinate - The polar coordinate to check
      * @return True if the coordinate is within this range, false otherwise
      */
     FORCEINLINE bool ContainCoordinate(const FPolarCoordinate& Coordinate) const;
     
     /**
      * Calculates how strongly a given coordinate is within this range (0.0 to 1.0)
      * 0.0 means outside the range, 1.0 means at the center of the range
      * @param Coordinate - The coordinate as a 2D vector to check
      * @return The strength value between 0.0 and 1.0
      */
     FORCEINLINE float GetStrengthForCartesianCoordinate(const FVector2D& Coordinate) const;
 };

/**
 * Blueprint function library for working with polar coordinates and ranges
 */
UCLASS()
class EMOTIONENGINE_API UPolarCoordinateLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    /** Normalizes an angle to the range [0, 360) */
    UFUNCTION(BlueprintPure, Category = "EmotionSystem|PolarCoordinate")
    static float NormalizeAngle(float Angle);
    
    /** Creates a polar coordinate from angle and intensity */
    UFUNCTION(BlueprintPure, Category = "EmotionSystem|PolarCoordinate")
    static FPolarCoordinate MakePolarCoordinate(float Angle, float Intensity = 1.0f);
    
    /** Converts a polar coordinate to a cartesian (X,Y) coordinate */
    UFUNCTION(BlueprintPure, Category = "EmotionSystem|PolarCoordinate")
    static FVector2D PolarToCartesian(const FPolarCoordinate& PolarCoordinate);
    
    /** Converts a cartesian (X,Y) coordinate to a polar coordinate */
    UFUNCTION(BlueprintPure, Category = "EmotionSystem|PolarCoordinate")
    static FPolarCoordinate CartesianToPolar(const FVector2D& CartesianCoordinate);
    
    /** Checks if a polar coordinate is within a polar coordinate range */
    UFUNCTION(BlueprintPure, Category = "EmotionSystem|PolarCoordinate")
    static bool IsCoordinateInRange(const FPolarCoordinate& Coordinate, const FPolarCoordinateRange& Range);
    
    /** Checks if a cartesian coordinate is within a polar coordinate range */
    UFUNCTION(BlueprintPure, Category = "EmotionSystem|PolarCoordinate")
    static bool IsCartesianCoordinateInRange(const FVector2D& Coordinate, const FPolarCoordinateRange& Range);
    
    /** Gets the strength of a coordinate within a range (0-1) */
    UFUNCTION(BlueprintPure, Category = "EmotionSystem|PolarCoordinate")
    static float GetCoordinateStrengthInRange(const FVector2D& Coordinate, const FPolarCoordinateRange& Range);
    
    /** Creates a polar coordinate range */
    UFUNCTION(BlueprintPure, Category = "EmotionSystem|PolarCoordinate")
    static FPolarCoordinateRange MakePolarCoordinateRange(float MinRadius, float MaxRadius, float StartAngle, float EndAngle);
    
    /** Gets the distance between two polar coordinates */
    UFUNCTION(BlueprintPure, Category = "EmotionSystem|PolarCoordinate")
    static float GetPolarDistance(const FPolarCoordinate& A, const FPolarCoordinate& B);
    
    /** Gets the angle difference between two polar coordinates (shortest path) */
    UFUNCTION(BlueprintPure, Category = "EmotionSystem|PolarCoordinate")
    static float GetAngleDifference(const FPolarCoordinate& A, const FPolarCoordinate& B);
    
    /** Interpolates between two polar coordinates */
    UFUNCTION(BlueprintPure, Category = "EmotionSystem|PolarCoordinate")
    static FPolarCoordinate InterpolatePolarCoordinates(const FPolarCoordinate& A, const FPolarCoordinate& B, float Alpha);
    
    /** Calculates the center point of a polar coordinate range */
    UFUNCTION(BlueprintPure, Category = "EmotionSystem|PolarCoordinate")
    static FPolarCoordinate GetRangeCenter(const FPolarCoordinateRange& Range);
};