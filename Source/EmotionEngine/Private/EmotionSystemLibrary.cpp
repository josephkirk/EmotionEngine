#include "EmotionSystemLibrary.h"
#include "Engine/AssetManager.h"
#include "Kismet/GameplayStatics.h"

// Private helper method to get library or default
UEmotionLibrary* UEmotionSystemLibrary::GetLibraryOrDefault(UEmotionLibrary* ProvidedLibrary)
{
    return ProvidedLibrary ? ProvidedLibrary : GetDefaultEmotionLibrary();
}

UEmotionLibrary* UEmotionSystemLibrary::GetDefaultEmotionLibrary()
{
    // Try to find a default emotion library asset
    // This assumes you'll create a default emotion library asset at this path
    static const FSoftObjectPath DefaultEmotionLibraryPath(
        TEXT("/EmotionEngine/EmotionSystem/DefaultEmotionLibrary.DefaultEmotionLibrary"));
    
    UEmotionLibrary* DefaultLibrary = Cast<UEmotionLibrary>(DefaultEmotionLibraryPath.TryLoad());
    
    if (!DefaultLibrary)
    {
        // If no default library is found, try to find any emotion library
        UAssetManager& AssetManager = UAssetManager::Get();
        TArray<FAssetData> AssetData;
        
        FARFilter Filter;
        Filter.ClassPaths.Add(FTopLevelAssetPath(UEmotionLibrary::StaticClass()->GetClassPathName().ToString()));
        Filter.bRecursiveClasses = true;
        
        AssetManager.GetAssetRegistry().GetAssets(Filter, AssetData);
        
        if (AssetData.Num() > 0)
        {
            DefaultLibrary = Cast<UEmotionLibrary>(AssetData[0].GetAsset());
        }
    }
    
    return DefaultLibrary;
}

UEmotionState* UEmotionSystemLibrary::CreateEmotionState(UEmotionLibrary* EmotionLibrary)
{
    UEmotionState* NewState = NewObject<UEmotionState>();
    
    if (!EmotionLibrary)
    {
        EmotionLibrary = GetDefaultEmotionLibrary();
    }
    
    if (NewState && EmotionLibrary)
    {
        NewState->Initialize(EmotionLibrary);
    }
    
    return NewState;
}

void UEmotionSystemLibrary::ApplyEmotion(UEmotionState* EmotionState, const FGameplayTag& EmotionTag, float Intensity)
{
    if (EmotionState && EmotionTag.IsValid())
    {
        // Add the emotion to the state
        EmotionState->AddEmotion(EmotionTag, Intensity);
    }
}

void UEmotionSystemLibrary::GetDominantEmotion(UEmotionState* EmotionState, FGameplayTag& OutEmotionTag, float& OutIntensity)
{
    OutEmotionTag = FGameplayTag::EmptyTag;
    OutIntensity = 0.0f;
    
    if (EmotionState)
    {
        EmotionState->GetDominantEmotion(OutEmotionTag, OutIntensity);
    }
}

UEmotionData* UEmotionSystemLibrary::GetEmotionData(const FGameplayTag& EmotionTag, UEmotionLibrary* EmotionLibrary)
{
    EmotionLibrary = GetLibraryOrDefault(EmotionLibrary);
    
    if (EmotionLibrary && EmotionTag.IsValid())
    {
        return EmotionLibrary->GetEmotionByTag(EmotionTag);
    }
    
    return nullptr;
}

bool UEmotionSystemLibrary::AreEmotionsOpposite(const FGameplayTag& EmotionTag1, const FGameplayTag& EmotionTag2, UEmotionLibrary* EmotionLibrary)
{
    EmotionLibrary = GetLibraryOrDefault(EmotionLibrary);
    
    if (EmotionLibrary && EmotionTag1.IsValid() && EmotionTag2.IsValid())
    {
        UEmotionData* Emotion1 = EmotionLibrary->GetEmotionByTag(EmotionTag1);
        if (Emotion1 && Emotion1->Emotion.OppositeEmotionTag == EmotionTag2)
        {
            return true;
        }
        
        UEmotionData* Emotion2 = EmotionLibrary->GetEmotionByTag(EmotionTag2);
        if (Emotion2 && Emotion2->Emotion.OppositeEmotionTag == EmotionTag1)
        {
            return true;
        }
    }
    
    return false;
}

bool UEmotionSystemLibrary::AreEmotionsAdjacent(const FGameplayTag& EmotionTag1, const FGameplayTag& EmotionTag2, float MaxDistance, UEmotionLibrary* EmotionLibrary)
{
    // Use GetEmotionDistance to avoid code duplication
    float Distance = GetEmotionDistance(EmotionTag1, EmotionTag2, EmotionLibrary);
    
    // If distance is valid and less than MaxDistance, consider them adjacent
    return (Distance >= 0.0f) && (Distance <= MaxDistance);
}

FGameplayTag UEmotionSystemLibrary::GetCombinedEmotion(const FGameplayTag& EmotionTag1, const FGameplayTag& EmotionTag2, UEmotionLibrary* EmotionLibrary)
{
    EmotionLibrary = GetLibraryOrDefault(EmotionLibrary);
    
    if (EmotionLibrary && EmotionTag1.IsValid() && EmotionTag2.IsValid())
    {
        UEmotionData* CombinedEmotion = EmotionLibrary->GetCombinedEmotion(EmotionTag1, EmotionTag2);
        if (CombinedEmotion)
        {
            return CombinedEmotion->Emotion.Tag;
        }
    }
    
    return FGameplayTag::EmptyTag;
}

FVector2D UEmotionSystemLibrary::GetEmotionVACoordinate(const FGameplayTag& EmotionTag, UEmotionLibrary* EmotionLibrary)
{
    EmotionLibrary = GetLibraryOrDefault(EmotionLibrary);
    
    if (EmotionLibrary && EmotionTag.IsValid())
    {
        UEmotionData* EmotionData = EmotionLibrary->GetEmotionByTag(EmotionTag);
        if (EmotionData)
        {
            return EmotionData->Emotion.VACoordinate;
        }
    }
    
    return FVector2D::ZeroVector;
}

TArray<UEmotionData*> UEmotionSystemLibrary::GetEmotionsInRadius(const FVector2D& VACoordinate, float Radius, UEmotionLibrary* EmotionLibrary)
{
    EmotionLibrary = GetLibraryOrDefault(EmotionLibrary);
    
    if (EmotionLibrary)
    {
        return EmotionLibrary->FindEmotionsInRadius(VACoordinate, Radius);
    }
    
    return TArray<UEmotionData*>();
}

float UEmotionSystemLibrary::GetEmotionDistance(const FGameplayTag& EmotionTag1, const FGameplayTag& EmotionTag2, UEmotionLibrary* EmotionLibrary)
{
    EmotionLibrary = GetLibraryOrDefault(EmotionLibrary);
    
    if (EmotionLibrary && EmotionTag1.IsValid() && EmotionTag2.IsValid())
    {
        UEmotionData* Emotion1 = EmotionLibrary->GetEmotionByTag(EmotionTag1);
        UEmotionData* Emotion2 = EmotionLibrary->GetEmotionByTag(EmotionTag2);
        
        if (Emotion1 && Emotion2)
        {
            // Calculate distance between emotions in VA space
            FVector2D VA1 = Emotion1->Emotion.VACoordinate;
            FVector2D VA2 = Emotion2->Emotion.VACoordinate;
            
            return FVector2D::Distance(VA1, VA2);
        }
    }
    
    return -1.0f; // Invalid distance
}

void UEmotionSystemLibrary::ApplyEmotionalStimulus(UEmotionComponent* EmotionComponent, const FGameplayTag& EmotionTag, float Intensity)
{
    if (EmotionComponent && EmotionTag.IsValid())
    {
        EmotionComponent->ApplyEmotionalStimulus(EmotionTag, Intensity);
    }
}

TArray<FActiveEmotion> UEmotionSystemLibrary::GetActiveEmotions(UEmotionState* EmotionState)
{
    if (EmotionState)
    {
        return EmotionState->GetActiveEmotions();
    }
    
    return TArray<FActiveEmotion>();
}

FVector2D UEmotionSystemLibrary::GetStateVACoordinate(UEmotionState* EmotionState)
{
    if (EmotionState)
    {
        return EmotionState->VACoordinate;
    }
    
    return FVector2D::ZeroVector;
}

void UEmotionSystemLibrary::SetStateVACoordinate(UEmotionState* EmotionState, const FVector2D& NewVACoordinate)
{
    if (EmotionState)
    {
        EmotionState->VACoordinate = NewVACoordinate;
    }
}

UEmotionData* UEmotionSystemLibrary::FindClosestEmotion(const FVector2D& VACoordinate, UEmotionLibrary* EmotionLibrary)
{
    EmotionLibrary = GetLibraryOrDefault(EmotionLibrary);
    
    if (EmotionLibrary)
    {
        UEmotionData* ClosestEmotion = nullptr;
        float ClosestDistance = MAX_FLT;
        
        // Check all emotions in the library
        for (UEmotionData* EmotionData : EmotionLibrary->Emotions)
        {
            if (EmotionData)
            {
                float Distance = FVector2D::Distance(EmotionData->Emotion.VACoordinate, VACoordinate);
                
                if (Distance < ClosestDistance)
                {
                    ClosestDistance = Distance;
                    ClosestEmotion = EmotionData;
                }
            }
        }
        
        return ClosestEmotion;
    }
    
    return nullptr;
}
