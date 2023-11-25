#pragma once

#include "CoreMinimal.h"
#include "OnSetDataAnimationCompleteDelegate.h"
#include "CoreButtonWidget.h"
#include "OnboardingTutorialButtonViewData.h"
#include "CoreOnboardingTutorialButtonWidget.generated.h"

class UCoreRewardWrapperWidget;
class UDBDImage;
class UWidgetSwitcher;
class UDBDTextBlock;
class UAkAudioEvent;

UCLASS(EditInlineNew)
class DBDUIVIEWSCORE_API UCoreOnboardingTutorialButtonWidget : public UCoreButtonWidget
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FOnSetDataAnimationCompleteDelegate OnSetDataAnimationCompleteDelegate;

	UPROPERTY(EditAnywhere)
	FString UnavailablePressedSfxName;

	UPROPERTY(EditAnywhere)
	UAkAudioEvent* UnavailablePressedSfx;

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDTextBlock* TitleText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDTextBlock* DescriptionText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDTextBlock* RewardsText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDImage* RoleIcon;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UWidgetSwitcher* StateSwitcher;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDImage* LockedImage;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDImage* CompletedImage;

	UPROPERTY(BlueprintReadWrite, Export)
	TArray<UCoreRewardWrapperWidget*> RewardWrappers;

	UPROPERTY(BlueprintReadWrite)
	FOnboardingTutorialButtonViewData ViewData;

protected:
	UFUNCTION(BlueprintCallable)
	void SetVisual();

public:
	UFUNCTION(BlueprintImplementableEvent)
	void SetUIEnabled(bool enabled);

	UFUNCTION(BlueprintImplementableEvent)
	void SetIsKillSwitch(bool isKillSwitch);

	UFUNCTION(BlueprintImplementableEvent)
	void SetData(const FOnboardingTutorialButtonViewData& viewDataNew, bool isRefreshingWithAnimation);

private:
	UFUNCTION()
	void OnRewardReleased(UCoreButtonWidget* buttonTarget);

	UFUNCTION()
	void OnRewardPressed(UCoreButtonWidget* buttonTarget);

	UFUNCTION()
	void OnRewardClicked(UCoreButtonWidget* buttonTarget);

public:
	UFUNCTION(BlueprintPure)
	bool IsInUnavailableStep() const;

public:
	UCoreOnboardingTutorialButtonWidget();
};

FORCEINLINE uint32 GetTypeHash(const UCoreOnboardingTutorialButtonWidget) { return 0; }
