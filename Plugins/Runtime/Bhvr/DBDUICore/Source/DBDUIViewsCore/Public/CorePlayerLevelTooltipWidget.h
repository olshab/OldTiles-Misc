#pragma once

#include "CoreMinimal.h"
#include "TooltipWidget.h"
#include "CorePlayerLevelTooltipViewData.h"
#include "CorePlayerLevelTooltipWidget.generated.h"

class UDBDTextBlock;
class UDBDRichTextBlock;

UCLASS(EditInlineNew)
class DBDUIVIEWSCORE_API UCorePlayerLevelTooltipWidget : public UTooltipWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDTextBlock* TitleTB;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDTextBlock* XPCurrentTitleTB;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDTextBlock* XPTB;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDTextBlock* XPNextTitleTB;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDTextBlock* NextXpTB;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDTextBlock* PlayerLevelTitleTB;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDTextBlock* PrestigeTitleTB;

	UPROPERTY(meta=(BindWidget))
	UDBDRichTextBlock* InfoTB;

public:
	UFUNCTION(BlueprintImplementableEvent)
	void SetTooltipData(const FCorePlayerLevelTooltipViewData& viewData);

public:
	UCorePlayerLevelTooltipWidget();
};

FORCEINLINE uint32 GetTypeHash(const UCorePlayerLevelTooltipWidget) { return 0; }
