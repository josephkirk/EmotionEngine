#include "EmotionDataFactory.h"
#include "EmotionEngineEditor.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "JsonObjectConverter.h"

// Emotion Data Factory
UEmotionDefinition_Factory::UEmotionDefinition_Factory(const class FObjectInitializer& OBJ) : Super(OBJ)
{
    bCreateNew = true;
    bEditAfterNew = true;
    bEditorImport = true;
    SupportedClass = UEmotionDefinition::StaticClass();
    
    // Set up supported formats
    Formats.Add(TEXT("emo;Emotion Definition JSON File"));
}

UObject* UEmotionDefinition_Factory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
    UEmotionDefinition* NewEmotionData = NewObject<UEmotionDefinition>(InParent, UEmotionDefinition::StaticClass(), InName, Flags | RF_Transactional, Context);
    return NewEmotionData;
}

UObject* UEmotionDefinition_Factory::FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled)
{
    // Create a new EmotionDefinition object
    UEmotionDefinition* NewEmotionData = NewObject<UEmotionDefinition>(InParent, UEmotionDefinition::StaticClass(), InName, Flags | RF_Transactional);
    
    if (!NewEmotionData)
    {
        bOutOperationCanceled = true;
        return nullptr;
    }
    
    // Read the file content
    FString FileContent;
    if (!FFileHelper::LoadFileToString(FileContent, *Filename))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to load file: %s"), *Filename);
        bOutOperationCanceled = true;
        return nullptr;
    }
    
    // Import the JSON data into the EmotionDefinition
    if (!ImportFromJSON(FileContent, NewEmotionData))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to import JSON from file: %s"), *Filename);
        bOutOperationCanceled = true;
        return nullptr;
    }
    
    bOutOperationCanceled = false;
    return NewEmotionData;
}

bool UEmotionDefinition_Factory::FactoryCanImport(const FString& Filename)
{
    const FString Extension = FPaths::GetExtension(Filename).ToLower();
    return Extension == TEXT("emo");
}

bool UEmotionDefinition_Factory::ImportFromJSON(const FString& JSONString, UEmotionDefinition* EmotionDefinition)
{
    if (!EmotionDefinition)
    {
        return false;
    }
    
    // Parse the JSON string into a JSON object
    TSharedPtr<FJsonObject> JsonObject;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JSONString);
    
    if (!FJsonSerializer::Deserialize(Reader, JsonObject) || !JsonObject.IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to parse JSON data"));
        return false;
    }
    
    // Convert the JSON object to the UEmotionDefinition
    FText FailReason;
    bool bSuccess = FJsonObjectConverter::JsonObjectToUStruct(JsonObject.ToSharedRef(), EmotionDefinition->GetClass(), EmotionDefinition, 0, 0, false, &FailReason);
    
    if (!bSuccess)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to convert JSON to EmotionDefinition: %s"), *FailReason.ToString());
        return false;
    }
    
    // Handle special cases for GameplayTags that need to be requested
    // Since JsonObjectConverter doesn't handle GameplayTags directly, we need to process them manually
    
    // Process the main emotion tag
    if (JsonObject->HasField(TEXT("Emotion")))
    {
        const TSharedPtr<FJsonObject>* EmotionObject;
        if (JsonObject->TryGetObjectField(TEXT("Emotion"), EmotionObject))
        {
            // Process Tag
            if ((*EmotionObject)->HasField(TEXT("Tag")))
            {
                const FString TagString = (*EmotionObject)->GetStringField(TEXT("Tag"));
                EmotionDefinition->Emotion.Tag = FGameplayTag::RequestGameplayTag(FName(*TagString));
            }
            
            // Process OppositeEmotionTag
            if ((*EmotionObject)->HasField(TEXT("OppositeEmotionTag")))
            {
                const FString OppositeTagString = (*EmotionObject)->GetStringField(TEXT("OppositeEmotionTag"));
                EmotionDefinition->Emotion.OppositeEmotionTag = FGameplayTag::RequestGameplayTag(FName(*OppositeTagString));
            }
            
            // Process RangeEmotionTags
            const TArray<TSharedPtr<FJsonValue>>* RangeEmotionsArray;
            if ((*EmotionObject)->TryGetArrayField(TEXT("RangeEmotionTags"), RangeEmotionsArray))
            {
                for (int32 i = 0; i < EmotionDefinition->Emotion.RangeEmotionTags.Num(); i++)
                {
                    if (i < RangeEmotionsArray->Num())
                    {
                        const TSharedPtr<FJsonObject>& RangeObject = (*RangeEmotionsArray)[i]->AsObject();
                        if (RangeObject->HasField(TEXT("EmotionTagTriggered")))
                        {
                            const FString TagString = RangeObject->GetStringField(TEXT("EmotionTagTriggered"));
                            EmotionDefinition->Emotion.RangeEmotionTags[i].EmotionTagTriggered = FGameplayTag::RequestGameplayTag(FName(*TagString));
                        }
                    }
                }
            }
            
            // Process LinkEmotions
            const TArray<TSharedPtr<FJsonValue>>* LinksArray;
            if ((*EmotionObject)->TryGetArrayField(TEXT("LinkEmotions"), LinksArray))
            {
                for (int32 i = 0; i < EmotionDefinition->Emotion.LinkEmotions.Num(); i++)
                {
                    if (i < LinksArray->Num())
                    {
                        const TSharedPtr<FJsonObject>& LinkObject = (*LinksArray)[i]->AsObject();
                        
                        // Process LinkEmotion tag
                        if (LinkObject->HasField(TEXT("LinkEmotion")))
                        {
                            const FString TagString = LinkObject->GetStringField(TEXT("LinkEmotion"));
                            EmotionDefinition->Emotion.LinkEmotions[i].LinkEmotion = FGameplayTag::RequestGameplayTag(FName(*TagString));
                        }
                        
                        // Process VariationEmotionTags
                        const TArray<TSharedPtr<FJsonValue>>* VariationsArray;
                        if (LinkObject->TryGetArrayField(TEXT("VariationEmotionTags"), VariationsArray))
                        {
                            for (int32 j = 0; j < EmotionDefinition->Emotion.LinkEmotions[i].VariationEmotionTags.Num(); j++)
                            {
                                if (j < VariationsArray->Num())
                                {
                                    const TSharedPtr<FJsonObject>& VariationObject = (*VariationsArray)[j]->AsObject();
                                    if (VariationObject->HasField(TEXT("EmotionTagTriggered")))
                                    {
                                        const FString TagString = VariationObject->GetStringField(TEXT("EmotionTagTriggered"));
                                        EmotionDefinition->Emotion.LinkEmotions[i].VariationEmotionTags[j].EmotionTagTriggered = 
                                            FGameplayTag::RequestGameplayTag(FName(*TagString));
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    return true;
}

bool UEmotionDefinition_Factory::ShouldShowInNewMenu() const
{
    return true;
}

uint32 UEmotionDefinition_Factory::GetMenuCategories() const
{
    return EAssetTypeCategories::Gameplay;
}

// Emotion Library Factory
UEmotionLibrary_Factory::UEmotionLibrary_Factory(const class FObjectInitializer& OBJ) : Super(OBJ)
{
    bCreateNew = true;
    bEditAfterNew = true;
    SupportedClass = UEmotionLibrary::StaticClass();
}

UObject* UEmotionLibrary_Factory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
    UEmotionLibrary* NewEmotionLibrary = NewObject<UEmotionLibrary>(InParent, UEmotionLibrary::StaticClass(), InName, Flags | RF_Transactional, Context);
    return NewEmotionLibrary;
}

bool UEmotionLibrary_Factory::ShouldShowInNewMenu() const
{
    return true;
}

uint32 UEmotionLibrary_Factory::GetMenuCategories() const
{
    return EAssetTypeCategories::Gameplay;
}
