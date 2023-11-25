#pragma once

#include "CoreMinimal.h"
#include "EEasingType.h"
#include "ETooltipVerticalAlignment.h"
#include "AlertsViewInterface.h"
#include "ETooltipHorizontalAlignment.h"
#include "CoreBaseUserWidget.h"
#include "UObject/NoExportTypes.h"
#include "Templates/SubclassOf.h"
#include "AlertsViewData.h"
#include "RewardWrapperViewData.h"
#include "CoreAlertsWidget.generated.h"

class UHorizontalBox;
class UCoreRewardWrapperWidget;
class UDBDRichTextBlock;
class UCoreButtonWidget;
class UDBDImage;
class UUITweenInstance;

UCLASS(EditInlineNew)
class DBDUIVIEWSCORE_API UCoreAlertsWidget : public UCoreBaseUserWidget, public IAlertsViewInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UCoreRewardWrapperWidget> RewardWidgetClass;

	UPROPERTY(BlueprintReadOnly, Export)
	UHorizontalBox* AlertRewardContainer;

	UPROPERTY(BlueprintReadOnly, Export)
	UDBDRichTextBlock* RewardsDescriptionText;

	UPROPERTY(BlueprintReadOnly, Export)
	UDBDImage* EventIMG;

	UPROPERTY(BlueprintReadOnly, Export)
	UDBDRichTextBlock* RewardName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ETooltipHorizontalAlignment HorizontalAlignment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ETooltipVerticalAlignment VerticalAlignment;

private:
	UPROPERTY(EditAnywhere)
	float _fadeInRewardDuration;

	UPROPERTY(EditAnywhere)
	float _fadeRewardDelay;

	UPROPERTY(EditAnywhere)
	EEasingType _fadeInRewardEasing;

	UPROPERTY(EditAnywhere)
	float _sequenceDelay;

	UPROPERTY(EditAnywhere)
	float _sequenceFadeOutDuration;

	UPROPERTY(EditAnywhere)
	float _finalSequenceDelay;

	UPROPERTY(EditAnywhere)
	float _finalSequenceFadeOutDuration;

	UPROPERTY(EditAnywhere)
	FVector2D _rewardInitialScale;

	UPROPERTY(EditAnywhere)
	FVector2D _rewardFinalScale;

	UPROPERTY(EditAnywhere)
	float _rewardScalingDuration;

	UPROPERTY(EditAnywhere)
	float _rewardScalingDelay;

	UPROPERTY(EditAnywhere)
	float _rewardScalingIdleDuration;

	UPROPERTY(EditAnywhere)
	EEasingType _rewardScalingEasing;

	UPROPERTY(EditAnywhere)
	float _sequenceShiftDuration;

	UPROPERTY(EditAnywhere)
	float _sequenceShiftDelay;

	UPROPERTY(EditAnywhere)
	EEasingType _sequenceShiftEasing;

	UPROPERTY(EditAnywhere)
	FVector2D _rewardContainerShiftFinalPosition;

private:
	UFUNCTION()
	void ShowRewardTooltip(UCoreButtonWidget* rewardWidget);

	UFUNCTION()
	void ShowRewardNameVisibility(UUITweenInstance* tween);

public:
	UFUNCTION(BlueprintCallable)
	void ShowAlertRewards(const FAlertsViewData& alertsViewData);

	UFUNCTION(BlueprintCallable)
	void SetRewardsDescription(const FString& rewardsDescription);

private:
	UFUNCTION()
	void RewardAlertSequenceCompleted(UUITweenInstance* tween);

public:
	UFUNCTION(BlueprintImplementableEvent)
	void PlayDisplayRewardSound(FRewardWrapperViewData rewardData);

	UFUNCTION(BlueprintImplementableEvent)
	void PlayDisappearRewardSound();

private:
	UFUNCTION()
	void OnRewardItemsFadeOutCompleted(UUITweenInstance* tween);

	UFUNCTION()
	void HideRewardTooltip(UCoreButtonWidget* rewardWidget);

public:
	UFUNCTION(BlueprintCallable)
	void EndRewardDisplayRequested();

private:
	UFUNCTION()
	void EndOfRewardDisplay(UUITweenInstance* tween);

	UFUNCTION()
	void DisplayNextRewardSequence(UUITweenInstance* tween);

	UFUNCTION()
	void DisplayNextReward(UUITweenInstance* tween);

public:
	UCoreAlertsWidget();
};

FORCEINLINE uint32 GetTypeHash(const UCoreAlertsWidget) { return 0; }
