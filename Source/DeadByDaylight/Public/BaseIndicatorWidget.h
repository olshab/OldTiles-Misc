#pragma once

#include "CoreMinimal.h"
#include "MobileBaseUserWidget.h"
#include "BaseIndicatorWidget.generated.h"

class UCanvasPanel;
class UCanvasPanelSlot;
class UImage;

UCLASS(EditInlineNew)
class UBaseIndicatorWidget : public UMobileBaseUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(Transient, meta=(BindWidget))
	UCanvasPanel* _safeZonePanel;

	UPROPERTY(Transient, meta=(BindWidget))
	UCanvasPanelSlot* _canvasPanelSlot;

	UPROPERTY(EditDefaultsOnly)
	float RadiusMultiplier;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCanvasPanel* IndicatorPanel;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCanvasPanel* Indicator;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* ArrowImage;

protected:
	UFUNCTION()
	void OnOutAnimationFinished();

public:
	UBaseIndicatorWidget();
};

FORCEINLINE uint32 GetTypeHash(const UBaseIndicatorWidget) { return 0; }
