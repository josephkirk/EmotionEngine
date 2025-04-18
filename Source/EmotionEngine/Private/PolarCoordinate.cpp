#include "PolarCoordinate.h"
#include "Kismet/BlueprintFunctionLibrary.h"

bool FPolarCoordinateRange::ContainCartersianCoordinate(const FVector2D& Coordinate) const
{
    // Calculate the radius (distance from origin)
    const float Radius = Coordinate.Length();
    float NormalizeStartAngle = UPolarCoordinateLibrary::NormalizeAngle(StartAngle);
    float NormalizeEndAngle = UPolarCoordinateLibrary::NormalizeAngle(EndAngle);
    
    // swap if NormalizeStartAngle > NormalizeEndAngle
    if (NormalizeStartAngle > NormalizeEndAngle)
    {
        float Temp = NormalizeStartAngle;
        NormalizeStartAngle = NormalizeEndAngle;
        NormalizeEndAngle = Temp;
    }
    
    // Check if the radius is within the min and max radius bounds
    if (Radius < MinRadius || Radius > MaxRadius)
    {
        return false;
    }
    
    // Calculate the angle in degrees (0-360)
    float Angle = UPolarCoordinateLibrary::NormalizeAngle(FMath::RadiansToDegrees(FMath::Atan2(Coordinate.Y, Coordinate.X)));
    
    return (Angle >= NormalizeStartAngle && Angle <= NormalizeEndAngle);
}

bool FPolarCoordinateRange::ContainCoordinate(const FPolarCoordinate& Coordinate) const
{
    // Check if the intensity (radius) is within the min and max radius bounds
    if (Coordinate.Intensity < MinRadius || Coordinate.Intensity > MaxRadius)
    {
        return false;
    }
    float NormalizeStartAngle = UPolarCoordinateLibrary::NormalizeAngle(StartAngle);
    float NormalizeEndAngle = UPolarCoordinateLibrary::NormalizeAngle(EndAngle);
    
    // swap if NormalizeStartAngle > NormalizeEndAngle
    if (NormalizeStartAngle > NormalizeEndAngle)
    {
        float Temp = NormalizeStartAngle;
        NormalizeStartAngle = NormalizeEndAngle;
        NormalizeEndAngle = Temp;
    }
    
    // Calculate the angle in degrees (0-360)
    float Angle = UPolarCoordinateLibrary::NormalizeAngle(Coordinate.Angle);
    
    return (Angle >= NormalizeStartAngle && Angle <= NormalizeEndAngle);
}

float FPolarCoordinateRange::GetStrengthForCartesianCoordinate(const FVector2D& Coordinate) const
{
    // If the coordinate is not within this range, return 0
    if (!ContainCartersianCoordinate(Coordinate))
    {
        return 0.0f;
    }
    
    // Calculate the radius (distance from origin)
    const float Radius = Coordinate.Length();
    
    // Normalize the range angles
    float NormalizeStartAngle = UPolarCoordinateLibrary::NormalizeAngle(StartAngle);
    float NormalizeEndAngle = UPolarCoordinateLibrary::NormalizeAngle(EndAngle);
    
    // Swap if NormalizeStartAngle > NormalizeEndAngle
    if (NormalizeStartAngle > NormalizeEndAngle)
    {
        float Temp = NormalizeStartAngle;
        NormalizeStartAngle = NormalizeEndAngle;
        NormalizeEndAngle = Temp;
    }
    
    // Calculate the angle in degrees (0-360)
    float Angle = UPolarCoordinateLibrary::NormalizeAngle(FMath::RadiansToDegrees(FMath::Atan2(Coordinate.Y, Coordinate.X)));
    
    // Calculate the normalized radius position within the min-max range
    // 0 means at MinRadius, 1 means at MaxRadius
    const float RadiusRange = MaxRadius - MinRadius;
    const float NormalizedRadiusPos = RadiusRange > 0.0f ? 
        FMath::Clamp((Radius - MinRadius) / RadiusRange, 0.0f, 1.0f) : 1.0f;
    
    // Calculate the normalized angle position within the start-end range
    // 0 means at StartAngle, 1 means at EndAngle
    const float AngleRange = NormalizeEndAngle - NormalizeStartAngle;
    const float NormalizedAnglePos = AngleRange > 0.0f ? 
        FMath::Clamp((Angle - NormalizeStartAngle) / AngleRange, 0.0f, 1.0f) : 1.0f;
    
    // Calculate the distance from the center of the range
    // We define the center as the middle of the radius range and the middle of the angle range
    const float RadiusCenter = (MinRadius + MaxRadius) * 0.5f;
    const float AngleCenter = (NormalizeStartAngle + NormalizeEndAngle) * 0.5f;
    
    // Calculate the normalized distance from the center (0 means at center, 1 means at edge)
    // For radius, the distance is |Radius - RadiusCenter| / (RadiusRange/2)
    const float RadiusDistFromCenter = RadiusRange > 0.0f ?
        FMath::Clamp(FMath::Abs(Radius - RadiusCenter) / (RadiusRange * 0.5f), 0.0f, 1.0f) : 0.0f;
    
    // For angle, we need to handle the shortest path
    float AngleDiff = FMath::Abs(Angle - AngleCenter);
    if (AngleDiff > 180.0f)
    {
        AngleDiff = 360.0f - AngleDiff;
    }
    const float AngleDistFromCenter = AngleRange > 0.0f ? 
        FMath::Clamp(AngleDiff / (AngleRange * 0.5f), 0.0f, 1.0f) : 0.0f;
    
    // Combine the radius and angle distances to get the overall distance from center
    // Use a weighted average of the two distances
    const float DistFromCenter = (RadiusDistFromCenter + AngleDistFromCenter) * 0.5f;
    
    // Convert distance from center to strength (1 at center, 0 at edge)
    return 1.0f - DistFromCenter;
}

// UPolarCoordinateLibrary implementation

float UPolarCoordinateLibrary::NormalizeAngle(float Angle)
{
    // Normalize angle to 0-360 range
    float NewAngle = FMath::Fmod(Angle, 360.0f);
    if(NewAngle < 0.0f)
    {
        NewAngle += 360.0f;
    }
    return NewAngle;
}

FPolarCoordinate UPolarCoordinateLibrary::MakePolarCoordinate(float Angle, float Intensity)
{
    FPolarCoordinate Result;
    Result.Angle = NormalizeAngle(Angle);
    Result.Intensity = FMath::Max(0.0f, Intensity);  // Ensure intensity is not negative
    return Result;
}

FVector2D UPolarCoordinateLibrary::PolarToCartesian(const FPolarCoordinate& PolarCoordinate)
{
    return PolarCoordinate.GetCartesianCoordinate();
}

FPolarCoordinate UPolarCoordinateLibrary::CartesianToPolar(const FVector2D& CartesianCoordinate)
{
    FPolarCoordinate Result;
    
    // Calculate intensity (radius)
    Result.Intensity = CartesianCoordinate.Length();
    
    // Calculate angle in degrees (0-360)
    if (Result.Intensity > SMALL_NUMBER)  // Avoid division by zero
    {
        Result.Angle = FMath::RadiansToDegrees(FMath::Atan2(CartesianCoordinate.Y, CartesianCoordinate.X));
        Result.Angle = NormalizeAngle(Result.Angle);
    }
    else
    {
        Result.Angle = 0.0f;
    }
    
    return Result;
}

bool UPolarCoordinateLibrary::IsCoordinateInRange(const FPolarCoordinate& Coordinate, const FPolarCoordinateRange& Range)
{
    return Range.ContainCoordinate(Coordinate);
}

bool UPolarCoordinateLibrary::IsCartesianCoordinateInRange(const FVector2D& Coordinate, const FPolarCoordinateRange& Range)
{
    return Range.ContainCartersianCoordinate(Coordinate);
}

float UPolarCoordinateLibrary::GetCoordinateStrengthInRange(const FVector2D& Coordinate, const FPolarCoordinateRange& Range)
{
    return Range.GetStrengthForCartesianCoordinate(Coordinate);
}

FPolarCoordinateRange UPolarCoordinateLibrary::MakePolarCoordinateRange(float MinRadius, float MaxRadius, float StartAngle, float EndAngle)
{
    FPolarCoordinateRange Result;
    Result.MinRadius = FMath::Clamp(MinRadius, 0.0f, 1.0f);
    Result.MaxRadius = FMath::Clamp(MaxRadius, Result.MinRadius, 1.0f);  // Ensure MaxRadius >= MinRadius
    Result.StartAngle = NormalizeAngle(StartAngle);
    Result.EndAngle = NormalizeAngle(EndAngle);
    return Result;
}

float UPolarCoordinateLibrary::GetPolarDistance(const FPolarCoordinate& A, const FPolarCoordinate& B)
{
    // Convert to cartesian coordinates and calculate Euclidean distance
    FVector2D CartesianA = A.GetCartesianCoordinate();
    FVector2D CartesianB = B.GetCartesianCoordinate();
    return FVector2D::Distance(CartesianA, CartesianB);
}

float UPolarCoordinateLibrary::GetAngleDifference(const FPolarCoordinate& A, const FPolarCoordinate& B)
{
    float AngleDiff = FMath::Abs(A.Angle - B.Angle);
    
    // Take the shorter path around the circle
    if (AngleDiff > 180.0f)
    {
        AngleDiff = 360.0f - AngleDiff;
    }
    
    return AngleDiff;
}

FPolarCoordinate UPolarCoordinateLibrary::InterpolatePolarCoordinates(const FPolarCoordinate& A, const FPolarCoordinate& B, float Alpha)
{
    // Clamp alpha to 0-1 range
    Alpha = FMath::Clamp(Alpha, 0.0f, 1.0f);
    
    FPolarCoordinate Result;
    
    // Interpolate intensity linearly
    Result.Intensity = FMath::Lerp(A.Intensity, B.Intensity, Alpha);
    
    // For angle, we need to handle the case where the shortest path crosses the 0/360 boundary
    float AngleA = A.Angle;
    float AngleB = B.Angle;
    
    // Determine if we need to adjust angles for shortest path interpolation
    if (FMath::Abs(AngleA - AngleB) > 180.0f)
    {
        // Adjust one of the angles to ensure shortest path
        if (AngleA < AngleB)
        {
            AngleA += 360.0f;
        }
        else
        {
            AngleB += 360.0f;
        }
    }
    
    // Interpolate angle
    Result.Angle = NormalizeAngle(FMath::Lerp(AngleA, AngleB, Alpha));
    
    return Result;
}

FPolarCoordinate UPolarCoordinateLibrary::GetRangeCenter(const FPolarCoordinateRange& Range)
{
    FPolarCoordinate Result;
    
    // Center radius is the average of min and max radius
    Result.Intensity = (Range.MinRadius + Range.MaxRadius) * 0.5f;
    
    // For angle, we need to handle the case where the range wraps around
    if (Range.StartAngle <= Range.EndAngle)
    {
        // Normal case
        Result.Angle = (Range.StartAngle + Range.EndAngle) * 0.5f;
    }
    else
    {
        // Wrapped case
        Result.Angle = NormalizeAngle((Range.StartAngle + Range.EndAngle + 360.0f) * 0.5f);
    }
    
    return Result;
}
