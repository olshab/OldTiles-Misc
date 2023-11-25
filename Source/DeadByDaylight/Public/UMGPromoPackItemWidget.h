#pragma once

#include "CoreMinimal.h"
#include "UMGBaseButtonWidget.h"
#include "UMGPromoPackItemWidget.generated.h"

class UCanvasPanel;

UCLASS(Abstract, EditInlineNew)
class UUMGPromoPackItemWidget : public UUMGBaseButtonWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCanvasPanel* SelectedPanel;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCanvasPanel* BackgroundPanel;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCanvasPanel* AmountPanel;

public:
	UUMGPromoPackItemWidget();
};

FORCEINLINE uint32 GetTypeHash(const UUMGPromoPackItemWidget) { return 0; }
