#pragma once

#include "CoreMinimal.h"
#include "UMGBaseCurrencyButtonWidget.h"
#include "UMGPromoPackPurchaseCurrencyButtonWidget.generated.h"

class UTextBlock;
class UOverlay;
class UCanvasPanel;

UCLASS(Abstract, EditInlineNew)
class UUMGPromoPackPurchaseCurrencyButtonWidget : public UUMGBaseCurrencyButtonWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* PercentageDiscountText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* UndiscountedPrice;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCanvasPanel* PercentageDiscountCanvas;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UOverlay* OverlayUndiscountedPrice;

public:
	UUMGPromoPackPurchaseCurrencyButtonWidget();
};

FORCEINLINE uint32 GetTypeHash(const UUMGPromoPackPurchaseCurrencyButtonWidget) { return 0; }
