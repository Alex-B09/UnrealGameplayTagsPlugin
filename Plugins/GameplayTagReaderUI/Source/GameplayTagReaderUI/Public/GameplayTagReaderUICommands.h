// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "GameplayTagReaderUIStyle.h"

class FGameplayTagReaderUICommands : public TCommands<FGameplayTagReaderUICommands>
{
public:

	FGameplayTagReaderUICommands()
		: TCommands<FGameplayTagReaderUICommands>(TEXT("GameplayTagReaderUI"), NSLOCTEXT("Contexts", "GameplayTagReaderUI", "GameplayTagReaderUI Plugin"), NAME_None, FGameplayTagReaderUIStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
	TSharedPtr< FUICommandInfo > PluginAction;
};