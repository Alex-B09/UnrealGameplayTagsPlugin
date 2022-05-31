// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameplayTagReaderUIStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Framework/Application/SlateApplication.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FGameplayTagReaderUIStyle::StyleInstance = nullptr;

void FGameplayTagReaderUIStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FGameplayTagReaderUIStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FGameplayTagReaderUIStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("GameplayTagReaderUIStyle"));
	return StyleSetName;
}

const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef< FSlateStyleSet > FGameplayTagReaderUIStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("GameplayTagReaderUIStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("GameplayTagReaderUI")->GetBaseDir() / TEXT("Resources"));

	Style->Set("GameplayTagReaderUI.OpenPluginWindow", new IMAGE_BRUSH_SVG(TEXT("PlaceholderButtonIcon"), Icon20x20));

	return Style;
}

void FGameplayTagReaderUIStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FGameplayTagReaderUIStyle::Get()
{
	return *StyleInstance;
}
