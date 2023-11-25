#pragma once

#include "CoreMinimal.h"
#include "MobileBaseUserWidget.h"
#include "Styling/SlateColor.h"
#include "UMGPurchaseCurrencyWidget.generated.h"

class UTextBlock;
class UOverlay;
class UImage;
class UCanvasPanel;

UCLASS(Abstract, EditInlineNew)
class UUMGPurchaseCurrencyWidget : public UMobileBaseUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* PercentageDiscountText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* CurrencyIcon;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* PriceText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* UndiscountedPrice;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* CurrencyColorImage;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UOverlay* OriginalPriceOverlay;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCanvasPanel* DiscountCanvas;

	UPROPERTY(EditDefaultsOnly)
	FSlateColor AffordableColor;

	UPROPERTY(EditDefaultsOnly)
	FSlateColor NotAffordableColor;

public:
	UUMGPurchaseCurrencyWidget();
};

FORCEINLINE uint32 GetTypeHash(const UUMGPurchaseCurrencyWidget) { return 0; }
