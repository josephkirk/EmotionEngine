#pragma once

#include "AssetDefinition_DataAsset.h"
#include "EmotionData.h"
#include "AssetDefinition_EmotionData.generated.h"

UCLASS()
class UAssetDefinition_EmotionData : public UAssetDefinition_DataAsset
{
	GENERATED_BODY()

protected:
	virtual FText GetAssetDisplayName() const override { return NSLOCTEXT("AssetDefinition", "EmotionDefinition", "Emotion Definition"); }
	virtual FLinearColor GetAssetColor() const override { return FLinearColor(FColor(127, 255, 255)); }
	virtual TSoftClassPtr<UObject> GetAssetClass() const override { return UEmotionDefinition::StaticClass(); }

};

UCLASS()
class UAssetDefinition_EmotionLibrary : public UAssetDefinition_DataAsset
{
	GENERATED_BODY()

protected:
	virtual FText GetAssetDisplayName() const override { return NSLOCTEXT("AssetDefinition", "UEmotionLibrary", "Emotion Library"); }
	virtual FLinearColor GetAssetColor() const override { return FLinearColor(FColor(155, 155, 255)); }
	virtual TSoftClassPtr<UObject> GetAssetClass() const override { return UEmotionLibrary::StaticClass(); }

};