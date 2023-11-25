#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AIDetectedStimulus.generated.h"

class AActor;

USTRUCT(BlueprintType)
struct FAIDetectedStimulus
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TWeakObjectPtr<AActor> Instigator;

	UPROPERTY()
	FVector Location;

	UPROPERTY()
	FRotator Rotation;

	UPROPERTY()
	FVector Velocity;

	UPROPERTY()
	FVector LastHasBeenSeenLocation;

	UPROPERTY()
	FVector LastHasBeenSeenDirection;

	UPROPERTY()
	float LastHasBeenSeenTime;

	UPROPERTY()
	float NextHasBeenSeenUpdateTime;

	UPROPERTY()
	float AtTime;

	UPROPERTY()
	FName Tag;

public:
	DEADBYDAYLIGHT_API FAIDetectedStimulus();
};

FORCEINLINE uint32 GetTypeHash(const FAIDetectedStimulus) { return 0; }
