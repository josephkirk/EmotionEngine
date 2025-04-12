// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"
#include "AssetTypeCategories.h"

DECLARE_LOG_CATEGORY_EXTERN(LogEmotionEngineEditor, Log, All);

class SWindow;
class UPlayerMappableKeySettings;
class IAssetTypeActions;
class IAssetTools;
class FSlateStyleSet;

class FEmotionEngineEditorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	static EAssetTypeCategories::Type GetEmotionAssetsCategory();
private:

	void RegisterAssetTypeActions(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action);
	static EAssetTypeCategories::Type EmotionAssetsCategory;

	TArray<TSharedPtr<IAssetTypeActions>> CreatedAssetTypeActions;
};
