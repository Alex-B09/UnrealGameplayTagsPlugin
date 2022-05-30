// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameplayTagsReaderCommands.h"

#define LOCTEXT_NAMESPACE "FGameplayTagsReaderModule"

void FGameplayTagsReaderCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "GameplayTagsReader", "Execute GameplayTagsReader action", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
