// Copyright Epic Games, Inc. All Rights Reserved.

#include "ParticleSystemGeneratorCommands.h"

#define LOCTEXT_NAMESPACE "FParticleSystemGeneratorModule"

void FParticleSystemGeneratorCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "ParticleSystemGenerator", "Execute ParticleSystemGenerator action", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
