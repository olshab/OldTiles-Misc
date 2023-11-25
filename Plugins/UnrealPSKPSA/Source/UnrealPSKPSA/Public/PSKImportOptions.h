#pragma once

#include "CoreMinimal.h"
#include "PSKImportOptions.generated.h"

UCLASS(config = Engine, defaultconfig, transient)
class UNREALPSKPSA_API UPSKImportOptions : public UObject
{
	GENERATED_BODY()
public:
	UPSKImportOptions();
	UPROPERTY(EditAnywhere, Category = "Import Settings")
	TWeakObjectPtr<USkeleton> Skeleton;

	bool bInitialized;
};
