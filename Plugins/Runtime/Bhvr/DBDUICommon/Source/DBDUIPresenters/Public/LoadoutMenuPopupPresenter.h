#pragma once

#include "CoreMinimal.h"
#include "GenericPopupPresenter.h"
#include "ELoadoutSlot.h"
#include "InventorySlotData.h"
#include "EPlayerRole.h"
#include "LoadoutMenuPopupPresenter.generated.h"

class ULoadoutMenuPopupViewData;

UCLASS(EditInlineNew)
class DBDUIPRESENTERS_API ULoadoutMenuPopupPresenter : public UGenericPopupPresenter
{
	GENERATED_BODY()

private:
	UPROPERTY(Transient)
	TArray<ULoadoutMenuPopupViewData*> _loadoutPopupSlotData;

	UPROPERTY(Transient)
	TArray<ULoadoutMenuPopupViewData*> _loadoutPopupInventoryData;

private:
	UFUNCTION()
	ULoadoutMenuPopupViewData* SetLoadoutPopupViewData(const FInventorySlotData& slotData, const EPlayerRole playerRole);

	UFUNCTION()
	void OnSelectedCharacterChanged(int32 selectedCharacterIndex);

	UFUNCTION()
	void OnLoadoutMenuSlotIsSelected(ELoadoutSlot slotSelected);

	UFUNCTION()
	void OnLoadoutMenuPresetSelected(const int32 presetId, const ELoadoutSlot slotSelected);

	UFUNCTION()
	void OnLoadoutMenuPresetClicked(const int32 presetId, const ELoadoutSlot slotSelected);

	UFUNCTION()
	void OnLoadoutMenuInventorySlotClick(const ELoadoutSlot itemIndex, const FName itemId);

public:
	ULoadoutMenuPopupPresenter();
};

FORCEINLINE uint32 GetTypeHash(const ULoadoutMenuPopupPresenter) { return 0; }
