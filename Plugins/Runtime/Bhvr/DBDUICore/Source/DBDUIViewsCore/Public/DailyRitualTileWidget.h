#pragma once

#include "CoreMinimal.h"
#include "DailyRitualViewData.h"
#include "CoreBaseUserWidget.h"
#include "RemovedDailyRitualDelegate.h"
#include "OnDailyRitualTileFadeOutCompletedDelegate.h"
#include "ClaimedRitualDelegate.h"
#include "OnDailyRitualTileFadeInCompletedDelegate.h"
#include "DailyRitualTileWidget.generated.h"

class UMaterialInterface;
class USizeBox;
class UDBDTextBlock;
class UCoreButtonWidget;
class UDBDImage;

UCLASS(EditInlineNew)
class DBDUIVIEWSCORE_API UDailyRitualTileWidget : public UCoreBaseUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	FClaimedRitualDelegate _claimButtonClickedDelegate;

	UPROPERTY()
	FRemovedDailyRitualDelegate _removeButtonClickedDelegate;

	UPROPERTY()
	FOnDailyRitualTileFadeInCompletedDelegate _onDailyRitualTileFadeInCompletedDelegate;

	UPROPERTY()
	FOnDailyRitualTileFadeOutCompletedDelegate _onDailyRitualTileFadeOutCompletedDelegate;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	USizeBox* ContainerSizeBox;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDImage* IconImage;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDImage* BackgroundImage;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDImage* ProgressBar;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDImage* BackgroundSheen;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDTextBlock* TitleTextBlock;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDTextBlock* RewardTextBlock;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDTextBlock* DescriptionTextBlock;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDTextBlock* ProgressTextBlock;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCoreButtonWidget* ClaimButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCoreButtonWidget* RemoveButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, NoClear)
	UMaterialInterface* DefaultBackgroundTexture;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, NoClear)
	UMaterialInterface* NewBackgroundTexture;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, NoClear)
	UMaterialInterface* CompletedBackgroundTexture;

	UPROPERTY(BlueprintReadOnly)
	FDailyRitualViewData _dailyRitualData;

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void PlayFadeOutAnimation();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void PlayFadeInAnimation();

protected:
	UFUNCTION()
	void OnRemoveButtonClicked(UCoreButtonWidget* button);

	UFUNCTION()
	void OnClaimButtonClicked(UCoreButtonWidget* button);

public:
	UDailyRitualTileWidget();
};

FORCEINLINE uint32 GetTypeHash(const UDailyRitualTileWidget) { return 0; }
