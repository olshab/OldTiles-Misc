#pragma once

#include "CoreMinimal.h"
#include "ETooltipVerticalAlignment.h"
#include "LoadoutMenuPopupViewInterface.h"
#include "OnLoadoutMenuInventorySlotClick.h"
#include "Components/SlateWrapperTypes.h"
#include "CoreGenericPopupWidget.h"
#include "OnPaginationAnimationCompleted.h"
#include "OnLoadoutMenuSlotClick.h"
#include "LoadoutMenuSlotIsSelected.h"
#include "OnLoadoutMenuPresetSlotClick.h"
#include "OnSelectedCharacterChanged.h"
#include "Templates/SubclassOf.h"
#include "Layout/Margin.h"
#include "ETooltipHorizontalAlignment.h"
#include "TabWidgetData.h"
#include "ELoadoutSlot.h"
#include "EItemAvailability.h"
#include "LoadoutMenuPopupWidget.generated.h"

class UDBDDropDownListWidget;
class UDBDDropDownListButton;
class UDBDRichTextBlock;
class UCoreMenuOfferingWidget;
class UDBDTextBlock;
class UCoreMenuItemWidget;
class UCoreMenuPowerWidget;
class UCoreMenuAddonWidget;
class UCoreMenuPerkWidget;
class UCorePresetWidgetContainer;
class UGridPanel;
class UCorePaginationContainerWidget;
class UCoreInputSwitcherWidget;
class UMenuLoadoutPartViewData;
class UDBDImage;
class UCoreMenuLoadoutPartWidget;
class ULoadoutMenuPopupViewData;
class UCoreButtonWidget;

UCLASS(EditInlineNew)
class DBDUIVIEWSCORE_API ULoadoutMenuPopupWidget : public UCoreGenericPopupWidget, public ILoadoutMenuPopupViewInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDRichTextBlock* LoadoutMenuPowerItemRTB;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDRichTextBlock* LoadoutMenuAddonRTB;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDRichTextBlock* LoadoutMenuOfferingRTB;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDRichTextBlock* LoadoutMenuPerkRTB;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDTextBlock* BotRoleIndexText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDRichTextBlock* LoadoutMenuInventoryRTB;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDRichTextBlock* LoadoutMenuSubtitleRTB;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDRichTextBlock* LoadoutMenuPresetRTB;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UDBDDropDownListWidget* DropDownListWidget;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UDBDDropDownListButton* DropDownListTrigger;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCoreMenuPowerWidget* CoreMenuPower;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCoreMenuItemWidget* CoreMenuItem;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCoreMenuAddonWidget* CoreAddon_1;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCoreMenuAddonWidget* CoreAddon_2;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCoreMenuOfferingWidget* CoreOffering;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCoreMenuPerkWidget* CorePerk_1;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCoreMenuPerkWidget* CorePerk_2;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCoreMenuPerkWidget* CorePerk_3;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCoreMenuPerkWidget* CorePerk_4;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UCorePresetWidgetContainer* PresetContainer;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UGridPanel* InventoryGridContainer;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UCorePaginationContainerWidget* PaginationGridContainer;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UCoreInputSwitcherWidget* LeftArrow;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UCoreInputSwitcherWidget* RightArrow;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UDBDImage* PlusSignImage;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UDBDImage* LinkBarImage;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UDBDImage* AddonLinkBarImage;

	UPROPERTY()
	FOnPaginationAnimationCompleted _onPaginationAnimationCompletedDelegate;

	UPROPERTY()
	FOnLoadoutMenuSlotClick _onLoadoutMenuSlotClickedDelegate;

	UPROPERTY()
	FLoadoutMenuSlotIsSelected _onLoadoutMenuSlotSelectedDelegate;

	UPROPERTY()
	FOnLoadoutMenuInventorySlotClick _onLoadoutMenuInventorySlotClickedDelegate;

	UPROPERTY()
	FOnLoadoutMenuPresetSlotClick _onLoadoutMenuPresetSlotClickedDelegate;

	UPROPERTY()
	FOnSelectedCharacterChanged _onSelectedCharacterChangedDelegate;

	UPROPERTY(EditAnywhere, NoClear)
	TSubclassOf<UCoreMenuPowerWidget> _loadoutPowerClass;

	UPROPERTY(EditAnywhere, NoClear)
	TSubclassOf<UCoreMenuItemWidget> _loadoutItemWidgetClass;

	UPROPERTY(EditAnywhere, NoClear)
	TSubclassOf<UCoreMenuAddonWidget> _loadoutAddonClass;

	UPROPERTY(EditAnywhere, NoClear)
	TSubclassOf<UCoreMenuOfferingWidget> _loadoutOfferingClass;

	UPROPERTY(EditAnywhere, NoClear)
	TSubclassOf<UCoreMenuPerkWidget> _loadoutPerkClass;

	UPROPERTY(EditAnywhere, NoClear)
	TSubclassOf<UCorePaginationContainerWidget> _paginationWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 _inventoryPerRow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 _inventoryPerColumn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 _cellsPerRow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FMargin _inventoryItemPadding;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FMargin _inventoryPerkPadding;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FMargin _inventoryOfferingPadding;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _inventoryPerkExtraNudge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _inventoryOfferingExtraNudge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ETooltipHorizontalAlignment HorizontalAlignment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ETooltipVerticalAlignment VerticalAlignment;

private:
	UPROPERTY(Transient, Export)
	TArray<UCoreMenuLoadoutPartWidget*> _inventoryItemWidgetList;

	UPROPERTY(Transient, Export)
	TArray<UCoreMenuPerkWidget*> _perkSlotWidget;

	UPROPERTY(Transient, Export)
	TArray<UCoreMenuAddonWidget*> _addonSlotWidget;

	UPROPERTY(Transient)
	UMenuLoadoutPartViewData* _menuLoadoutPartViewData;

	UPROPERTY(Transient)
	ELoadoutSlot _loadoutSelectedSlot;

	UPROPERTY(Transient)
	int32 _numberOfPaginationItem;

	UPROPERTY(Transient)
	TArray<ULoadoutMenuPopupViewData*> _perkData;

	UPROPERTY(Transient)
	TArray<ULoadoutMenuPopupViewData*> _addonLoadoutData;

	UPROPERTY(Transient)
	TArray<ULoadoutMenuPopupViewData*> _inventoryViewData;

private:
	UFUNCTION(BlueprintCallable)
	void UpdateInventoryItemData();

	UFUNCTION(BlueprintCallable)
	void ShowMenuLoadoutPartsTooltip(UCoreButtonWidget* hoveredSlotWidget);

protected:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SetInventoryItemEnabled(UCoreMenuLoadoutPartWidget* widget, const EItemAvailability availability);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void PlayPaginationOutAnimation(bool isNextPage);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void PlayPaginationInAnimation();

private:
	UFUNCTION()
	void OnPaginationSelected(const int32 currentPage, bool isUpdate);

	UFUNCTION(BlueprintCallable)
	void OnLoadoutMenuRightArrowClicked();

	UFUNCTION(BlueprintCallable)
	void OnLoadoutMenuPresetClicked(const int32 selectedPresetId);

	UFUNCTION(BlueprintCallable)
	void OnLoadoutMenuPowerSlotClicked(UCoreButtonWidget* menuPowerWidget);

	UFUNCTION(BlueprintCallable)
	void OnLoadoutMenuPerkSlotClicked(UCoreButtonWidget* menuPerkWidget);

	UFUNCTION(BlueprintCallable)
	void OnLoadoutMenuOfferingSlotClicked(UCoreButtonWidget* menuOfferingWidget);

	UFUNCTION(BlueprintCallable)
	void OnLoadoutMenuLeftArrowClicked();

	UFUNCTION(BlueprintCallable)
	void OnLoadoutMenuItemSlotClicked(UCoreButtonWidget* menuItemWidget);

	UFUNCTION(BlueprintCallable)
	void OnLoadoutMenuInventorySlotClicked(UCoreButtonWidget* menuPerkWidget);

	UFUNCTION(BlueprintCallable)
	void OnLoadoutMenuAddonSlotClicked(UCoreButtonWidget* menuAddonWidget);

	UFUNCTION()
	void OnDropdownSelected(ESlateVisibility InVisibility);

	UFUNCTION()
	void OnDropDownListSelectedOptionChanged(FTabWidgetData buttonData);

	UFUNCTION(BlueprintCallable)
	void HideMenuLoadoutPartsTooltip(UCoreButtonWidget* unhoveredSlotWidget);

public:
	ULoadoutMenuPopupWidget();
};

FORCEINLINE uint32 GetTypeHash(const ULoadoutMenuPopupWidget) { return 0; }
