// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameplayTagsReaderCommands.h"

#define LOCTEXT_NAMESPACE "FGameplayTagsReaderModule"

void FGameplayTagsReaderCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "GameplayTagsReader", "Transfer BP GamplayTags to C++", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
