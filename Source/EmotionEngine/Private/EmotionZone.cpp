#include "EmotionZone.h"

bool FPolarCoordinateRange::ContainsCoordinate(const FVector2D& Coordinate) const
{
    // Calculate the radius (distance from origin)
    const float Radius = Coordinate.Length();
    
    // Check if the radius is within the min and max radius bounds
    if (Radius < MinRadius || Radius > MaxRadius)
    {
        return false;
    }
    
    // Calculate the angle in degrees (0-360)
    float Angle = FMath::RadiansToDegrees(FMath::Atan2(Coordinate.Y, Coordinate.X));
    
    // Ensure angle is in the 0-360 range
    if (Angle < 0.0f)
    {
        Angle += 360.0f;
    }
    
    // Check if the angle is within the start and end angle bounds
    // Handle the case where the angle range wraps around (e.g., 330 to 30 degrees)
    if (StartAngle <= EndAngle)
    {
        // Normal case: StartAngle to EndAngle
        return (Angle >= StartAngle && Angle <= EndAngle);
    }
    else
    {
        // Wrapped case: StartAngle to 360 OR 0 to EndAngle
        return (Angle >= StartAngle || Angle <= EndAngle);
    }
}

float FPolarCoordinateRange::GetStrengthForCoordinate(const FVector2D& Coordinate) const
{
    // If the coordinate is not within this range, return 0
    if (!ContainsCoordinate(Coordinate))
    {
        return 0.0f;
    }
    
    // Calculate the radius (distance from origin)
    const float Radius = Coordinate.Length();
    
    // Calculate the angle in degrees (0-360)
    float Angle = FMath::RadiansToDegrees(FMath::Atan2(Coordinate.Y, Coordinate.X));
    
    // Ensure angle is in the 0-360 range
    if (Angle < 0.0f)
    {
        Angle += 360.0f;
    }
    
    // Calculate the normalized radius position within the min-max range
    // 0 means at MinRadius, 1 means at MaxRadius
    const float RadiusRange = MaxRadius - MinRadius;
    const float NormalizedRadiusPos = RadiusRange > 0.0f ? 
        FMath::Clamp((Radius - MinRadius) / RadiusRange, 0.0f, 1.0f) : 1.0f;
    
    // Calculate the normalized angle position within the start-end range
    // 0 means at StartAngle, 1 means at EndAngle
    float AngleRange;
    float NormalizedAnglePos;
    
    if (StartAngle <= EndAngle)
    {
        // Normal case
        AngleRange = EndAngle - StartAngle;
        NormalizedAnglePos = AngleRange > 0.0f ? 
            FMath::Clamp((Angle - StartAngle) / AngleRange, 0.0f, 1.0f) : 1.0f;
    }
    else
    {
        // Wrapped case
        AngleRange = (360.0f - StartAngle) + EndAngle;
        
        if (Angle >= StartAngle)
        {
            // Angle is between StartAngle and 360
            NormalizedAnglePos = (Angle - StartAngle) / (360.0f - StartAngle);
        }
        else
        {
            // Angle is between 0 and EndAngle
            NormalizedAnglePos = (360.0f - StartAngle + Angle) / AngleRange;
        }
        
        NormalizedAnglePos = FMath::Clamp(NormalizedAnglePos, 0.0f, 1.0f);
    }
    
    // Calculate the distance from the center of the range
    // We define the center as the middle of the radius range and the middle of the angle range
    const float RadiusCenter = (MinRadius + MaxRadius) * 0.5f;
    const float AngleCenter = StartAngle <= EndAngle ?
        (StartAngle + EndAngle) * 0.5f :
        FMath::Fmod((StartAngle + EndAngle + 360.0f) * 0.5f, 360.0f);
    
    // Calculate the normalized distance from the center (0 means at center, 1 means at edge)
    // For radius, the distance is |Radius - RadiusCenter| / (RadiusRange/2)
    const float RadiusDistFromCenter = FMath::Abs(Radius - RadiusCenter) / (RadiusRange * 0.5f);
    
    // For angle, we need to handle the wrapped case
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
