#pragma once

#include "CoreMinimal.h"
#include "LoadingTimeoutPerStep.h"
#include "S3LoadingConfig.generated.h"

USTRUCT()
struct FS3LoadingConfig
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FLoadingTimeoutPerStep GlobalTimeout;

	UPROPERTY()
	TArray<FLoadingTimeoutPerStep> TimeoutPerSteps;

public:
	DEADBYDAYLIGHT_API FS3LoadingConfig();
};

FORCEINLINE uint32 GetTypeHash(const FS3LoadingConfig) { return 0; }
