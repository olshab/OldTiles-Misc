#pragma once

#include "CoreMinimal.h"
#include "UMGGenericPopup.h"
#include "UObject/SoftObjectPtr.h"
#include "UMGAtlantaRankUpPopup.generated.h"

class UCanvasPanel;
class UUMGTallyRankBanner;
class UHorizontalBox;
class UUMGRewardWidget;

UCLASS(Abstract, EditInlineNew)
class UUMGAtlantaRankUpPopup : public UUMGGenericPopup
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGTallyRankBanner* RankBanner;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UHorizontalBox* RewardsContainer;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCanvasPanel* RewardsSection;

	UPROPERTY(EditAnywhere, NoClear)
	TSoftClassPtr<UUMGRewardWidget> RewardWidgetClass;

private:
	UFUNCTION()
	void PlayRankUpBannerAnimation();

public:
	UUMGAtlantaRankUpPopup();
};

FORCEINLINE uint32 GetTypeHash(const UUMGAtlantaRankUpPopup) { return 0; }
