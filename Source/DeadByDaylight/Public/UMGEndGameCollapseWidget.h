#pragma once

#include "CoreMinimal.h"
#include "MobileBaseUserWidget.h"
#include "UMGEndGameCollapseWidget.generated.h"

class UCanvasPanel;
class UUMGEndGameCollapseProgressWidget;

UCLASS(EditInlineNew)
class UUMGEndGameCollapseWidget : public UMobileBaseUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	float _progressBarInterpSpeed;

	UPROPERTY(BlueprintReadOnly)
	bool _slowMode;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCanvasPanel* NormalBar;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCanvasPanel* SlowBar;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGEndGameCollapseProgressWidget* NormalProgressBar;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGEndGameCollapseProgressWidget* SlowProgressBar;

private:
	UPROPERTY(Transient, Export)
	UUMGEndGameCollapseProgressWidget* _topBar;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void PlayToZeroAnimation();

public:
	UUMGEndGameCollapseWidget();
};

FORCEINLINE uint32 GetTypeHash(const UUMGEndGameCollapseWidget) { return 0; }
