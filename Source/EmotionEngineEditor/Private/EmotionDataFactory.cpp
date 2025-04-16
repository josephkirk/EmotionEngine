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

UObject* UEmotionDefinition_Factory::ImportObject(UClass* InClass, UObject* InOuter, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, bool& OutCanceled)
{
    UObject* Result = nullptr;
    AdditionalImportedObjects.Empty();
    CurrentFilename = Filename;
    
    
    // sanity check the file size of the impending import and prompt
    // the user if they wish to continue if the file size is very large
    const int64 FileSize = IFileManager::Get().FileSize(*CurrentFilename);
    
    const int32 Gigabyte = 1024 * 1024 * 1024;
    if(FileSize < Gigabyte)
    {
        FileHash = FMD5Hash::HashFile(*CurrentFilename);
    }

    if (CanCreateNew() && Filename.IsEmpty())
    {
        UE_LOG(LogTemp, Log, TEXT("EmotionFactoryCreateNew: %s with %s (%i %i %s)"), *InClass->GetName(), *GetClass()->GetName(), bCreateNew, bText, *Filename);
        ParseParms(Parms);

        Result = FactoryCreateNew(InClass, InOuter, InName, Flags, nullptr, GWarn);
    }
    else if (!Filename.IsEmpty())
    {
        if (FileSize != INDEX_NONE)
        {
            UE_LOG(LogTemp, Log, TEXT("EmotionFactoryCreateFile: %s with %s (%i %i %s)"), *InClass->GetName(), *GetClass()->GetName(), bCreateNew, bText, *Filename);

            Result = FactoryCreateFile(InClass, InOuter, InName, Flags, *Filename, Parms, GWarn, OutCanceled);
        }
    }
    
    return Result;
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
    
    // Serialize the JSON object to a string with pretty formatting
    TSharedRef<TJsonWriter<TCHAR, TPrettyJsonPrintPolicy<TCHAR>>> JsonWriter = TJsonWriterFactory<TCHAR, TPrettyJsonPrintPolicy<TCHAR>>::Create(&OutJSONString);
    if (!FJsonSerializer::Serialize(JsonObject, JsonWriter))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to serialize JSON object to string"));
        return false;
    }
    
    return true;
}
