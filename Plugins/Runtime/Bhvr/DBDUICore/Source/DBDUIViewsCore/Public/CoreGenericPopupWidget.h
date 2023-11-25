#pragma once

#include "CoreMinimal.h"
#include "GenericPopupViewInterface.h"
#include "CoreBasePopupWidget.h"
#include "PopupBackActionDelegate.h"
#include "PopupAction.h"
#include "CoreGenericPopupWidget.generated.h"

class UCoreInputSwitcherWidget;

UCLASS(EditInlineNew)
class DBDUIVIEWSCORE_API UCoreGenericPopupWidget : public UCoreBasePopupWidget, public IGenericPopupViewInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCoreInputSwitcherWidget* ProgressionButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCoreInputSwitcherWidget* RegressionButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCoreInputSwitcherWidget* AlternativeButton;

private:
	UPROPERTY()
	FPopupAction _popupActionDelegate;

	UPROPERTY()
	FPopupBackActionDelegate _popupBackActionDelegate;

protected:
	UFUNCTION()
	void OnRegressionAction();

	UFUNCTION()
	void OnProgressionAction();

	UFUNCTION()
	void OnAlternativeAction();

public:
	UCoreGenericPopupWidget();
};

FORCEINLINE uint32 GetTypeHash(const UCoreGenericPopupWidget) { return 0; }
