#pragma once

#include "CoreMinimal.h"
#include "TooltipWidget.h"
#include "CompendiumButtonData.h"
#include "ArchiveCompendiumTooltipWidget.generated.h"

class UCoreStoryLevelsSelectorWidget;
class UDBDTextBlock;

UCLASS(EditInlineNew)
class DBDUIVIEWSCORE_API UArchiveCompendiumTooltipWidget : public UTooltipWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDTextBlock* TomeTitleTB;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDTextBlock* DescriptionTB;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCoreStoryLevelsSelectorWidget* StoryLevelsSelector;

public:
	UFUNCTION()
	void SetTooltipData(const FCompendiumButtonData& tooltipViewData);

	UFUNCTION()
	void Reset();

public:
	UArchiveCompendiumTooltipWidget();
};

FORCEINLINE uint32 GetTypeHash(const UArchiveCompendiumTooltipWidget) { return 0; }
