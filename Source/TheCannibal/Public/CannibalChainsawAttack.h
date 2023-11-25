#pragma once

#include "CoreMinimal.h"
#include "ButtonPromptSource.h"
#include "HillbillyChainsawAttack.h"
#include "TagStateBool.h"
#include "CannibalChainsawAttack.generated.h"

class ADBDPlayer;

UCLASS(meta=(BlueprintSpawnableComponent))
class THECANNIBAL_API UCannibalChainsawAttack : public UHillbillyChainsawAttack, public IButtonPromptSource
{
	GENERATED_BODY()

private:
	UPROPERTY(Transient)
	FTagStateBool _isInTantrum;

	UPROPERTY(EditDefaultsOnly)
	float _immuneToSuccessiveChainsawHitsDuration;

	UPROPERTY(Transient)
	TMap<ADBDPlayer*, float> _lastChainsawHitTimes;

public:
	UCannibalChainsawAttack();
};

FORCEINLINE uint32 GetTypeHash(const UCannibalChainsawAttack) { return 0; }
