// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameplayTagsReaderStyle.h"
#include "GameplayTagsReader.h"
#include "Framework/Application/SlateApplication.h"
#include "Styling/SlateStyleRegistry.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FGameplayTagsReaderStyle::StyleInstance = nullptr;

void FGameplayTagsReaderStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FGameplayTagsReaderStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FGameplayTagsReaderStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("GameplayTagsReaderStyle"));
	return StyleSetName;
}


const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef< FSlateStyleSet > FGameplayTagsReaderStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("GameplayTagsReaderStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("GameplayTagsReader")->GetBaseDir() / TEXT("Resources"));

	Style->Set("GameplayTagsReader.PluginAction", new IMAGE_BRUSH_SVG(TEXT("PlaceholderButtonIcon"), Icon20x20));
	return Style;
}

void FGameplayTagsReaderStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FGameplayTagsReaderStyle::Get()
{
	return *StyleInstance;
}
