#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "AssetTypeCategories.h"
#include "EmotionData.h"
#include "EmotionDataFactory.generated.h"

/**
 * Factory for creating Emotion Data Assets
 */
UCLASS()
class EMOTIONENGINEEDITOR_API UEmotionDefinition_Factory : public UFactory
{
    GENERATED_UCLASS_BODY()

public:

    UPROPERTY(EditAnywhere, Category = EmotionEngine)
    TSubclassOf<UEmotionDefinition> EmotionData;
    
    virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
    virtual bool ShouldShowInNewMenu() const override;
    virtual uint32 GetMenuCategories() const override;
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

