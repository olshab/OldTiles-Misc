// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "ParticleSystemGeneratorStyle.h"

class FParticleSystemGeneratorCommands : public TCommands<FParticleSystemGeneratorCommands>
{
public:

	FParticleSystemGeneratorCommands()
		: TCommands<FParticleSystemGeneratorCommands>(TEXT("ParticleSystemGenerator"), NSLOCTEXT("Contexts", "ParticleSystemGenerator", "ParticleSystemGenerator Plugin"), NAME_None, FParticleSystemGeneratorStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
