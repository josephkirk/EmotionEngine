#include "EmotionSystemLibrary.h"
#include "Engine/AssetManager.h"

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
        Filter.ClassNames.Add(UEmotionLibrary::StaticClass()->GetFName());
        Filter.bRecursiveClasses = true;
        
        AssetManager.GetAssetRegistry().GetAssets(Filter, AssetData);
        
        if (AssetData.Num() > 0)
        {
            DefaultLibrary = Cast<UEmotionLibrary>(AssetData[0].GetAsset());
        }
    }
    
    return DefaultLibrary;
}

UEmotionState* UEmotionSystemLibrary::CreateEmotionState()
{
    return NewObject<UEmotionState>();
}

void UEmotionSystemLibrary::ApplyEmotion(UEmotionState* EmotionState, const FGameplayTag& EmotionTag, float Intensity)
{
    if (EmotionState && EmotionTag.IsValid())
    {
        // Check if it's a core emotion tag
        if (EmotionTag.ToString().StartsWith(TEXT("Emotion.Core")))
        {
            EmotionState->AddCoreEmotionTag(EmotionTag, Intensity);
        }
        else
        {
            EmotionState->SetIntensity(EmotionTag, Intensity);
        }
    }
}

FGameplayTag UEmotionSystemLibrary::GetDominantEmotion(UEmotionState* EmotionState)
{
    if (!EmotionState)
    {
        return FGameplayTag::EmptyTag;
    }
    
    FGameplayTag DominantTag = FGameplayTag::EmptyTag;
    float HighestIntensity = 0.0f;
    
    for (const FGameplayTag& Tag : EmotionState->EmotionTags)
    {
        float Intensity = EmotionState->GetIntensity(Tag);
        if (Intensity > HighestIntensity)
        {
            HighestIntensity = Intensity;
            DominantTag = Tag;
        }
    }
    
    return DominantTag;
}

UEmotionData* UEmotionSystemLibrary::GetEmotionData(const FGameplayTag& EmotionTag, UEmotionLibrary* EmotionLibrary)
{
    if (!EmotionLibrary)
    {
        EmotionLibrary = GetDefaultEmotionLibrary();
    }
    
    if (EmotionLibrary && EmotionTag.IsValid())
    {
        return EmotionLibrary->GetEmotionByTag(EmotionTag);
    }
    
    return nullptr;
}

bool UEmotionSystemLibrary::AreEmotionsOpposite(const FGameplayTag& EmotionTag1, const FGameplayTag& EmotionTag2, UEmotionLibrary* EmotionLibrary)
{
    if (!EmotionLibrary)
    {
        EmotionLibrary = GetDefaultEmotionLibrary();
    }
    
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

bool UEmotionSystemLibrary::AreEmotionsAdjacent(const FGameplayTag& EmotionTag1, const FGameplayTag& EmotionTag2, UEmotionLibrary* EmotionLibrary)
{
    if (!EmotionLibrary)
    {
        EmotionLibrary = GetDefaultEmotionLibrary();
    }
    
    // if (EmotionLibrary && EmotionTag1.IsValid() && EmotionTag2.IsValid())
    // {
    //     UEmotionData* Emotion1 = EmotionLibrary->GetEmotionByTag(EmotionTag1);
    //     if (Emotion1 && Emotion1->Emotion.AdjacentEmotionTags.HasTag(EmotionTag2))
    //     {
    //         return true;
    //     }
        
    //     UEmotionData* Emotion2 = EmotionLibrary->GetEmotionByTag(EmotionTag2);
    //     if (Emotion2 && Emotion2->Emotion.AdjacentEmotionTags.HasTag(EmotionTag1))
    //     {
    //         return true;
    //     }
    // }
    
    return false;
}

FGameplayTag UEmotionSystemLibrary::GetCombinedEmotion(const FGameplayTag& EmotionTag1, const FGameplayTag& EmotionTag2, UEmotionLibrary* EmotionLibrary)
{
    if (!EmotionLibrary)
    {
        EmotionLibrary = GetDefaultEmotionLibrary();
    }
    
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
