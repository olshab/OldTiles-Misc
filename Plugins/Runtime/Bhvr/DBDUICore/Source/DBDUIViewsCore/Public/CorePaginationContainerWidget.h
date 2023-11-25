#pragma once

#include "CoreMinimal.h"
#include "CoreButtonSelector.h"
#include "Templates/SubclassOf.h"
#include "Layout/Margin.h"
#include "CorePaginationContainerWidget.generated.h"

class UCoreSelectableButtonWidget;
class UDBDTextBlock;
class UGridPanel;

UCLASS(EditInlineNew)
class UCorePaginationContainerWidget : public UCoreButtonSelector
{
	GENERATED_BODY()

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSelectedPageDelegate, int32, selectedPage, bool, isUpdate);

public:
	UPROPERTY(BlueprintAssignable)
	FOnSelectedPageDelegate OnSelectedPageDelegate;

protected:
	UPROPERTY(EditAnywhere, NoClear)
	TSubclassOf<UCoreSelectableButtonWidget> PaginationWidgetClass;

	UPROPERTY(EditAnywhere, NoClear)
	int32 MaxNumberOfPages;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UGridPanel* PaginationContainer;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UCoreSelectableButtonWidget* FirstPage;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UDBDTextBlock* FirstEllipsis;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UDBDTextBlock* LastEllipsis;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UCoreSelectableButtonWidget* LastPage;

private:
	UPROPERTY(EditInstanceOnly, NoClear)
	FMargin _widgetPadding;

	UPROPERTY(Transient, Export)
	TArray<UCoreSelectableButtonWidget*> _paginationWidgetList;

public:
	UFUNCTION(BlueprintCallable)
	void UpdateSelectedWidget(int32 currentIndex, int32 numberOfPages);

private:
	UFUNCTION()
	void OnPaginationSelected(UCoreSelectableButtonWidget* selectedButton);

public:
	UFUNCTION(BlueprintCallable)
	int32 GetCurrentPage();

public:
	UCorePaginationContainerWidget();
};

FORCEINLINE uint32 GetTypeHash(const UCorePaginationContainerWidget) { return 0; }
