#pragma once

#include "CoreMinimal.h"
#include "Perk.h"
#include "Templates/SubclassOf.h"
#include "UObject/NoExportTypes.h"
#include "FastTimer.h"
#include "K26P01.generated.h"

class AActor;
class UStatusEffect;
class AGenerator;

UCLASS(meta=(BlueprintSpawnableComponent))
class UK26P01 : public UPerk
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	float _generatorBlockDuration;

	UPROPERTY(EditDefaultsOnly)
	float _auraRevealDuration;

	UPROPERTY(EditDefaultsOnly)
	FLinearColor _generatorAuraColorForKiller;

	UPROPERTY(EditDefaultsOnly)
	int32 _survivorsToBeHooked;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UStatusEffect> _timedRevealToKillerClass;

private:
	UPROPERTY(ReplicatedUsing=OnRep_BlockedGenerators, Transient)
	TArray<AGenerator*> _blockedGenerators;

	UPROPERTY(Transient)
	TArray<AActor*> _hookedSurvivors;

	UPROPERTY(Transient)
	TArray<FFastTimer> _generatorBlockingTimers;

	UPROPERTY(Transient, Export)
	UStatusEffect* _timedRevealToKillerEffect;

private:
	UFUNCTION()
	void OnRep_BlockedGenerators();

	UFUNCTION()
	void Authority_OnBlockTimerDone(AGenerator* generator);

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UK26P01();
};

FORCEINLINE uint32 GetTypeHash(const UK26P01) { return 0; }
