#include "EmotionDataFactory.h"

// Emotion Data Factory
UEmotionData_Factory::UEmotionData_Factory(const class FObjectInitializer& OBJ) : Super(OBJ)
{
    bCreateNew = true;
    bEditAfterNew = true;
    SupportedClass = UEmotionData::StaticClass();
}

UObject* UEmotionData_Factory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
    UEmotionData* NewEmotionData = NewObject<UEmotionData>(InParent, InClass, InName, Flags);
    return NewEmotionData;
}

bool UEmotionData_Factory::ShouldShowInNewMenu() const
{
    return true;
}

uint32 UEmotionData_Factory::GetMenuCategories() const
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
    UEmotionLibrary* NewEmotionLibrary = NewObject<UEmotionLibrary>(InParent, InClass, InName, Flags);
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
