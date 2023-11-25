#pragma once

#include "CoreMinimal.h"
#include "CoreButtonWidget.h"
#include "RankViewData.h"
#include "CoreRankWidgetConfiguration.h"
#include "CorePlayerRankWidget.generated.h"

class UDBDImage;
class UDBDTextBlock;

UCLASS(EditInlineNew)
class DBDUIVIEWSCORE_API UCorePlayerRankWidget : public UCoreButtonWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCoreRankWidgetConfiguration _widgetConfiguration;

	UPROPERTY(EditInstanceOnly)
	bool _showTooltipOnHover;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDImage* LevelBG;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDImage* RankNumberImage;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDTextBlock* LevelTB;

public:
	UFUNCTION(BlueprintCallable)
	void SetRankImageAndText(const int32 rankIndex, const bool isKiller);

	UFUNCTION(BlueprintImplementableEvent)
	void SetData(const FRankViewData& data);

protected:
	UFUNCTION(BlueprintPure)
	FCoreRankWidgetConfiguration GetConfiguration() const;

public:
	UCorePlayerRankWidget();
};

FORCEINLINE uint32 GetTypeHash(const UCorePlayerRankWidget) { return 0; }
