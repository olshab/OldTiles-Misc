#pragma once

#include "CoreMinimal.h"
#include "TeachableData.h"
#include "MobileBaseUserWidget.h"
#include "OnLoadoutItemButtonLongPressEvent.h"
#include "OnTeachableTooltipLongPressEvent.h"
#include "InventorySlotData.h"
#include "UObject/NoExportTypes.h"
#include "UMGCharacterScrollingInfoWidget.generated.h"

class UUMGTeachablePerkButton;
class UTextBlock;
class UUMGInventoryItemButton;
class UCanvasPanel;
class UUMGHtmlRichText;

UCLASS(EditInlineNew)
class UUMGCharacterScrollingInfoWidget : public UMobileBaseUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGTeachablePerkButton* FirstTeachablePerk;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGTeachablePerkButton* SecondTeachablePerk;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGTeachablePerkButton* ThirdTeachablePerk;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCanvasPanel* KillerInfoPanel;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGInventoryItemButton* KillerPower;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGHtmlRichText* CharacterBackstoryBox;

	UPROPERTY(BlueprintReadOnly)
	FText _killerPowerName;

	UPROPERTY(BlueprintReadOnly)
	FText _killerSpeedText;

	UPROPERTY(BlueprintReadOnly)
	FText _killerTerrorRadiusText;

	UPROPERTY(BlueprintReadOnly)
	FText _killerHeightText;

	UPROPERTY(BlueprintReadOnly)
	FText _perksTitle;

	UPROPERTY(BlueprintReadOnly)
	FText _teachablesTitle;

	UPROPERTY(BlueprintReadOnly)
	FText _powerTitle;

	UPROPERTY(BlueprintReadOnly)
	FText _attributesTitle;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* FirstTeachablePerkText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* SecondTeachablePerkText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* ThirdTeachablePerkText;

	UPROPERTY(BlueprintReadOnly)
	FText _backStoryTitle;

private:
	UPROPERTY(Transient, Export)
	TArray<UUMGTeachablePerkButton*> _teachablePerkArray;

	UPROPERTY(Transient, Export)
	TArray<UTextBlock*> _teachablePerkNameArray;

	UPROPERTY()
	FOnTeachableTooltipLongPressEvent _onTeachableTooltipTriggeredEvent;

	UPROPERTY()
	FOnLoadoutItemButtonLongPressEvent _onPowerButtonTooltipLongPressEvent;

private:
	UFUNCTION()
	void HandleTooltipLongPressedKillerPowerEvent(const FInventorySlotData& itemData, FVector2D position);

	UFUNCTION()
	void HandleTooltipLongPressedEvent(const FTeachableData& teachableData, const FVector2D& position);

public:
	UUMGCharacterScrollingInfoWidget();
};

FORCEINLINE uint32 GetTypeHash(const UUMGCharacterScrollingInfoWidget) { return 0; }
