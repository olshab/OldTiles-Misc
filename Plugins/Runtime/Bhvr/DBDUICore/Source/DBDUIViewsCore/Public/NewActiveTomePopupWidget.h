#pragma once

#include "CoreMinimal.h"
#include "NewActiveTomePopupViewInterface.h"
#include "NewActiveTomePopupButtonClicked.h"
#include "CoreGenericPopupWidget.h"
#include "NewActiveTomePopupWidget.generated.h"

class UDBDTextBlock;
class UCoreInputSwitcherWidget;
class UDBDImage;

UCLASS(EditInlineNew)
class DBDUIVIEWSCORE_API UNewActiveTomePopupWidget : public UCoreGenericPopupWidget, public INewActiveTomePopupViewInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UDBDImage* BgImageContainer;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDTextBlock* RiftTimeLabel;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDTextBlock* TomeTitle;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDTextBlock* TomeDescription;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCoreInputSwitcherWidget* TomeButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDTextBlock* RiftTitle;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDTextBlock* RiftDescription;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCoreInputSwitcherWidget* RiftButton;

	UPROPERTY()
	FNewActiveTomePopupButtonClicked _currentTomeButtonClickedDelegate;

	UPROPERTY()
	FNewActiveTomePopupButtonClicked _riftButtonClickedDelegate;

private:
	UFUNCTION(BlueprintCallable)
	void OnRiftButtonClicked();

	UFUNCTION(BlueprintCallable)
	void OnCurrentTomeButtonClicked();

public:
	UNewActiveTomePopupWidget();
};

FORCEINLINE uint32 GetTypeHash(const UNewActiveTomePopupWidget) { return 0; }
