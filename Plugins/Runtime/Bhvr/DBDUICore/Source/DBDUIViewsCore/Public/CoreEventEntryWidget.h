#pragma once

#include "CoreMinimal.h"
#include "EventEntryViewInterface.h"
#include "CoreBaseUserWidget.h"
#include "EventEntryTabSelectedDelegate.h"
#include "EventEntryPopupSkinUIData.h"
#include "EventEntryBackActionDelegate.h"
#include "CoreEventEntryWidget.generated.h"

class UEventEntryViewData;
class UCoreTabContainerWidget;
class UDataTable;
class UDBDImage;
class UCoreInputSwitcherWidget;
class UMilestoneTrackerWidget;
class UDBDTextBlock;
class UCoreKeyListenerInputPromptWidget;
class URichTextBlock;
class UCoreSelectableButtonWidget;

UCLASS(EditInlineNew)
class DBDUIVIEWSCORE_API UCoreEventEntryWidget : public UCoreBaseUserWidget, public IEventEntryViewInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly)
	UEventEntryViewData* _viewData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, NoClear)
	UDataTable* _eventSkinDataTable;

	UPROPERTY(BlueprintReadOnly)
	FEventEntryPopupSkinUIData _skinData;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDImage* TitleBanner;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDImage* TitleImage;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDTextBlock* EventDateText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCoreTabContainerWidget* TabsContainer;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UMilestoneTrackerWidget* MilestoneTracker;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCoreKeyListenerInputPromptWidget* ScrollPrompt;

	UPROPERTY(BlueprintAssignable)
	FEventEntryTabSelectedDelegate _eventEntryTabSelectedEvent;

	UPROPERTY()
	FEventEntryBackActionDelegate _backActionDelegate;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCoreInputSwitcherWidget* RegressionButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	URichTextBlock* TitleText;

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetUiTakeoverActive(bool isActive);

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void SetTabsVisuals();

	UFUNCTION()
	void OnTabSelected(UCoreSelectableButtonWidget* selectedButton);

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnShow();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnLeave();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnEnter();

	UFUNCTION(BlueprintCallable)
	void OnBackAction();

public:
	UCoreEventEntryWidget();
};

FORCEINLINE uint32 GetTypeHash(const UCoreEventEntryWidget) { return 0; }
