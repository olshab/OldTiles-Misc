#pragma once

#include "CoreMinimal.h"
#include "ECustomizationCategory.h"
#include "MobileBaseUserWidget.h"
#include "UMGCustomizationTooltipHeaderWidget.generated.h"

class UTextBlock;

UCLASS(Abstract, EditInlineNew)
class UUMGCustomizationTooltipHeaderWidget : public UMobileBaseUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* Title;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* CollectionName;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* CategoryAndRarityText;

public:
	UFUNCTION(BlueprintImplementableEvent)
	void SetOutfitComposition(const bool isUnbreakable, const TArray<ECustomizationCategory>& composition);

public:
	UUMGCustomizationTooltipHeaderWidget();
};

FORCEINLINE uint32 GetTypeHash(const UUMGCustomizationTooltipHeaderWidget) { return 0; }
