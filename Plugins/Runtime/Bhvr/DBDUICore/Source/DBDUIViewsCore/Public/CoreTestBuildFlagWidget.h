#pragma once

#include "CoreMinimal.h"
#include "TestBuildFlagViewInterface.h"
#include "CoreBaseHudWidget.h"
#include "CoreTestBuildFlagWidget.generated.h"

class UGridPanel;
class UTextBlock;

UCLASS(EditInlineNew)
class DBDUIVIEWSCORE_API UCoreTestBuildFlagWidget : public UCoreBaseHudWidget, public ITestBuildFlagViewInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UGridPanel* HudTestFlagContainer;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* HudTopLineTextfield;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* HudBottomLineTextfield;

public:
	UCoreTestBuildFlagWidget();
};

FORCEINLINE uint32 GetTypeHash(const UCoreTestBuildFlagWidget) { return 0; }
