#pragma once

#include "CoreMinimal.h"
#include "MobileBaseUserWidget.h"
#include "RewardLayoutWidgetToGenerate.h"
#include "UMGRewardPopupLayout.generated.h"

class UHorizontalBox;
class UUMGRewardSlotTutorialPopupRewardWidget;

UCLASS(Abstract, EditInlineNew)
class UUMGRewardPopupLayout : public UMobileBaseUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UHorizontalBox* TopHorizontalBox;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UHorizontalBox* BottomHorizontalBox;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGRewardSlotTutorialPopupRewardWidget* FirstCharacter;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGRewardSlotTutorialPopupRewardWidget* SecondCharacter;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGRewardSlotTutorialPopupRewardWidget* ThirdCharacter;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGRewardSlotTutorialPopupRewardWidget* FourthCharacter;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGRewardSlotTutorialPopupRewardWidget* FifthCharacter;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGRewardSlotTutorialPopupRewardWidget* AuricCells;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGRewardSlotTutorialPopupRewardWidget* IridescentShards;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGRewardSlotTutorialPopupRewardWidget* Bloodpoints;

	UPROPERTY(EditDefaultsOnly)
	FRewardLayoutWidgetToGenerate TopWidgetToGenerate;

	UPROPERTY(EditDefaultsOnly)
	FRewardLayoutWidgetToGenerate BottomWidgetToGenerate;

public:
	UUMGRewardPopupLayout();
};

FORCEINLINE uint32 GetTypeHash(const UUMGRewardPopupLayout) { return 0; }
