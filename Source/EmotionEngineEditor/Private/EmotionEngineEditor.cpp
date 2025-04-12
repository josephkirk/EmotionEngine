// Copyright Epic Games, Inc. All Rights Reserved.

#include "EmotionEngineEditor.h"
#include "EmotionData.h"
#include "AssetTypeActions/AssetTypeActions_DataAsset.h"
#include "IAssetTools.h"
#include "Styling/SlateStyle.h"
#include "Styling/SlateStyleMacros.h"
#include "Styling/SlateStyleRegistry.h"
#include "Misc/PackageName.h"
#include "Brushes/SlateImageBrush.h"
#include "IAssetTypeActions.h"
#include "AssetDefinition_DataAsset.h"

#define LOCTEXT_NAMESPACE "FEmotionEngineEditorModule"

DEFINE_LOG_CATEGORY(LogEmotionEngineEditor);

EAssetTypeCategories::Type FEmotionEngineEditorModule::EmotionAssetsCategory;

void FEmotionEngineEditorModule::StartupModule()
{
	// Register input assets
	/*IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	EmotionAssetsCategory = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("Emotion")), LOCTEXT("EmotionAssetsCategory", "Emotion"));
	{
		RegisterAssetTypeActions(AssetTools, MakeShareable(new FAssetTypeActions_EmotionData));
	}*/

}

void FEmotionEngineEditorModule::ShutdownModule()
{
	// Unregister input assets
	/*if (FAssetToolsModule* AssetToolsModule = FModuleManager::GetModulePtr<FAssetToolsModule>("AssetTools"))
	{
		for (TSharedPtr<IAssetTypeActions>& AssetAction : CreatedAssetTypeActions)
		{
			AssetToolsModule->Get().UnregisterAssetTypeActions(AssetAction.ToSharedRef());
		}
	}
	CreatedAssetTypeActions.Empty();*/
}


void FEmotionEngineEditorModule::RegisterAssetTypeActions(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action)
{
	AssetTools.RegisterAssetTypeActions(Action);
	CreatedAssetTypeActions.Add(Action);
}

EAssetTypeCategories::Type FEmotionEngineEditorModule::GetEmotionAssetsCategory()
{
	return EmotionAssetsCategory;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FEmotionEngineEditorModule, EmotionEngineEditor)