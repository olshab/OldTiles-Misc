// Copyright Epic Games, Inc. All Rights Reserved.

#include "BlueprintMergeToolCommands.h"

#define LOCTEXT_NAMESPACE "FBlueprintMergeToolModule"

void FBlueprintMergeToolCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "BlueprintMergeTool", "Execute BlueprintMergeTool action", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
