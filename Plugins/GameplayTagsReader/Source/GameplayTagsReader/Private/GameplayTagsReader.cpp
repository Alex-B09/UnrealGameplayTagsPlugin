// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameplayTagsReader.h"
#include "GameplayTagsReaderStyle.h"
#include "GameplayTagsReaderCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"

#include <fstream>
#include <filesystem>

static const FName GameplayTagsReaderTabName("GameplayTagsReader");

#define LOCTEXT_NAMESPACE "FGameplayTagsReaderModule"

void FGameplayTagsReaderModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FGameplayTagsReaderStyle::Initialize();
	FGameplayTagsReaderStyle::ReloadTextures();

	FGameplayTagsReaderCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FGameplayTagsReaderCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FGameplayTagsReaderModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FGameplayTagsReaderModule::RegisterMenus));
}

void FGameplayTagsReaderModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FGameplayTagsReaderStyle::Shutdown();

	FGameplayTagsReaderCommands::Unregister();
}

void FGameplayTagsReaderModule::PluginButtonClicked()
{
	// Put your "OnButtonClicked" stuff here
	FText DialogText = FText::Format(
							LOCTEXT("PluginButtonDialogText", "Add code to {0} in {1} to override this button's actions"),
							FText::FromString(TEXT("FGameplayTagsReaderModule::PluginButtonClicked()")),
							FText::FromString(TEXT("GameplayTagsReader.cpp"))
					   );

	// open file
	
	auto trest = std::filesystem::current_path();
	auto test2 = FPaths::GetProjectFilePath();
	auto test3 = FPaths::GameSourceDir();
	auto test4 = FPaths::ProjectConfigDir() + "DefaultGameplayTags.ini";

	FMessageDialog::Open(EAppMsgType::Ok, DialogText);
}

void FGameplayTagsReaderModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FGameplayTagsReaderCommands::Get().PluginAction, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("PluginTools");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FGameplayTagsReaderCommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FGameplayTagsReaderModule, GameplayTagsReader)