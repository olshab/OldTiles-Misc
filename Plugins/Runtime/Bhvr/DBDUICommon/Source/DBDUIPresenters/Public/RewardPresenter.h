#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "BaseAlertPresenter.h"
#include "RewardPresenter.generated.h"

class UUserWidget;

UCLASS(EditInlineNew)
class DBDUIPRESENTERS_API URewardPresenter : public UBaseAlertPresenter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> RewardWidgetClass;

private:
	UFUNCTION()
	void OnOkAction();

public:
	URewardPresenter();
};

FORCEINLINE uint32 GetTypeHash(const URewardPresenter) { return 0; }
