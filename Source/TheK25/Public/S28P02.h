#pragma once

#include "CoreMinimal.h"
#include "BoonPerk.h"
#include "Templates/SubclassOf.h"
#include "S28P02.generated.h"

class UStatusEffect;

UCLASS(meta=(BlueprintSpawnableComponent))
class US28P02 : public UBoonPerk
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	float _healingSpeedGainPercentage;

	UPROPERTY(EditDefaultsOnly)
	bool _canSelfHeal;

	UPROPERTY(EditDefaultsOnly)
	float _selfHealSpeedPenalty;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UStatusEffect> _healingSpeedIncreaseEffect;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UStatusEffect> _allowSelfHealEffectClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UStatusEffect> _selfHealSpeedPenaltyEffectClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UStatusEffect> _revealInjuredPlayersInBoonRangeEffectClass;

public:
	UFUNCTION(BlueprintPure)
	float GetSelfHealSpeedPenaltyAtLevel() const;

	UFUNCTION(BlueprintPure)
	float GetHealingSpeedGainPercentageAtLevel() const;

	UFUNCTION(BlueprintPure)
	bool CanSelfHeal() const;

public:
	US28P02();
};

FORCEINLINE uint32 GetTypeHash(const US28P02) { return 0; }
