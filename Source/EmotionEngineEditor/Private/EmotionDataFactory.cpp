#include "EmotionDataFactory.h"
#include "EmotionEngineEditor.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "JsonObjectConverter.h"
#include "Serialization/JsonSerializer.h"
#include "HAL/FileManager.h"

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

// Emotion Definition Exporter
UEmotionDefinition_Exporter::UEmotionDefinition_Exporter(const class FObjectInitializer& OBJ) : Super(OBJ)
{
    SupportedClass = UEmotionDefinition::StaticClass();
    bText = true;  // We're exporting as text (JSON)
    FormatExtension.Add(TEXT("emo"));
    FormatDescription.Add(TEXT("Emotion Definition JSON File"));
}

bool UEmotionDefinition_Exporter::ExportText(const FExportObjectInnerContext* Context, UObject* Object, const TCHAR* Type, FOutputDevice& Ar, FFeedbackContext* Warn, uint32 PortFlags)
{
    UEmotionDefinition* EmotionDefinition = Cast<UEmotionDefinition>(Object);
    if (!EmotionDefinition)
    {
        return false;
    }
    
    FString JSONString;
    if (!ExportToJSON(EmotionDefinition, JSONString))
    {
        return false;
    }
    
    Ar.Log(*JSONString);
    return true;
}

bool UEmotionDefinition_Exporter::ExportBinary(UObject* Object, const TCHAR* Type, FArchive& Ar, FFeedbackContext* Warn, int32 FileIndex, uint32 PortFlags)
{
    UEmotionDefinition* EmotionDefinition = Cast<UEmotionDefinition>(Object);
    if (!EmotionDefinition)
    {
        return false;
    }
    
    FString JSONString;
    if (!ExportToJSON(EmotionDefinition, JSONString))
    {
        return false;
    }
    
    // Convert the string to UTF8 and write to the archive
    FTCHARToUTF8 UTF8String(*JSONString);
    Ar.Serialize((UTF8CHAR*)UTF8String.Get(), UTF8String.Length());
    
    return true;
}

bool UEmotionDefinition_Exporter::SupportsObject(UObject* Object) const
{
    return Object && Object->IsA(UEmotionDefinition::StaticClass());
}

bool UEmotionDefinition_Exporter::ExportToJSON(const UEmotionDefinition* EmotionDefinition, FString& OutJSONString)
{
    if (!EmotionDefinition)
    {
        return false;
    }
    
    // Create a JSON object to hold the data
    TSharedRef<FJsonObject> JsonObject = MakeShared<FJsonObject>();
    
    // Convert basic properties
    if (!FJsonObjectConverter::UStructToJsonObject(EmotionDefinition->GetClass(), EmotionDefinition, JsonObject, 0, 0))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to convert EmotionDefinition to JSON object"));
        return false;
    }
    
    // Handle special cases for GameplayTags that need to be manually processed
    TSharedPtr<FJsonObject> EmotionObject = JsonObject->GetObjectField(TEXT("Emotion"));
    if (EmotionObject.IsValid())
    {
        // Convert Tag to string
        if (EmotionDefinition->Emotion.Tag.IsValid())
        {
            EmotionObject->SetStringField(TEXT("Tag"), EmotionDefinition->Emotion.Tag.ToString());
        }
        
        // Convert OppositeEmotionTag to string
        if (EmotionDefinition->Emotion.OppositeEmotionTag.IsValid())
        {
            EmotionObject->SetStringField(TEXT("OppositeEmotionTag"), EmotionDefinition->Emotion.OppositeEmotionTag.ToString());
        }
        
        // Process RangeEmotionTags
        TArray<TSharedPtr<FJsonValue>> RangeEmotionsArray;
        for (const FEmotionTriggerRange& TriggerRange : EmotionDefinition->Emotion.RangeEmotionTags)
        {
            TSharedRef<FJsonObject> RangeObject = MakeShared<FJsonObject>();
            
            if (TriggerRange.EmotionTagTriggered.IsValid())
            {
                RangeObject->SetStringField(TEXT("EmotionTagTriggered"), TriggerRange.EmotionTagTriggered.ToString());
            }
            
            RangeObject->SetNumberField(TEXT("Start"), TriggerRange.Start);
            RangeObject->SetNumberField(TEXT("End"), TriggerRange.End);
            
            RangeEmotionsArray.Add(MakeShared<FJsonValueObject>(RangeObject));
        }
        EmotionObject->SetArrayField(TEXT("RangeEmotionTags"), RangeEmotionsArray);
        
        // Process LinkEmotions
        TArray<TSharedPtr<FJsonValue>> LinksArray;
        for (const FEmotionLink& Link : EmotionDefinition->Emotion.LinkEmotions)
        {
            TSharedRef<FJsonObject> LinkObject = MakeShared<FJsonObject>();
            
            if (Link.LinkEmotion.IsValid())
            {
                LinkObject->SetStringField(TEXT("LinkEmotion"), Link.LinkEmotion.ToString());
            }
            
            LinkObject->SetNumberField(TEXT("Threshold"), Link.Threshold);
            
            // Process VariationEmotionTags
            TArray<TSharedPtr<FJsonValue>> VariationsArray;
            for (const FEmotionTriggerRange& TriggerRange : Link.VariationEmotionTags)
            {
                TSharedRef<FJsonObject> VariationObject = MakeShared<FJsonObject>();
                
                if (TriggerRange.EmotionTagTriggered.IsValid())
                {
                    VariationObject->SetStringField(TEXT("EmotionTagTriggered"), TriggerRange.EmotionTagTriggered.ToString());
                }
                
                VariationObject->SetNumberField(TEXT("Start"), TriggerRange.Start);
                VariationObject->SetNumberField(TEXT("End"), TriggerRange.End);
                
                VariationsArray.Add(MakeShared<FJsonValueObject>(VariationObject));
            }
            LinkObject->SetArrayField(TEXT("VariationEmotionTags"), VariationsArray);
            
            LinksArray.Add(MakeShared<FJsonValueObject>(LinkObject));
        }
        EmotionObject->SetArrayField(TEXT("LinkEmotions"), LinksArray);
        
        // Update the Emotion field in the main JSON object
        JsonObject->SetObjectField(TEXT("Emotion"), EmotionObject);
    }
    
    // Serialize the JSON object to a string with pretty formatting
    TSharedRef<TJsonWriter<TCHAR, TPrettyJsonPrintPolicy<TCHAR>>> JsonWriter = TJsonWriterFactory<TCHAR, TPrettyJsonPrintPolicy<TCHAR>>::Create(&OutJSONString);
    if (!FJsonSerializer::Serialize(JsonObject, JsonWriter))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to serialize JSON object to string"));
        return false;
    }
    
    return true;
}
