#pragma once

#include "CoreMinimal.h"
#include "TooltipWidget.h"
#include "RankTooltipViewData.h"
#include "CoreRankTooltipWidget.generated.h"

class UDBDTextBlock;
class UDBDRichTextBlock;

UCLASS(EditInlineNew)
class DBDUIVIEWSCORE_API UCoreRankTooltipWidget : public UTooltipWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDTextBlock* TitleTB;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDTextBlock* RankNameTB;

	UPROPERTY(meta=(BindWidget))
	UDBDTextBlock* ProgressTB;

	UPROPERTY(meta=(BindWidget))
	UDBDRichTextBlock* InfoTB;

public:
	UFUNCTION(BlueprintNativeEvent)
	void SetTooltipData(const FRankTooltipViewData& viewData);

public:
	UCoreRankTooltipWidget();
};

FORCEINLINE uint32 GetTypeHash(const UCoreRankTooltipWidget) { return 0; }
