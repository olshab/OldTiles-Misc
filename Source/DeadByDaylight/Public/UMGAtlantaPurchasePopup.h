#pragma once

#include "CoreMinimal.h"
#include "MobileBaseUserWidget.h"
#include "UObject/SoftObjectPtr.h"
#include "UMGAtlantaPurchasePopup.generated.h"

class UUMGBaseButtonWidget;
class UHorizontalBox;
class UImage;
class UWidgetSwitcher;
class UUMGPurchaseBuyButton;
class UTextBlock;
class UUMGPurchaseSticker;
class UUMGPurchaseItemsInfo;

UCLASS(Abstract, EditInlineNew)
class UUMGAtlantaPurchasePopup : public UMobileBaseUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UWidgetSwitcher* LayoutSwitcher;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* ImagePopup;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* OfferTextWithInfo;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* OfferText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* TitleTextWithInfo;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* TitleText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* DescriptionText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UHorizontalBox* ItemsContainer;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGPurchaseBuyButton* BuyButtonWithInfo;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGPurchaseBuyButton* BuyButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGBaseButtonWidget* CloseButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGPurchaseSticker* PurchaseSticker;

	UPROPERTY(EditAnywhere, NoClear)
	TSoftClassPtr<UUMGPurchaseItemsInfo> PurchaseItemsInfoWidgetClass;

protected:
	UFUNCTION()
	void HandleCloseButtonClicked();

	UFUNCTION()
	void HandleBuyButtonClicked();

public:
	UUMGAtlantaPurchasePopup();
};

FORCEINLINE uint32 GetTypeHash(const UUMGAtlantaPurchasePopup) { return 0; }
