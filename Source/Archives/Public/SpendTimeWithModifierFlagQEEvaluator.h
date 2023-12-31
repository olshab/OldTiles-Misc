#pragma once

#include "CoreMinimal.h"
#include "QuestEventEvaluatorBase.h"
#include "GameplayTagContainer.h"
#include "SpendTimeWithModifierFlagQEEvaluator.generated.h"

UCLASS()
class USpendTimeWithModifierFlagQEEvaluator : public UQuestEventEvaluatorBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	TArray<FGameplayTag> _modifierFlags;

public:
	USpendTimeWithModifierFlagQEEvaluator();
};

FORCEINLINE uint32 GetTypeHash(const USpendTimeWithModifierFlagQEEvaluator) { return 0; }
