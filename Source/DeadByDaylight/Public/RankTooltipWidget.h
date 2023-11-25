#pragma once

#include "CoreMinimal.h"
#include "BaseTooltipWidget.h"
#include "RankTooltipWidget.generated.h"

class UUMGPlayerRankInfo;
class UTextBlock;
class UGridPanel;

UCLASS(Abstract, EditInlineNew)
class URankTooltipWidget : public UBaseTooltipWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* RankInfoLabel;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* ResetInfoLabel;

	UPROPERTY(meta=(BindWidget))
	UGridPanel* RankInfoSlotsContainer;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGPlayerRankInfo* SurvivorRankInfoWidget;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGPlayerRankInfo* KillerRankInfoWidget;

public:
	URankTooltipWidget();
};

FORCEINLINE uint32 GetTypeHash(const URankTooltipWidget) { return 0; }
