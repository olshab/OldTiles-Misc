#pragma once

#include "CoreMinimal.h"
#include "UMGPromoPackItemWidget.h"
#include "UMGStorefrontCustomizationWidget.generated.h"

class UCanvasPanel;
class UTextBlock;

UCLASS(Abstract, EditInlineNew)
class UUMGStorefrontCustomizationWidget : public UUMGPromoPackItemWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* CustomizationQuantityText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCanvasPanel* CustomizationQuantityPanel;

public:
	UUMGStorefrontCustomizationWidget();
};

FORCEINLINE uint32 GetTypeHash(const UUMGStorefrontCustomizationWidget) { return 0; }
