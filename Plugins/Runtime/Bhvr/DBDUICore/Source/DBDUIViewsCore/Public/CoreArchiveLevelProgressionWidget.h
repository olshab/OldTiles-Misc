#pragma once

#include "CoreMinimal.h"
#include "TomeLevelRewardAnimationDoneDelegate.h"
#include "ArchiveLevelProgressionViewInterface.h"
#include "CoreBaseUserWidget.h"
#include "TomeLevelUnlockedAnimationDoneDelegate.h"
#include "TomeLevelSelectedDelegate.h"
#include "TomeLevelAnimationDoneDelegate.h"
#include "CoreArchiveLevelProgressionWidget.generated.h"

class UDBDTextBlock;
class UCoreStoryLevelsSelectorWidget;
class UOverlay;
class UCoreSelectableButtonWidget;

UCLASS(EditInlineNew)
class DBDUIVIEWSCORE_API UCoreArchiveLevelProgressionWidget : public UCoreBaseUserWidget, public IArchiveLevelProgressionViewInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	FTomeLevelSelectedDelegate _levelSelectedDelegate;

	UPROPERTY()
	FTomeLevelAnimationDoneDelegate _levelAnimationDoneDelegate;

	UPROPERTY()
	FTomeLevelRewardAnimationDoneDelegate _levelRewardAnimationDoneDelegate;

	UPROPERTY()
	FTomeLevelUnlockedAnimationDoneDelegate _levelUnlockedAnimationDoneDelegate;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCoreStoryLevelsSelectorWidget* StoryLevelsSelector;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDTextBlock* LevelNumberTF;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDTextBlock* LevelCompletionTF;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UOverlay* SideContent;

private:
	UFUNCTION()
	void OnTomeLevelUnlockedAnimation();

protected:
	UFUNCTION()
	void OnStoryLevelSelected(UCoreSelectableButtonWidget* selectedButton);

public:
	UCoreArchiveLevelProgressionWidget();
};

FORCEINLINE uint32 GetTypeHash(const UCoreArchiveLevelProgressionWidget) { return 0; }
