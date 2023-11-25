#pragma once

#include "CoreMinimal.h"
#include "LoadingTimeoutPerStep.generated.h"

USTRUCT()
struct FLoadingTimeoutPerStep
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FString StepName;

	UPROPERTY()
	float ExpectedTimeout;

	UPROPERTY()
	float HardCapTimeout;

	UPROPERTY()
	float TimeCapWithoutProgress;

public:
	DEADBYDAYLIGHT_API FLoadingTimeoutPerStep();
};

FORCEINLINE uint32 GetTypeHash(const FLoadingTimeoutPerStep) { return 0; }
