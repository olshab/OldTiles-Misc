#pragma once

#include "CoreMinimal.h"
#include "CoreMemoryBehaviourBase.h"
#include "GameplayTagContainer.h"
#include "CoreMemoryFragmentSpawnData.h"
#include "CoreMemorySpawnFragmentOnEventBehaviour.generated.h"

UCLASS(EditInlineNew)
class UCoreMemorySpawnFragmentOnEventBehaviour : public UCoreMemoryBehaviourBase
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	TArray<FGameplayTag> _spawnFragmentOnGameEvents;

	UPROPERTY(EditDefaultsOnly)
	FCoreMemoryFragmentSpawnData _fragmentSpawnData;

	UPROPERTY(EditDefaultsOnly)
	bool _onlyForKiller;

public:
	UCoreMemorySpawnFragmentOnEventBehaviour();
};

FORCEINLINE uint32 GetTypeHash(const UCoreMemorySpawnFragmentOnEventBehaviour) { return 0; }
