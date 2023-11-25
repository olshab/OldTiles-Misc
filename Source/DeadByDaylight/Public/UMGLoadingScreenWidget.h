#pragma once

#include "CoreMinimal.h"
#include "MobileBaseUserWidget.h"
#include "UMGLoadingScreenWidget.generated.h"

class UTextBlock;
class UImage;
class UProgressBar;
class UPanelWidget;

UCLASS(EditInlineNew)
class UUMGLoadingScreenWidget : public UMobileBaseUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* Description;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, meta=(BindWidget))
	UImage* HintIcon;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, meta=(BindWidget))
	UProgressBar* LoadingBar;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, meta=(BindWidget))
	UPanelWidget* KillerPanel;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, meta=(BindWidget))
	UPanelWidget* SurvivorPanel;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* Title;

public:
	UUMGLoadingScreenWidget();
};

FORCEINLINE uint32 GetTypeHash(const UUMGLoadingScreenWidget) { return 0; }
