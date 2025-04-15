#include "CombinedEmotionMappingFactory.h"
#include "EmotionEngineEditor.h"

// Combined Emotion Mapping Factory
UCombinedEmotionMapping_Factory::UCombinedEmotionMapping_Factory(const class FObjectInitializer& OBJ) : Super(OBJ)
{
    bCreateNew = true;
    bEditAfterNew = true;
    SupportedClass = UCombinedEmotionMapping::StaticClass();
}

UObject* UCombinedEmotionMapping_Factory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
    UCombinedEmotionMapping* NewCombinedEmotionMapping = NewObject<UCombinedEmotionMapping>(InParent, UCombinedEmotionMapping::StaticClass(), InName, Flags | RF_Transactional, Context);
    return NewCombinedEmotionMapping;
}

bool UCombinedEmotionMapping_Factory::ShouldShowInNewMenu() const
{
    return true;
}

uint32 UCombinedEmotionMapping_Factory::GetMenuCategories() const
{
    return EAssetTypeCategories::Gameplay;
}

// Emotional Tendency Factory
UEmotionalTendency_Factory::UEmotionalTendency_Factory(const class FObjectInitializer& OBJ) : Super(OBJ)
{
    bCreateNew = true;
    bEditAfterNew = true;
    SupportedClass = UEmotionalTendency::StaticClass();
}

UObject* UEmotionalTendency_Factory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
    UEmotionalTendency* NewEmotionalTendency = NewObject<UEmotionalTendency>(InParent, UEmotionalTendency::StaticClass(), InName, Flags | RF_Transactional, Context);
    return NewEmotionalTendency;
}

bool UEmotionalTendency_Factory::ShouldShowInNewMenu() const
{
    return true;
}

uint32 UEmotionalTendency_Factory::GetMenuCategories() const
{
    return EAssetTypeCategories::Gameplay;
}
