#pragma once

#include "CoreMinimal.h"
#include "Perk.h"
#include "Templates/SubclassOf.h"
#include "FurtiveChase.generated.h"

class UStatusEffect;

UCLASS(meta=(BlueprintSpawnableComponent))
class DBDCOMPETENCE_API UFurtiveChase : public UPerk
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UStatusEffect> _undetectableStatusEffectClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UStatusEffect> _hasteStatusEffectClass;

	UPROPERTY(EditDefaultsOnly)
	float _undetectableAndHasteStatusEffectDuration;

	UPROPERTY(EditDefaultsOnly)
	float _hasteStatusEffectPercent;

public:
	UFurtiveChase();
};

FORCEINLINE uint32 GetTypeHash(const UFurtiveChase) { return 0; }
