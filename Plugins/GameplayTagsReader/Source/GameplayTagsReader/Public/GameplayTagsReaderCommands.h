// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "GameplayTagsReaderStyle.h"

class FGameplayTagsReaderCommands : public TCommands<FGameplayTagsReaderCommands>
{
public:

	FGameplayTagsReaderCommands()
		: TCommands<FGameplayTagsReaderCommands>(TEXT("GameplayTagsReader"), NSLOCTEXT("Contexts", "GameplayTagsReader", "GameplayTagsReader Plugin"), NAME_None, FGameplayTagsReaderStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
