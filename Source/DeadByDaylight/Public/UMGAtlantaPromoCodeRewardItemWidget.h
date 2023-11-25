#pragma once

#include "CoreMinimal.h"
#include "MobileBaseUserWidget.h"
#include "UMGAtlantaPromoCodeRewardItemWidget.generated.h"

class UPanelWidget;
class UWidgetAnimation;
class UImage;
class UTextBlock;

UCLASS(Abstract, EditInlineNew)
class DEADBYDAYLIGHT_API UUMGAtlantaPromoCodeRewardItemWidget : public UMobileBaseUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UPanelWidget* CurrencyItem;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* CurrencyIcon;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* CurrencyName;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* CurrencyAmount;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* ItemRarityTint;

	UPROPERTY()
	UWidgetAnimation* RevealAnimationSmall;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UPanelWidget* CustomizationItem;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* CustomizationIcon;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* CustomizationName;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* CustomizationRarityTint;

	UPROPERTY()
	UWidgetAnimation* RevealAnimationLarge;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UPanelWidget* CharacterPanel;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* CharacterPortrait;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* CharacterName;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UPanelWidget* TicketPanel;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* TicketRarityTint;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* TicketIcon;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* TicketName;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* TicketAmount;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UPanelWidget* OfferingPanel;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* OfferingRarityTint;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* OfferingIcon;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* OfferingName;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* OfferingAmount;

public:
	UUMGAtlantaPromoCodeRewardItemWidget();
};

FORCEINLINE uint32 GetTypeHash(const UUMGAtlantaPromoCodeRewardItemWidget) { return 0; }
