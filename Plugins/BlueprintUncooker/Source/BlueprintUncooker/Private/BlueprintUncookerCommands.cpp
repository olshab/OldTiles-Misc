// Copyright Epic Games, Inc. All Rights Reserved.

#include "BlueprintUncookerCommands.h"

#define LOCTEXT_NAMESPACE "FBlueprintUncookerModule"

void FBlueprintUncookerCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "BlueprintUncooker", "Execute BlueprintUncooker action", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
