// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameplayTagReaderUI.h"
#include "GameplayTagReaderUIStyle.h"
#include "GameplayTagReaderUICommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

static const FName GameplayTagReaderUITabName("GameplayTagReaderUI");

#define LOCTEXT_NAMESPACE "FGameplayTagReaderUIModule"

void FGameplayTagReaderUIModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FGameplayTagReaderUIStyle::Initialize();
	FGameplayTagReaderUIStyle::ReloadTextures();

	FGameplayTagReaderUICommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FGameplayTagReaderUICommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FGameplayTagReaderUIModule::PluginButtonClicked),
		FCanExecuteAction());

	PluginCommands->MapAction(
		FGameplayTagReaderUICommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FGameplayTagReaderUIModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FGameplayTagReaderUIModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(GameplayTagReaderUITabName, FOnSpawnTab::CreateRaw(this, &FGameplayTagReaderUIModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FGameplayTagReaderUITabTitle", "GameplayTagReaderUI"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FGameplayTagReaderUIModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FGameplayTagReaderUIStyle::Shutdown();

	FGameplayTagReaderUICommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(GameplayTagReaderUITabName);
}

TSharedRef<SDockTab> FGameplayTagReaderUIModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FGameplayTagReaderUIModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("GameplayTagReaderUI.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]
		];
}

void FGameplayTagReaderUIModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(GameplayTagReaderUITabName);
}

void FGameplayTagReaderUIModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FGameplayTagReaderUICommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("PluginTools");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FGameplayTagReaderUICommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FGameplayTagReaderUIModule, GameplayTagReaderUI)