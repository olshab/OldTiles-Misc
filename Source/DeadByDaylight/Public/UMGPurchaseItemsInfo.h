#pragma once

#include "CoreMinimal.h"
#include "MobileBaseUserWidget.h"
#include "UMGPurchaseItemsInfo.generated.h"

class UImage;
class UTextBlock;

UCLASS(Abstract, EditInlineNew)
class UUMGPurchaseItemsInfo : public UMobileBaseUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* Icon;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* Quantity;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* ItemName;

public:
	UUMGPurchaseItemsInfo();
};

FORCEINLINE uint32 GetTypeHash(const UUMGPurchaseItemsInfo) { return 0; }
