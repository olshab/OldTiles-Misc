#pragma once

#include "CoreMinimal.h"
#include "Perk.h"
#include "Rancor.generated.h"

class UStatusEffect;

UCLASS(meta=(BlueprintSpawnableComponent))
class URancor : public UPerk
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	float _survivorRevealDuration;

	UPROPERTY(EditDefaultsOnly)
	float _killerRevealToObsessionDuration;

	UPROPERTY(Transient, Export)
	UStatusEffect* _exposedStatusEffect;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void SpawnBubbleAtSurvivorsLocation();

public:
	UFUNCTION(BlueprintPure)
	float GetSurvivorRevealDuration() const;

	UFUNCTION(BlueprintPure)
	float GetKillerRevealToObsessionDurationAtLevel() const;

public:
	URancor();
};

FORCEINLINE uint32 GetTypeHash(const URancor) { return 0; }
