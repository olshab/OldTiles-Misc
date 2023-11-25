#pragma once

#include "CoreMinimal.h"
#include "UMGGenericPopup.h"
#include "Engine/EngineTypes.h"
#include "UMGAtlantaSeasonEndPopup.generated.h"

class UUMGTallyRankBanner;
class UHorizontalBox;

UCLASS(Abstract, EditInlineNew)
class UUMGAtlantaSeasonEndPopup : public UUMGGenericPopup
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGTallyRankBanner* OldSurvivorRankBanner;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGTallyRankBanner* NewSurvivorRankBanner;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGTallyRankBanner* OldKillerRankBanner;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGTallyRankBanner* NewKillerRankBanner;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UHorizontalBox* NewRankHorizontalBox;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UHorizontalBox* OldRankHorizontalBox;

private:
	UPROPERTY(Transient)
	FTimerHandle _fadeOutTimerHandle;

	UPROPERTY(EditDefaultsOnly)
	float _timerBeforeFadeOutAnimation;

private:
	UFUNCTION()
	void TriggerFadeOutAnimationTimer();

	UFUNCTION()
	void PlayNewRankFadeInAnimation();

public:
	UUMGAtlantaSeasonEndPopup();
};

FORCEINLINE uint32 GetTypeHash(const UUMGAtlantaSeasonEndPopup) { return 0; }
