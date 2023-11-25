#pragma once

#include "CoreMinimal.h"
#include "TooltipWidget.h"
#include "ArchiveRewardNodeTooltipWidget.generated.h"

class UCustomizationTooltipWidget;
class UCurrencyProgressionTooltipWidget;

UCLASS(EditInlineNew)
class DBDUIVIEWSCORE_API UArchiveRewardNodeTooltipWidget : public UTooltipWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCustomizationTooltipWidget* CustomizationTooltip;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCurrencyProgressionTooltipWidget* CurrencyProgressionTooltip;

public:
	UArchiveRewardNodeTooltipWidget();
};

FORCEINLINE uint32 GetTypeHash(const UArchiveRewardNodeTooltipWidget) { return 0; }
