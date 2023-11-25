#pragma once

#include "CoreMinimal.h"
#include "MobileBaseUserWidget.h"
#include "EPlayerRole.h"
#include "UObject/NoExportTypes.h"
#include "UMGPlayerRankInfo.generated.h"

class UTextBlock;
class UUMGTallyPipsContainer;
class UUMGTallyRankFrame;
class UImage;
class UCanvasPanel;

UCLASS(Abstract, EditInlineNew)
class UUMGPlayerRankInfo : public UMobileBaseUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGTallyPipsContainer* PipsContainerWidget;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGTallyRankFrame* RankFrameWidget;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* Background;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* TitleLabel;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* RankLabel;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* PipLabel;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCanvasPanel* HighlightContainer;

	UPROPERTY(EditDefaultsOnly)
	FLinearColor _survivorColorBackground;

	UPROPERTY(EditDefaultsOnly)
	FLinearColor _killerColorBackground;

	UPROPERTY(EditDefaultsOnly)
	float _disableOpacity;

public:
	UFUNCTION(BlueprintCallable)
	void SetData(int32 rank, int32 pipsRequiredForNextRank, int32 filledPips, FText titleLabelNew, FText pipLabelNew, EPlayerRole playerRole, bool IsHighlight);

public:
	UUMGPlayerRankInfo();
};

FORCEINLINE uint32 GetTypeHash(const UUMGPlayerRankInfo) { return 0; }
