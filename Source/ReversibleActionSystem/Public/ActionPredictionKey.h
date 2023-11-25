#pragma once

#include "CoreMinimal.h"
#include "ActionPredictionKey.generated.h"

USTRUCT(BlueprintType)
struct FActionPredictionKey
{
	GENERATED_BODY()

private:
	UPROPERTY()
	int32 _keyValue;

public:
	REVERSIBLEACTIONSYSTEM_API FActionPredictionKey();
};

FORCEINLINE uint32 GetTypeHash(const FActionPredictionKey) { return 0; }
