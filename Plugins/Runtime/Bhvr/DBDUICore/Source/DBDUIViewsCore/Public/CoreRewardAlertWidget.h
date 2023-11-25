#pragma once

#include "CoreMinimal.h"
#include "RewardViewInterface.h"
#include "CoreBaseUserWidget.h"
#include "RewardOkActionDelegate.h"
#include "CoreRewardAlertWidget.generated.h"

class UCoreKeyListenerButtonWidget;
class UDBDTextBlock;
class UCoreButtonWidget;

UCLASS(EditInlineNew)
class UCoreRewardAlertWidget : public UCoreBaseUserWidget, public IRewardViewInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	FRewardOkActionDelegate _okActionDelegate;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDTextBlock* RewardTitle;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCoreKeyListenerButtonWidget* OkButton;

protected:
	UFUNCTION()
	void OnOkButtonClicked(UCoreButtonWidget* buttonTarget);

public:
	UCoreRewardAlertWidget();
};

FORCEINLINE uint32 GetTypeHash(const UCoreRewardAlertWidget) { return 0; }
