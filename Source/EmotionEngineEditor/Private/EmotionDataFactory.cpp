#include "EmotionDataFactory.h"
#include "EmotionEngineEditor.h"

// Emotion Data Factory
UEmotionDefinition_Factory::UEmotionDefinition_Factory(const class FObjectInitializer& OBJ) : Super(OBJ)
{
    bCreateNew = true;
    bEditAfterNew = true;
    SupportedClass = UEmotionDefinition::StaticClass();
    //Supported
}

UObject* UEmotionDefinition_Factory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
    UEmotionDefinition* NewEmotionData = NewObject<UEmotionDefinition>(InParent, UEmotionDefinition::StaticClass(), InName, Flags | RF_Transactional, Context);
    return NewEmotionData;
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
