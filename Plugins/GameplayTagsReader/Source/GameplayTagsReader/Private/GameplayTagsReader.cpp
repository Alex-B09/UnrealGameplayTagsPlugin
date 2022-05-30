// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameplayTagsReader.h"
#include "GameplayTagsReaderStyle.h"
#include "GameplayTagsReaderCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"

#include "GameplayTagsManager.h"
#include "Misc/App.h"
#include "Misc/FileHelper.h"

#include <fstream>
#include <filesystem>
#include <sstream>

static const FName GameplayTagsReaderTabName("GameplayTagsReader");

#define LOCTEXT_NAMESPACE "FGameplayTagsReaderModule"


FString GetHeaderFileFormat(FGameplayTagContainer tags)
{
	std::stringstream ss;

	ss << "#pragma once" << std::endl
		<< std::endl
		<< "#include \"GameplayTagContainer.h\"" << std::endl
		<< std::endl
		<< "namespace Tags" << std::endl
		<< "{" << std::endl;

	for (auto tag : tags)
	{
		auto parsedName = tag.GetTagName().ToString();
		parsedName = parsedName.Replace(TEXT("."), TEXT("_"));

		ss << "\t"
			<<"const FGameplayTag "
			<< TCHAR_TO_UTF8(*parsedName.ToUpper())
			<< " = FGameplayTag(\""
			<< TCHAR_TO_UTF8(*(tag.GetTagName().ToString()))
			<< "\");"
			<< std::endl;

	}

	ss << "};" << std::endl;

	return ss.str().c_str();
}


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

	auto completeSourcePath = FPaths::GameSourceDir().Append(FApp::GetProjectName()).Append("/Tags.h");
	FString filePath = FPaths::ConvertRelativePathToFull(completeSourcePath);

	FGameplayTagContainer allTags;
	UGameplayTagsManager::Get().RequestAllGameplayTags(allTags, false);

	auto test1 = GetHeaderFileFormat(allTags);
	FFileHelper::SaveStringToFile(test1, *filePath);
	
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