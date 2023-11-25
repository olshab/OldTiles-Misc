// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "BlueprintUncookerStyle.h"

class FBlueprintUncookerCommands : public TCommands<FBlueprintUncookerCommands>
{
public:

	FBlueprintUncookerCommands()
		: TCommands<FBlueprintUncookerCommands>(TEXT("BlueprintUncooker"), NSLOCTEXT("Contexts", "BlueprintUncooker", "BlueprintUncooker Plugin"), NAME_None, FBlueprintUncookerStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
