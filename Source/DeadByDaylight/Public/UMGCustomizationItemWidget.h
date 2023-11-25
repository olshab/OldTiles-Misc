#pragma once

#include "CoreMinimal.h"
#include "MobileBaseUserWidget.h"
#include "UObject/SoftObjectPtr.h"
#include "UMGCustomizationItemWidget.generated.h"

class UImage;
class UCanvasPanel;
class UVerticalBox;
class UUMGCustomizationItemPriceWidget;

UCLASS(Abstract, EditInlineNew)
class UUMGCustomizationItemWidget : public UMobileBaseUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* RarityBackground;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* PaintOverlay;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* Icon;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCanvasPanel* NewIndicator;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCanvasPanel* OutfitIndicator;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UVerticalBox* PricesContainer;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCanvasPanel* ItemSelectedBorder;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCanvasPanel* EquippedContainer;

	UPROPERTY(EditDefaultsOnly, NoClear)
	TSoftClassPtr<UUMGCustomizationItemPriceWidget> _customizationItemPriceWidgetClass;

private:
	UPROPERTY(Transient, Export)
	TArray<UUMGCustomizationItemPriceWidget*> _priceWidgets;

	UPROPERTY(Transient)
	int32 _itemIndex;

	UPROPERTY(Transient)
	FName _itemId;

protected:
	UFUNCTION(BlueprintCallable)
	void BroadcastAvailableItemSelected();

public:
	UUMGCustomizationItemWidget();
};

FORCEINLINE uint32 GetTypeHash(const UUMGCustomizationItemWidget) { return 0; }
