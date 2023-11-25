#pragma once

#include "CoreMinimal.h"
#include "MobileBaseUserWidget.h"
#include "CharacterSlotData.h"
#include "UMGCharacterButton.generated.h"

class UUMGCharacterPrice;
class UImage;
class UCanvasPanel;
class UTextBlock;

UCLASS(EditInlineNew)
class DEADBYDAYLIGHT_API UUMGCharacterButton : public UMobileBaseUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* PortraitIcon;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCanvasPanel* CharacterSelectedPanel;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCanvasPanel* LevelPanel;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* CharacterLevelText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* OwnedCustomizationText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* TotalCustomizationText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCanvasPanel* PricePanel;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGCharacterPrice* CellPrice;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGCharacterPrice* ShardPrice;

	UPROPERTY(BlueprintReadWrite, Transient)
	FCharacterSlotData CharacterSlotData;

public:
	UFUNCTION(BlueprintCallable)
	void SetIsSelected(bool isSelected);

	UFUNCTION(BlueprintCallable)
	void SetCharacterData(const FCharacterSlotData& characterData);

	UFUNCTION(BlueprintCallable)
	void BroadcastClickedEvent(int32 characterIndex);

public:
	UUMGCharacterButton();
};

FORCEINLINE uint32 GetTypeHash(const UUMGCharacterButton) { return 0; }
