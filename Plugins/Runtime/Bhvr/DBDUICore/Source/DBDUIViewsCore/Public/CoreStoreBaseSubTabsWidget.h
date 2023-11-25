#pragma once

#include "CoreMinimal.h"
#include "StoreBaseSubTabsViewInterface.h"
#include "CoreBaseUserWidget.h"
#include "CoreStoreBaseSubTabsWidget.generated.h"

class UCoreTabContainerWidget;
class UWidgetSwitcher;
class UCoreSelectableButtonWidget;
class UWidget;

UCLASS(Abstract, EditInlineNew)
class UCoreStoreBaseSubTabsWidget : public UCoreBaseUserWidget, public IStoreBaseSubTabsViewInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UCoreTabContainerWidget* SubTabsContainer;

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UWidgetSwitcher* TabContentSwitcher;

protected:
	UFUNCTION()
	void OnSubTabSelected(UCoreSelectableButtonWidget* selectedButton);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	UWidget* GetSubTabContentForTab(int32 subTabId);

public:
	UCoreStoreBaseSubTabsWidget();
};

FORCEINLINE uint32 GetTypeHash(const UCoreStoreBaseSubTabsWidget) { return 0; }
