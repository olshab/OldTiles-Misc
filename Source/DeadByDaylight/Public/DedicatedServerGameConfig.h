#pragma once

#include "CoreMinimal.h"
#include "DedicatedServerGameConfig.generated.h"

USTRUCT()
struct FDedicatedServerGameConfig
{
	GENERATED_BODY()

public:
	UPROPERTY()
	int32 LatencyRetryCooldownSeconds;

	UPROPERTY()
	bool NewContentShutdown;

	UPROPERTY()
	int32 NewContentShutdownMaxMinutes;

	UPROPERTY()
	int32 NewContentShutdownMinMinutes;

public:
	DEADBYDAYLIGHT_API FDedicatedServerGameConfig();
};

FORCEINLINE uint32 GetTypeHash(const FDedicatedServerGameConfig) { return 0; }
