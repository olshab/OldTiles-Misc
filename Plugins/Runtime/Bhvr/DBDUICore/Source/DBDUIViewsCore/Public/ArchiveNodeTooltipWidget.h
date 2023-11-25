#pragma once

#include "CoreMinimal.h"
#include "TooltipWidget.h"
#include "EArchiveNodeType.h"
#include "Templates/SubclassOf.h"
#include "ArchiveNodeViewData.h"
#include "ArchiveNodeTooltipWidget.generated.h"

class UDBDImage;
class UVerticalBox;
class UCoreArchiveObjectiveWidget;
class UDBDTextBlock;
class UDBDRichTextBlock;
class UCoreCurrencyForTooltipsWidget;
class UHorizontalBox;

UCLASS(EditInlineNew)
class DBDUIVIEWSCORE_API UArchiveNodeTooltipWidget : public UTooltipWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDImage* BackgroundIMG;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDImage* RarityIMG;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDTextBlock* NodeTitleTB;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDTextBlock* SubtitleTB;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDRichTextBlock* NodeDescriptionRTB;

	UPROPERTY(EditAnywhere, NoClear)
	TSubclassOf<UCoreArchiveObjectiveWidget> ObjectiveWidgetClass;

	UPROPERTY(EditAnywhere, NoClear)
	TSubclassOf<UCoreCurrencyForTooltipsWidget> RewardWidgetClass;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UVerticalBox* ArchiveObjectivesContainer;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UHorizontalBox* RewardsContainer;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDRichTextBlock* VignetteRTB;

public:
	UFUNCTION()
	void SetTooltipData(const FArchiveNodeViewData& nodeViewData);

	UFUNCTION(BlueprintImplementableEvent)
	void SetNodeType(EArchiveNodeType type);

	UFUNCTION()
	void Reset();

public:
	UArchiveNodeTooltipWidget();
};

FORCEINLINE uint32 GetTypeHash(const UArchiveNodeTooltipWidget) { return 0; }
