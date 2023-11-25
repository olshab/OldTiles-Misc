#pragma once

#include "CoreMinimal.h"
#include "UMGBaseCurrencyStorefrontWidget.h"
#include "Layout/Margin.h"
#include "UObject/SoftObjectPtr.h"
#include "UMGAtlCurrencyStorefrontWidget.generated.h"

class UHorizontalBox;
class UCanvasPanel;
class URichTextBlock;
class UUniformGridPanel;
class UOverlay;
class UUMGStoreEventItemsPackButton;
class UImage;
class UUMGStoreAuricCellButton;

UCLASS(Abstract, EditInlineNew)
class UUMGAtlCurrencyStorefrontWidget : public UUMGBaseCurrencyStorefrontWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCanvasPanel* AuricCellsCanvasPanel;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUniformGridPanel* AuricCellsGridPanel;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UHorizontalBox* BottomPurchaseBox;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	URichTextBlock* BottomRightPurchaseRichText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UOverlay* BottomTimer;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* AuricsBgR;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* AuricsBgL;

private:
	UPROPERTY(Export)
	UHorizontalBox* EventItemsPackContainerBox;

	UPROPERTY(EditDefaultsOnly)
	FMargin PaddingEventItemsPackButton;

	UPROPERTY(EditDefaultsOnly, NoClear)
	TSoftClassPtr<UUMGStoreEventItemsPackButton> EventItemsPackWidgetClass;

	UPROPERTY(Transient, Export)
	TArray<UUMGStoreAuricCellButton*> _auricCellButtons;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateFirstPurchaseForAllAuricCellsEndInUI(const FString& endInText);

public:
	UUMGAtlCurrencyStorefrontWidget();
};

FORCEINLINE uint32 GetTypeHash(const UUMGAtlCurrencyStorefrontWidget) { return 0; }
