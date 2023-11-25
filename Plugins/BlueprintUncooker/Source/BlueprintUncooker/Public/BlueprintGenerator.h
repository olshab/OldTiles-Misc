#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class UBlueprint;

class UBlueprintGenerator
{
	UBlueprint* CreateBlueprint(const FString& JsonFilePath);
};
