#pragma once

#include "CoreMinimal.h"
#include "OnTooltipTriggeredEvent.h"
#include "Highlightable.h"
#include "MobileBaseUserWidget.h"
#include "EPlayerRole.h"
#include "UMGRankBanner.generated.h"

class UAkAudioEvent;
class UUMGTallyRankFrame;
class UButton;
class UImage;

UCLASS(Abstract, EditInlineNew)
class UUMGRankBanner : public UMobileBaseUserWidget, public IHighlightable
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGTallyRankFrame* RankFrameWidget;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UButton* TooltipButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* HighlightImage;

	UPROPERTY(EditDefaultsOnly)
	UAkAudioEvent* OnLongPressSound;

private:
	UPROPERTY()
	FOnTooltipTriggeredEvent _onLongPressRankTooltipEvent;

public:
	UFUNCTION(BlueprintCallable)
	void StopHighlight();

	UFUNCTION(BlueprintCallable)
	void StartHighlight();

	UFUNCTION(BlueprintCallable)
	void SetData(int32 rank, EPlayerRole playerRole);

private:
	UFUNCTION()
	void HandleTooltipLongPressedEvent();

public:
	UUMGRankBanner();
};

FORCEINLINE uint32 GetTypeHash(const UUMGRankBanner) { return 0; }
