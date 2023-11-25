#pragma once

#include "CoreMinimal.h"
#include "MobileBaseUserWidget.h"
#include "UMGCustomizationTooltipContentWidget.generated.h"

class UUMGHtmlRichText;
class UUMGCustomizationInfoWidget;
class UUMGCustomizationItemPriceWidget;

UCLASS(Abstract, EditInlineNew)
class UUMGCustomizationTooltipContentWidget : public UMobileBaseUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGHtmlRichText* ItemDescription;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGCustomizationInfoWidget* OutfitInformation;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGCustomizationInfoWidget* RoleInformation;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGCustomizationInfoWidget* ReplacementInformation;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGCustomizationItemPriceWidget* AuricCellsPrice;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGCustomizationItemPriceWidget* IridescentShardsPrice;

public:
	UUMGCustomizationTooltipContentWidget();
};

FORCEINLINE uint32 GetTypeHash(const UUMGCustomizationTooltipContentWidget) { return 0; }
