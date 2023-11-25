#pragma once

#include "CoreMinimal.h"
#include "ArchiveTierPurchasePopupViewInterface.h"
#include "CoreGenericPopupWidget.h"
#include "Styling/SlateColor.h"
#include "ECurrencyType.h"
#include "ConfirmPurchase.h"
#include "CoreArchiveTierPurchasePopupWidget.generated.h"

class UCurveFloat;
class UDBDImage;
class UDBDTextBlock;
class UCoreInputSwitcherWidget;
class UArchiveTierPurchasePopupViewData;
class UDBDRichTextBlock;
class UOverlay;

UCLASS(EditInlineNew)
class DBDUIVIEWSCORE_API UCoreArchiveTierPurchasePopupWidget : public UCoreGenericPopupWidget, public IArchiveTierPurchasePopupViewInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta=(BindWidget))
	UCoreInputSwitcherWidget* LessInputSwitcher;

	UPROPERTY(meta=(BindWidget))
	UCoreInputSwitcherWidget* MoreInputSwitcher;

	UPROPERTY(meta=(BindWidget))
	UDBDRichTextBlock* CurrentQuantityText;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UDBDImage* ImageContainer;

	UPROPERTY(meta=(BindWidget))
	UOverlay* PriceContainer;

	UPROPERTY(meta=(BindWidget))
	UDBDTextBlock* PriceText;

	UPROPERTY(meta=(BindWidget))
	UDBDTextBlock* DiscountText;

	UPROPERTY(EditDefaultsOnly)
	UCurveFloat* _quantityCurve;

	UPROPERTY(EditDefaultsOnly)
	FText _bonusTierStyleName;

	UPROPERTY(EditDefaultsOnly)
	TMap<ECurrencyType, FSlateColor> _currencyTextColors;

	UPROPERTY(EditDefaultsOnly)
	FSlateColor _unaffordablePriceColor;

private:
	UPROPERTY()
	FConfirmPurchase _confirmPurchaseDelegate;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void SetVisualData(const UArchiveTierPurchasePopupViewData* viewData);

	UFUNCTION(BlueprintImplementableEvent)
	void SetCurrencyIcon(const ECurrencyType currencyType);

private:
	UFUNCTION()
	void OnMoreInputTriggered();

	UFUNCTION()
	void OnLessInputTriggered();

	UFUNCTION()
	void OnConfirmPurchase();

public:
	UCoreArchiveTierPurchasePopupWidget();
};

FORCEINLINE uint32 GetTypeHash(const UCoreArchiveTierPurchasePopupWidget) { return 0; }
