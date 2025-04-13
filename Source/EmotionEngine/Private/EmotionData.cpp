#include "EmotionData.h"

UEmotionData* UEmotionLibrary::GetEmotionByTag(const FGameplayTag& EmotionTag) const
{
    for (UEmotionData* EmotionData : Emotions)
    {
        if (EmotionData && EmotionData->Emotion.Tag == EmotionTag)
        {
            return EmotionData;
        }
    }
    return nullptr;
}

TArray<UEmotionData*> UEmotionLibrary::GetOppositeEmotions(const FGameplayTag& EmotionTag) const
{
    TArray<UEmotionData*> Result;
    UEmotionData* SourceEmotion = GetEmotionByTag(EmotionTag);
    
    if (SourceEmotion)
    {
        // Get the direct opposite
        if (SourceEmotion->Emotion.OppositeEmotionTag.IsValid())
        {
            UEmotionData* OppositeEmotion = GetEmotionByTag(SourceEmotion->Emotion.OppositeEmotionTag);
            if (OppositeEmotion)
            {
                Result.Add(OppositeEmotion);
            }
        }
    }
    
    return Result;
}

TArray<UEmotionData*> UEmotionLibrary::GetAdjacentEmotions(const FGameplayTag& EmotionTag) const
{
    TArray<UEmotionData*> Result;
    UEmotionData* SourceEmotion = GetEmotionByTag(EmotionTag);
    
    // if (SourceEmotion)
    // {
    //     // Get all adjacent emotions
    //     for (const FGameplayTag& AdjacentTag : SourceEmotion->Emotion.AdjacentEmotionTags)
    //     {
    //         UEmotionData* AdjacentEmotion = GetEmotionByTag(AdjacentTag);
    //         if (AdjacentEmotion)
    //         {
    //             Result.Add(AdjacentEmotion);
    //         }
    //     }
    // }
    
    return Result;
}

UEmotionData* UEmotionLibrary::GetCombinedEmotion(const FGameplayTag& EmotionTag1, const FGameplayTag& EmotionTag2) const
{
    UEmotionData* Emotion1 = GetEmotionByTag(EmotionTag1);
    
    //if (Emotion1)
    //{
    //    // Check if this emotion has a defined combination with the second emotion
    //    const FGameplayTag* CombinedTag = Emotion1->Emotion.CombinedEmotionTag.Find(EmotionTag2);
    //    if (CombinedTag && CombinedTag->IsValid())
    //    {
    //        return GetEmotionByTag(*CombinedTag);
    //    }
    //}
    //
    //// Also check the reverse combination (Emotion2 + Emotion1)
    //UEmotionData* Emotion2 = GetEmotionByTag(EmotionTag2);
    //if (Emotion2)
    //{
    //    const FGameplayTag* CombinedTag = Emotion2->Emotion.CombinedEmotionTag.Find(EmotionTag1);
    //    if (CombinedTag && CombinedTag->IsValid())
    //    {
    //        return GetEmotionByTag(*CombinedTag);
    //    }
    //}
    
    return nullptr;
}
