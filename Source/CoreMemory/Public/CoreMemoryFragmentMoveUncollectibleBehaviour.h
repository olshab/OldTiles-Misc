#pragma once

#include "CoreMinimal.h"
#include "CoreMemoryBehaviourBase.h"
#include "DBDTunableRowHandle.h"
#include "CoreMemoryFragmentMoveUncollectibleBehaviour.generated.h"

UCLASS(EditInlineNew)
class UCoreMemoryFragmentMoveUncollectibleBehaviour : public UCoreMemoryBehaviourBase
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	FDBDTunableRowHandle _fragmentSpeed;

	UPROPERTY(EditDefaultsOnly)
	int32 _maxLineOfSightTries;

public:
	UCoreMemoryFragmentMoveUncollectibleBehaviour();
};

FORCEINLINE uint32 GetTypeHash(const UCoreMemoryFragmentMoveUncollectibleBehaviour) { return 0; }
