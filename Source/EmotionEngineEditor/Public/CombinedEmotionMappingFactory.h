#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "AssetTypeCategories.h"
#include "EmotionData.h"
#include "CombinedEmotionMappingFactory.generated.h"

/**
 * Factory for creating Combined Emotion Mapping Data Assets
 */
UCLASS()
class EMOTIONENGINEEDITOR_API UCombinedEmotionMapping_Factory : public UFactory
{
    GENERATED_UCLASS_BODY()

public:

    UPROPERTY(EditAnywhere, Category = EmotionEngine)
    TSubclassOf<UCombinedEmotionMapping> CombinedEmotionMapping;
    
    virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
    virtual bool ShouldShowInNewMenu() const override;
    virtual uint32 GetMenuCategories() const override;
};

/**
 * Factory for creating Emotional Tendency Data Assets
 */
UCLASS()
class EMOTIONENGINEEDITOR_API UEmotionalTendency_Factory : public UFactory
{
    GENERATED_UCLASS_BODY()

public:
    
    UPROPERTY(EditAnywhere, Category = EmotionEngine)
    TSubclassOf<UEmotionalTendency> EmotionalTendency;

    virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
    virtual bool ShouldShowInNewMenu() const override;
    virtual uint32 GetMenuCategories() const override;
};
