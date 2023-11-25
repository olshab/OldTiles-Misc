#pragma once

#include "CoreMinimal.h"
#include "TooltipWidget.h"
#include "LoadoutTooltipData.h"
#include "LoadoutTooltipWidget.generated.h"

class UDBDTextBlock;
class UDBDRichTextBlock;
class UDBDImage;

UCLASS(EditInlineNew)
class DBDUIVIEWSCORE_API ULoadoutTooltipWidget : public UTooltipWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDTextBlock* TooltipTitle;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDRichTextBlock* ToolTipDescriptionRTB;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDTextBlock* SpecialEventTitle;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDTextBlock* SpecialEventDescription;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDTextBlock* UnlockInstructionText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDTextBlock* RarityTypeSubtitle;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDImage* RarityBG;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDImage* Line_1;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDImage* LevelIcon;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDRichTextBlock* ToolTipWarning;

public:
	UFUNCTION()
	void SetTooltipData(const FLoadoutTooltipData& tooltipViewData);

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void SetLoadoutTooltipPerkLevel(int32 level);

	UFUNCTION(BlueprintImplementableEvent)
	void SetLoadoutTooltipLockedState();

public:
	UFUNCTION()
	void Reset();

public:
	ULoadoutTooltipWidget();
};

FORCEINLINE uint32 GetTypeHash(const ULoadoutTooltipWidget) { return 0; }
