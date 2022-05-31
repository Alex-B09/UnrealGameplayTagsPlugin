// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameplayTagReaderUICommands.h"

#define LOCTEXT_NAMESPACE "FGameplayTagReaderUIModule"

void FGameplayTagReaderUICommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "GameplayTagReaderUI", "Button - GameplayTagReaderUI", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(OpenPluginWindow, "GameplayTagReaderUI", "Menu - GameplayTagReaderUI", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
