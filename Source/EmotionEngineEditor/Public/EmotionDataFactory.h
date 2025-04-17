#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "EditorReimportHandler.h"
#include "Exporters/Exporter.h"
#include "AssetTypeCategories.h"
#include "EmotionData.h"
#include "EmotionDataFactory.generated.h"

/**
 * Factory for creating Emotion Data Assets
 */
UCLASS()
class EMOTIONENGINEEDITOR_API UEmotionDefinition_Factory : public UFactory, public FReimportHandler
{
    GENERATED_UCLASS_BODY()

public:

    UPROPERTY(EditAnywhere, Category = EmotionEngine)
    TSubclassOf<UEmotionDefinition> EmotionData;
    
    //~ Begin UFactory Interface
    virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
    virtual UObject* FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled) override;
    virtual bool FactoryCanImport(const FString& Filename) override;
    virtual bool ShouldShowInNewMenu() const override;
    virtual uint32 GetMenuCategories() const override;
    virtual UObject* ImportObject(UClass* InClass, UObject* InOuter, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, bool& OutCanceled) override;
    //~ End UFactory Interface

    //~ Begin FReimportHandler Interface
    virtual bool CanReimport(UObject* Obj, TArray<FString>& OutFilenames) override;
    virtual EReimportResult::Type Reimport(UObject* Obj) override;
    virtual void SetReimportPaths(UObject* Obj, const TArray<FString>& NewReimportPaths) override;
    //~ End FReimportHandler Interface

private:
    bool ImportFromJSON(const FString& JSONString, UEmotionDefinition* EmotionDefinition);
};

/**
 * Exporter for Emotion Definition Assets to .emo (JSON) files
 */
UCLASS()
class EMOTIONENGINEEDITOR_API UEmotionDefinition_Exporter : public UExporter
{
    GENERATED_UCLASS_BODY()

public:
    virtual bool ExportText(const FExportObjectInnerContext* Context, UObject* Object, const TCHAR* Type, FOutputDevice& Ar, FFeedbackContext* Warn, uint32 PortFlags = 0) override;
    virtual bool ExportBinary(UObject* Object, const TCHAR* Type, FArchive& Ar, FFeedbackContext* Warn, int32 FileIndex = 0, uint32 PortFlags = 0) override;
    virtual bool SupportsObject(UObject* Object) const override;


private:
    bool ExportToJSON(const UEmotionDefinition* EmotionDefinition, FString& OutJSONString);
};

/**
 * Factory for creating Emotion Library Data Assets
 */
UCLASS()
class EMOTIONENGINEEDITOR_API UEmotionLibrary_Factory : public UFactory
{
    GENERATED_UCLASS_BODY()

public:
    
    UPROPERTY(EditAnywhere, Category = EmotionEngine)
    TSubclassOf<UEmotionLibrary> EmotionLibrary;

    virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
    virtual bool ShouldShowInNewMenu() const override;
    virtual uint32 GetMenuCategories() const override;
};

