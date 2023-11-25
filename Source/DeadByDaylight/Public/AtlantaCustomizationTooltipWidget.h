#pragma once

#include "CoreMinimal.h"
#include "BaseTooltipWidget.h"
#include "AtlantaCustomizationTooltipWidget.generated.h"

class UImage;
class UUMGCustomizationTooltipContentWidget;
class UUMGCustomizationTooltipHeaderWidget;

UCLASS(Abstract, EditInlineNew)
class UAtlantaCustomizationTooltipWidget : public UBaseTooltipWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* SmokeImage;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGCustomizationTooltipHeaderWidget* Header;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGCustomizationTooltipContentWidget* Content;

public:
	UAtlantaCustomizationTooltipWidget();
};

FORCEINLINE uint32 GetTypeHash(const UAtlantaCustomizationTooltipWidget) { return 0; }
