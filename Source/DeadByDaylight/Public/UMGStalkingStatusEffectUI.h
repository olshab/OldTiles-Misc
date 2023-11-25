#pragma once

#include "CoreMinimal.h"
#include "MobileBaseUserWidget.h"
#include "UMGStalkingStatusEffectUI.generated.h"

class UMaterialInstanceDynamic;
class UCanvasPanel;
class UImage;

UCLASS(Abstract, EditInlineNew)
class DEADBYDAYLIGHT_API UUMGStalkingStatusEffectUI : public UMobileBaseUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCanvasPanel* StalkedCanvas;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* StalkingFillFull;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* StalkingFillLines;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* StalkingRedBackground;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName StalkingStartAnimationName;

private:
	UPROPERTY(Transient)
	UMaterialInstanceDynamic* _stalkingFillFullMI;

	UPROPERTY(Transient)
	UMaterialInstanceDynamic* _stalkingFillLinesMI;

public:
	UUMGStalkingStatusEffectUI();
};

FORCEINLINE uint32 GetTypeHash(const UUMGStalkingStatusEffectUI) { return 0; }
