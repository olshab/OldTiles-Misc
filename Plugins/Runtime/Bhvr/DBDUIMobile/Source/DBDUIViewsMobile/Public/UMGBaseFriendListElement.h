#pragma once

#include "CoreMinimal.h"
#include "MobileBaseUserWidget.h"
#include "AtlantaFriendUIData.h"
#include "EActionOnFriendType.h"
#include "UMGBaseFriendListElement.generated.h"

class UCanvasPanel;
class UUMGBaseButtonWidget;
class UDataTable;
class UNamedSlot;
class UImage;
class UTextBlock;

UCLASS(Abstract, EditInlineNew)
class DBDUIVIEWSMOBILE_API UUMGBaseFriendListElement : public UMobileBaseUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta=(BindWidget))
	UImage* StatusPicture;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* FriendName;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* FriendStatus;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCanvasPanel* SelectionHighlight;

	UPROPERTY(meta=(BindWidget))
	UUMGBaseButtonWidget* ItemSelectionBaseButton;

	UPROPERTY(meta=(BindWidget))
	UNamedSlot* ContextualMenuPosition;

	UPROPERTY()
	FAtlantaFriendUIData _cachedFriendData;

	UPROPERTY(EditAnywhere)
	UDataTable* FriendUIStatusDataTable;

public:
	UFUNCTION(BlueprintCallable)
	void TriggerActionOnThisFriend(EActionOnFriendType actionType);

public:
	UUMGBaseFriendListElement();
};

FORCEINLINE uint32 GetTypeHash(const UUMGBaseFriendListElement) { return 0; }
