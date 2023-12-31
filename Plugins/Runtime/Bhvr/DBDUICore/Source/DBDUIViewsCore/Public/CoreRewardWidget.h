#pragma once

#include "CoreMinimal.h"
#include "CoreSelectableButtonWidget.h"
#include "RewardViewData.h"
#include "CoreRewardWidget.generated.h"

class UScaleBox;
class UDBDImage;
class UCoreLockedOverlayWidget;
class UCoreOnHoverBorderWidget;

UCLASS(EditInlineNew)
class DBDUIVIEWSCORE_API UCoreRewardWidget : public UCoreSelectableButtonWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDImage* RewardIcon;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UScaleBox* LayoutScale;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCoreLockedOverlayWidget* LockedOverlay;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCoreOnHoverBorderWidget* OnHoverBorder;

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SetSmallTemplate(bool useSmallTemplate);

	UFUNCTION(BlueprintCallable)
	void SetRewardScale(float scale);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetRewardData(const FRewardViewData& rewardData);

	UFUNCTION(BlueprintCallable)
	void SetIsLocked(bool isLocked, bool useAnimation);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ClearData();

public:
	UCoreRewardWidget();
};

FORCEINLINE uint32 GetTypeHash(const UCoreRewardWidget) { return 0; }
