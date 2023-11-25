#pragma once

#include "CoreMinimal.h"
#include "QuestEventEvaluatorBase.h"
#include "GameplayTagContainer.h"
#include "SpendTimeWithStateTagQEEvaluator.generated.h"

UCLASS()
class USpendTimeWithStateTagQEEvaluator : public UQuestEventEvaluatorBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	TArray<FGameplayTag> _stateTags;

public:
	USpendTimeWithStateTagQEEvaluator();
};

FORCEINLINE uint32 GetTypeHash(const USpendTimeWithStateTagQEEvaluator) { return 0; }
