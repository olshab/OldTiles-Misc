#pragma once

#include "CoreMinimal.h"
#include "TooltipPressedData.h"
#include "MobileBaseUserWidget.h"
#include "ECurrencyType.h"
#include "Components/SlateWrapperTypes.h"
#include "OnButtonClickEvent.h"
#include "UMGBankAndPlayerInfoWidget.generated.h"

class UUMGLevelBannerWidget;
class UUMGSelectedCharacterWidget;
class UUMGMainMenuMonthlyPassButton;
class UUMGBankWidget;
class UTextBlock;
class UUMGRankBanner;

UCLASS(Abstract, EditInlineNew)
class DEADBYDAYLIGHT_API UUMGBankAndPlayerInfoWidget : public UMobileBaseUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGBankWidget* BankWidget;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* PlayerNameText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGSelectedCharacterWidget* SelectedCharacterWidget;

	UPROPERTY(BlueprintReadWrite, Transient)
	ESlateVisibility RankWidgetVisibility;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGLevelBannerWidget* LevelBanner;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGRankBanner* RankBanner;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGMainMenuMonthlyPassButton* MonthlyPassButton;

	UPROPERTY(BlueprintAssignable)
	FOnButtonClickEvent _onCancelPartyButtonClickedEvent;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void SetPlayerLevelBP(int32 level, int32 devotion, int32 currentLevelXp, int32 totalLevelXp, bool isSlasher, bool playUpdateAnim);

private:
	UFUNCTION()
	void OnTooltipTriggeredByRankBanner(const FTooltipPressedData& tooltipPressedData);

public:
	UFUNCTION()
	void OnTooltipTriggeredByLevelBannerWidget(const FTooltipPressedData& tooltipPressedData);

private:
	UFUNCTION()
	void OnTooltipTriggeredByCurrency(const FTooltipPressedData& tooltipPressedData, const ECurrencyType currencyType);

public:
	UFUNCTION()
	void OnPurchaseAuricCellsButtonClicked();

	UFUNCTION()
	void OnPrestigeButtonClicked();

	UFUNCTION()
	void OnMainMenuSubscriptionClicked();

private:
	UFUNCTION()
	void OnCancelPartyButtonClicked();

public:
	UUMGBankAndPlayerInfoWidget();
};

FORCEINLINE uint32 GetTypeHash(const UUMGBankAndPlayerInfoWidget) { return 0; }
