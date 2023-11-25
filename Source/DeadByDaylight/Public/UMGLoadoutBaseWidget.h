#pragma once

#include "CoreMinimal.h"
#include "MobileBaseUserWidget.h"
#include "UObject/NoExportTypes.h"
#include "InventorySlotData.h"
#include "ELoadoutSlot.h"
#include "UMGLoadoutBaseWidget.generated.h"

class UUMGLoadoutItemButton;

UCLASS(EditInlineNew)
class UUMGLoadoutBaseWidget : public UMobileBaseUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGLoadoutItemButton* ItemOrPowerButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGLoadoutItemButton* AddonFirstButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGLoadoutItemButton* AddonSecondButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGLoadoutItemButton* OfferingButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGLoadoutItemButton* PerkFirstButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGLoadoutItemButton* PerkSecondButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGLoadoutItemButton* PerkThirdButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGLoadoutItemButton* PerkFourthButton;

	UPROPERTY(BlueprintReadOnly, Transient, Export)
	TArray<UUMGLoadoutItemButton*> LoadoutItemButtons;

	UPROPERTY(BlueprintReadOnly)
	bool UsingMatchRules;

	UPROPERTY(BlueprintReadOnly)
	bool PerkSlotsLockedByAdmin;

	UPROPERTY(BlueprintReadOnly)
	bool IsSlasher;

public:
	UFUNCTION(BlueprintCallable)
	void SetLoadoutData(const TArray<FInventorySlotData>& loadoutData, bool usingMatchRulesNew, bool perkSlotsLockedByAdminNew, ELoadoutSlot loadoutSlot, bool isSlasherNew, bool isClickable);

	UFUNCTION(BlueprintImplementableEvent)
	void SetIsSelectedLoadoutItemButton(ELoadoutSlot loadoutSlot);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SetDividerImageColor(FLinearColor color);

public:
	UUMGLoadoutBaseWidget();
};

FORCEINLINE uint32 GetTypeHash(const UUMGLoadoutBaseWidget) { return 0; }
