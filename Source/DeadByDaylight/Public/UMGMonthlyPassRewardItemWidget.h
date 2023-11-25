#pragma once

#include "CoreMinimal.h"
#include "MobileBaseUserWidget.h"
#include "UObject/NoExportTypes.h"
#include "UMGMonthlyPassRewardItemWidget.generated.h"

class UTextBlock;
class UImage;
class UCanvasPanel;

UCLASS(Abstract, EditInlineNew)
class DEADBYDAYLIGHT_API UUMGMonthlyPassRewardItemWidget : public UMobileBaseUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* ItemAmount;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* ItemName;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* ItemIcon;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* CheckIcon;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* ItemFrame;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* ItemRarityBackground;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCanvasPanel* ItemPaintPanel;

	UPROPERTY(EditDefaultsOnly)
	FLinearColor ActiveItemFrameColor;

	UPROPERTY(EditDefaultsOnly)
	FLinearColor NonActiveItemFrameColor;

public:
	UUMGMonthlyPassRewardItemWidget();
};

FORCEINLINE uint32 GetTypeHash(const UUMGMonthlyPassRewardItemWidget) { return 0; }
