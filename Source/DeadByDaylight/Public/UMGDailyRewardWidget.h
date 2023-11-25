#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UMGBaseButtonWidget.h"
#include "OnIntegerIntegerGenericEvent.h"
#include "EUMGDailyRewardWidgetState.h"
#include "UMGDailyRewardWidget.generated.h"

class UImage;
class UWidgetSwitcher;
class UTextBlock;
class UCanvasPanel;

UCLASS(Abstract, EditInlineNew)
class UUMGDailyRewardWidget : public UUMGBaseButtonWidget
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FOnIntegerIntegerGenericEvent OnDailyRewardStateChanged;

protected:
	UPROPERTY(BlueprintReadOnly)
	bool IsMarkedSpecial;

	UPROPERTY(BlueprintReadOnly)
	EUMGDailyRewardWidgetState State;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* AmountText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* ItemNameText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* RewardNumberText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UWidgetSwitcher* RewardTypeSwitcher;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCanvasPanel* ItemInfoPanel;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCanvasPanel* OfferingInfoPanel;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCanvasPanel* GenericInfoPanel;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCanvasPanel* FreeTicketInfoPanel;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCanvasPanel* CrateKeyInfoPanel;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* ItemIcon;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* OfferingIcon;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* GenericRewardIcon;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* FreeTicketRewardIcon;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* ParentItemIcon;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* CrateKeyRewardIcon;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCanvasPanel* ParentItemPanel;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void StopIdleAnimationForState(const EUMGDailyRewardWidgetState inState);

	UFUNCTION(BlueprintImplementableEvent)
	void SetStateVisuals(const EUMGDailyRewardWidgetState inState);

	UFUNCTION(BlueprintImplementableEvent)
	void SetRarityColors(FColor backgroundColor, FColor tintColor);

	UFUNCTION(BlueprintImplementableEvent)
	void PlayIdleAnimationForState(const EUMGDailyRewardWidgetState inState);

	UFUNCTION(BlueprintCallable)
	void HandleUnlockRewardAnimationFinished();

	UFUNCTION(BlueprintCallable)
	void HandleUnlockMysteryRewardAnimationFinished();

	UFUNCTION(BlueprintCallable)
	void HandleDiscoverRewardAnimationFinished();

	UFUNCTION(BlueprintCallable)
	void HandleCollectRewardAnimationFinished();

	UFUNCTION(BlueprintCallable)
	void HandleCollectButtonClick();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void DiscoverMysteryReward();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void CollectReward();

public:
	UUMGDailyRewardWidget();
};

FORCEINLINE uint32 GetTypeHash(const UUMGDailyRewardWidget) { return 0; }
