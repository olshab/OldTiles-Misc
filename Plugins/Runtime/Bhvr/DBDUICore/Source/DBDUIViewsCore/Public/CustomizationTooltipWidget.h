#pragma once

#include "CoreMinimal.h"
#include "TooltipWidget.h"
#include "CustomizationTooltipViewData.h"
#include "CustomizationTooltipWidget.generated.h"

class UDBDTextBlock;
class UDBDRichTextBlock;

UCLASS(EditInlineNew)
class DBDUIVIEWSCORE_API UCustomizationTooltipWidget : public UTooltipWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDTextBlock* ToolTipStatusTB;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDRichTextBlock* ToolTipDescriptionRTB;

public:
	UFUNCTION(BlueprintImplementableEvent)
	void SetTooltipData(const FCustomizationTooltipViewData& customizationViewData);

protected:
	UFUNCTION(BlueprintCallable)
	void SetStatusText(const bool isEquipped, const bool isOwned, const bool isLocked);

public:
	UFUNCTION()
	void AppendToDescriptionText(const FText& appendedText);

public:
	UCustomizationTooltipWidget();
};

FORCEINLINE uint32 GetTypeHash(const UCustomizationTooltipWidget) { return 0; }
