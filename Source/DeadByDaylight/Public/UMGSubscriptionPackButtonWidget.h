#pragma once

#include "CoreMinimal.h"
#include "UMGBaseButtonWidget.h"
#include "UObject/NoExportTypes.h"
#include "UMGSubscriptionPackButtonWidget.generated.h"

class UTextBlock;
class UCanvasPanel;
class USubscriptionRewardDataAsset;
class UButton;
class UImage;
class UUniformGridPanel;

UCLASS(Abstract, EditInlineNew)
class DEADBYDAYLIGHT_API UUMGSubscriptionPackButtonWidget : public UUMGBaseButtonWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	USubscriptionRewardDataAsset* WidgetPerRewardType;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCanvasPanel* ButtonPressedVFX;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCanvasPanel* PricePanel;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* TitleIcon;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* Title;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* Price;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCanvasPanel* RenewalDatePanel;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* RenewalDateText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUniformGridPanel* PurchaseRewardsGrid;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUniformGridPanel* DailyRewardsGrid;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* PortraitBorder;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UButton* InfoButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* ActiveBackgroundImage;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* NonActiveBackgroundImage;

	UPROPERTY(EditDefaultsOnly)
	FLinearColor ActiveTextColor;

	UPROPERTY(EditDefaultsOnly)
	FLinearColor NonActiveTextColor;

	UPROPERTY(BlueprintReadOnly)
	FLinearColor TextColor;

	UPROPERTY(EditDefaultsOnly)
	FLinearColor ActiveSmokeBackgroundTint;

	UPROPERTY(EditDefaultsOnly)
	FLinearColor NonActiveSmokeBackgroundTint;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* PurchaseRewardsSmokeBackground;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* DailyRewardsSmokeBackground;

	UPROPERTY(EditDefaultsOnly)
	FLinearColor ActiveTitleBackgroundTint;

	UPROPERTY(EditDefaultsOnly)
	FLinearColor NonActiveTitleBackgroundTint;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* TitleBackground;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCanvasPanel* ActiveFrame;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCanvasPanel* NonActiveFrame;

private:
	UFUNCTION(BlueprintCallable)
	void OnInfoButtonClicked();

public:
	UUMGSubscriptionPackButtonWidget();
};

FORCEINLINE uint32 GetTypeHash(const UUMGSubscriptionPackButtonWidget) { return 0; }
