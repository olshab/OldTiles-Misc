#pragma once

#include "CoreMinimal.h"
#include "ECustomizationCategory.h"
#include "MobileBaseUserWidget.h"
#include "UObject/SoftObjectPtr.h"
#include "StoreItemSlotData.h"
#include "UMGCustomizationScreenWidget.generated.h"

class UUMGCustomizationPageScrollWidget;
class UUMGCustomizationCategoriesBar;
class UUMGCustomizationItemBuyButton;
class UUMGCustomizationItemWidget;
class UVerticalBox;
class UTextBlock;
class UCanvasPanel;

UCLASS(Abstract, EditInlineNew)
class UUMGCustomizationScreenWidget : public UMobileBaseUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGCustomizationPageScrollWidget* PageScrollWidget;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGCustomizationCategoriesBar* CustomizationCategoriesBar;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* CategoryLabel;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* CurrentlyEquippedLabel;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCanvasPanel* AvailableInOutfitsContainer;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCanvasPanel* UnlockItemContainer;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGCustomizationItemWidget* OutfitItem;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UVerticalBox* PriceContainer;

	UPROPERTY(EditDefaultsOnly, NoClear)
	TSoftClassPtr<UUMGCustomizationItemBuyButton> PriceButtonWidgetClass;

private:
	UPROPERTY(Transient)
	FName _currentSelectedItem;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void SetCategoryLabel(const ECustomizationCategory category);

private:
	UFUNCTION(BlueprintCallable)
	void BroadcastUnlockWithCurrencyEvent(int32 currencyId, const FString& combinedItem);

	UFUNCTION()
	void BroadcastCustomizationCategoryButtonPressed(int32 categoryIndex);

	UFUNCTION()
	void BroadcastAvailableItemSelectedEvent(int32 itemIndex, const FStoreItemSlotData& selectedItem, const FStoreItemSlotData& parentItem);

public:
	UUMGCustomizationScreenWidget();
};

FORCEINLINE uint32 GetTypeHash(const UUMGCustomizationScreenWidget) { return 0; }
