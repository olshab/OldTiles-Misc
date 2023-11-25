#pragma once

#include "CoreMinimal.h"
#include "UMGSettingContextWidget.h"
#include "UMGSettingTutorialContextWidget.generated.h"

class UUMGSettingContextButton;

UCLASS(Abstract, EditInlineNew)
class UUMGSettingTutorialContextWidget : public UUMGSettingContextWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGSettingContextButton* SurvivorTutorialButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGSettingContextButton* KillerTutorialButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGSettingContextButton* SurvivorCinematicButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGSettingContextButton* KillerCinematicButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGSettingContextButton* LoreCinematicButton;

public:
	UUMGSettingTutorialContextWidget();
};

FORCEINLINE uint32 GetTypeHash(const UUMGSettingTutorialContextWidget) { return 0; }
