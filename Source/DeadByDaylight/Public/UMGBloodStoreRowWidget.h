#pragma once

#include "CoreMinimal.h"
#include "Layout/Margin.h"
#include "MobileBaseUserWidget.h"
#include "EBloodStoreRowStyle.h"
#include "UObject/SoftObjectPtr.h"
#include "UMGBloodStoreRowWidget.generated.h"

class UHorizontalBox;
class UCanvasPanel;
class UUMGBloodStoreItemWidget;

UCLASS(Abstract, EditInlineNew)
class UUMGBloodStoreRowWidget : public UMobileBaseUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UHorizontalBox* ItemContainer;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCanvasPanel* LockStatusPanel;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCanvasPanel* HardLockedStatusPanel;

	UPROPERTY(BlueprintReadOnly)
	int32 _purchasedItemsNbr;

	UPROPERTY(BlueprintReadOnly)
	int32 _requiredItemNbr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EBloodStoreRowStyle _rowStyle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FMargin _itemPadding;

private:
	UPROPERTY(EditAnywhere, NoClear)
	TSoftClassPtr<UUMGBloodStoreItemWidget> _itemWidgetClass;

	UPROPERTY(Transient)
	UClass* _itemClass;

public:
	UFUNCTION(BlueprintImplementableEvent)
	void UnlockRow(bool playAnim);

	UFUNCTION(BlueprintImplementableEvent)
	void LockRow(bool playAnim);

protected:
	UFUNCTION(BlueprintCallable)
	void BroadcastUnlockAnimationFinished();

private:
	UFUNCTION()
	void BroadcastBloodNodeSelected(const FString& id);

public:
	UUMGBloodStoreRowWidget();
};

FORCEINLINE uint32 GetTypeHash(const UUMGBloodStoreRowWidget) { return 0; }
