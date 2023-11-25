#pragma once

#include "CoreMinimal.h"
#include "MobileBaseUserWidget.h"
#include "UMGRewardSlotTutorialPopupRewardWidget.generated.h"

class UTextBlock;
class UImage;
class UWidget;

UCLASS(Abstract, EditInlineNew)
class UUMGRewardSlotTutorialPopupRewardWidget : public UMobileBaseUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* RewardText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* RewardPicture;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UWidget* UnlockedPanel;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UWidget* MissedRewardPanel;

	UPROPERTY(EditDefaultsOnly)
	float RewardUnlockedTextOpacity;

	UPROPERTY(EditDefaultsOnly)
	float RewardToBeMissedTextOpacity;

public:
	UUMGRewardSlotTutorialPopupRewardWidget();
};

FORCEINLINE uint32 GetTypeHash(const UUMGRewardSlotTutorialPopupRewardWidget) { return 0; }
