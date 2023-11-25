#pragma once

#include "CoreMinimal.h"
#include "TooltipPressedData.h"
#include "MobileBaseUserWidget.h"
#include "ECurrencyType.h"
#include "UMGBaseRootStorefrontWidget.generated.h"

class UPanelWidget;
class UUMGBaseButtonWidget;
class UNamedSlot;
class UTextBlock;

UCLASS(Abstract, EditInlineNew)
class UUMGBaseRootStorefrontWidget : public UMobileBaseUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta=(BindWidget))
	UNamedSlot* StorePageSlot;

	UPROPERTY(meta=(BindWidget))
	UUMGBaseButtonWidget* BackButton;

	UPROPERTY(meta=(BindWidget))
	UPanelWidget* CurrencyButtonsPanel;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* StorefrontTitle;

protected:
	UFUNCTION()
	void OnPurchaseAuricCellButtonPressed();

	UFUNCTION()
	void OnCurrencyButtonLongPressed(const FTooltipPressedData& tooltipPressedData, const ECurrencyType currencyType);

	UFUNCTION()
	void OnBackButtonPressed();

public:
	UUMGBaseRootStorefrontWidget();
};

FORCEINLINE uint32 GetTypeHash(const UUMGBaseRootStorefrontWidget) { return 0; }
