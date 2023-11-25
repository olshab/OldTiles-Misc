#pragma once

#include "CoreMinimal.h"
#include "MobileBaseUserWidget.h"
#include "EActionButtonState.h"
#include "ERadialProgressBarType.h"
#include "PowerButton.generated.h"

class UUMGInventoryItemButton;
class UCanvasPanel;
class UActionButton;
class UTextBlock;
class UImage;
class UProgressBar;

UCLASS(EditInlineNew)
class UPowerButton : public UMobileBaseUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UActionButton* Button;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCanvasPanel* SwitchIcon;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCanvasPanel* CountContainer;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCanvasPanel* RadialProgressBarContainer;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* CountLabel;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* TierImage;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCanvasPanel* AddonsContainer;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGInventoryItemButton* FirstAddonSlot;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGInventoryItemButton* SecondAddonSlot;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UProgressBar* FillPowerChargeProgression;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float DisabledOpacity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float EnabledOpacity;

	UPROPERTY(BlueprintReadOnly)
	bool EnabledLongPressed;

	UPROPERTY(Transient)
	int32 _itemCount;

public:
	UFUNCTION(BlueprintCallable)
	void SetSwitchIconActive(bool active);

	UFUNCTION(BlueprintCallable)
	void SetState(EActionButtonState state);

	UFUNCTION(BlueprintImplementableEvent)
	void SetRadialProgressPercentage(const float progression, ERadialProgressBarType progressBarType);

	UFUNCTION(BlueprintCallable)
	void SetRadialProgressBarActice(bool active);

	UFUNCTION(BlueprintCallable)
	void SetPowerIntensityOpacity(float opacity);

	UFUNCTION(BlueprintCallable)
	void SetFillProgressPercentage(const float chargeProgressionPercentage);

	UFUNCTION(BlueprintImplementableEvent)
	void OnTierChanged(int32 previousTier, int32 currentTier, bool isFirstTime);

	UFUNCTION(BlueprintCallable)
	bool IsRadialProgressBarActive();

	UFUNCTION(BlueprintCallable)
	UActionButton* GetActionButton();

public:
	UPowerButton();
};

FORCEINLINE uint32 GetTypeHash(const UPowerButton) { return 0; }
