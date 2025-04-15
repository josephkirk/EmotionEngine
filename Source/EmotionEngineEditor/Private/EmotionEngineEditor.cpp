// Copyright Epic Games, Inc. All Rights Reserved.

#include "EmotionEngineEditor.h"

#define LOCTEXT_NAMESPACE "FEmotionEngineEditorModule"

DEFINE_LOG_CATEGORY(LogEmotionEngineEditor);

EAssetTypeCategories::Type FEmotionEngineEditorModule::EmotionAssetsCategory;

void FEmotionEngineEditorModule::StartupModule()
{
	// Register input assets

}

void FEmotionEngineEditorModule::ShutdownModule()
{
	// Unregister input assets

}


EAssetTypeCategories::Type FEmotionEngineEditorModule::GetEmotionAssetsCategory()
{
	return EmotionAssetsCategory;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FEmotionEngineEditorModule, EmotionEngineEditor)