// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "BlueprintMergeToolStyle.h"

class FBlueprintMergeToolCommands : public TCommands<FBlueprintMergeToolCommands>
{
public:

	FBlueprintMergeToolCommands()
		: TCommands<FBlueprintMergeToolCommands>(TEXT("BlueprintMergeTool"), NSLOCTEXT("Contexts", "BlueprintMergeTool", "BlueprintMergeTool Plugin"), NAME_None, FBlueprintMergeToolStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
