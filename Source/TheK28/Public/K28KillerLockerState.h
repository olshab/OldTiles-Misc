#pragma once

#include "CoreMinimal.h"
#include "K28KillerLockerState.generated.h"

class UK28LockerComponent;

USTRUCT(BlueprintType)
struct FK28KillerLockerState
{
	GENERATED_BODY()

private:
	UPROPERTY(Export)
	UK28LockerComponent* _lockerUsedByKiller;

	UPROPERTY()
	bool _isTeleportingToLocker;

public:
	THEK28_API FK28KillerLockerState();
};

FORCEINLINE uint32 GetTypeHash(const FK28KillerLockerState) { return 0; }
