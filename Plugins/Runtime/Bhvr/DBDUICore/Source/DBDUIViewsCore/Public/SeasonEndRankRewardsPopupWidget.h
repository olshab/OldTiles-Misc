#pragma once

#include "CoreMinimal.h"
#include "SeasonEndRankRewardsPopupViewInterface.h"
#include "CoreGenericPopupWidget.h"
#include "SeasonEndRankRewardsPopupWidget.generated.h"

class UCorePlayerRankWidget;
class UCoreCurrencyProgressionRewardWidget;
class UDBDRichTextBlock;

UCLASS(EditInlineNew)
class DBDUIVIEWSCORE_API USeasonEndRankRewardsPopupWidget : public UCoreGenericPopupWidget, public ISeasonEndRankRewardsPopupViewInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDRichTextBlock* SurvivorSeasonHighRTB;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDRichTextBlock* KillerSeasonHighRTB;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDRichTextBlock* DisclaimerMessageRTB;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDRichTextBlock* SurvivorRankRTB;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDRichTextBlock* KillerRankRTB;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCorePlayerRankWidget* SurvivorRank;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCoreCurrencyProgressionRewardWidget* SurvivorReward;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCorePlayerRankWidget* KillerRank;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCoreCurrencyProgressionRewardWidget* KillerReward;

public:
	USeasonEndRankRewardsPopupWidget();
};

FORCEINLINE uint32 GetTypeHash(const USeasonEndRankRewardsPopupWidget) { return 0; }
