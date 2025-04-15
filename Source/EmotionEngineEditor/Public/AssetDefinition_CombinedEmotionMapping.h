#pragma once

#include "AssetDefinition_DataAsset.h"
#include "EmotionData.h"
#include "AssetDefinition_CombinedEmotionMapping.generated.h"

UCLASS()
class UAssetDefinition_CombinedEmotionMapping : public UAssetDefinition_DataAsset
{
	GENERATED_BODY()

protected:
	virtual FText GetAssetDisplayName() const override { return NSLOCTEXT("AssetDefinition", "CombinedEmotionMapping", "Combined Emotion Mapping"); }
	virtual FLinearColor GetAssetColor() const override { return FLinearColor(FColor(255, 200, 100)); }
	virtual TSoftClassPtr<UObject> GetAssetClass() const override { return UCombinedEmotionMapping::StaticClass(); }
};

UCLASS()
class UAssetDefinition_EmotionalTendency : public UAssetDefinition_DataAsset
{
	GENERATED_BODY()

protected:
	virtual FText GetAssetDisplayName() const override { return NSLOCTEXT("AssetDefinition", "EmotionalTendency", "Emotional Tendency"); }
	virtual FLinearColor GetAssetColor() const override { return FLinearColor(FColor(200, 255, 150)); }
	virtual TSoftClassPtr<UObject> GetAssetClass() const override { return UEmotionalTendency::StaticClass(); }
};
