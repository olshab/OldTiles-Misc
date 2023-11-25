#pragma once

#include "CoreMinimal.h"
#include "CoreBaseUserWidget.h"
#include "CoreEndGameCollapseProgressWidget.generated.h"

class UProgressBar;
class UCanvasPanel;
class UHorizontalBoxSlot;

UCLASS(EditInlineNew)
class UCoreEndGameCollapseProgressWidget : public UCoreBaseUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UProgressBar* ProgressBar;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCanvasPanel* MarkerLeftCanvas;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCanvasPanel* MarkerRightCanvas;

private:
	UPROPERTY(Transient, Export)
	UHorizontalBoxSlot* _markerLeftBox;

	UPROPERTY(Transient, Export)
	UHorizontalBoxSlot* _markerRightBox;

public:
	UCoreEndGameCollapseProgressWidget();
};

FORCEINLINE uint32 GetTypeHash(const UCoreEndGameCollapseProgressWidget) { return 0; }
