#pragma once

#include "CoreMinimal.h"
#include "MobileBaseUserWidget.h"
#include "UObject/SoftObjectPtr.h"
#include "ECurrencyType.h"
#include "Styling/SlateColor.h"
#include "UMGCustomizationItemPriceWidget.generated.h"

class UTextBlock;
class UTexture2D;
class UImage;

UCLASS(Abstract, EditInlineNew)
class UUMGCustomizationItemPriceWidget : public UMobileBaseUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* CurrencyValue;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* DiscountPercentageContainer;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* DiscountPercentage;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* CurrencyIcon;

	UPROPERTY(EditDefaultsOnly)
	TMap<ECurrencyType, TSoftObjectPtr<UTexture2D>> CurrencyTextures;

	UPROPERTY(EditDefaultsOnly)
	FSlateColor AffordableCurrencyTextColor;

	UPROPERTY(EditDefaultsOnly)
	FSlateColor AffordableSpecialCurrencyTextColor;

	UPROPERTY(EditDefaultsOnly)
	FSlateColor NonAffordableCurrencyTextColor;

	UPROPERTY(Transient)
	FString _itemId;

	UPROPERTY(Transient)
	ECurrencyType _currencyType;

	UPROPERTY(Transient)
	bool _hasDiscountPercentage;

public:
	UUMGCustomizationItemPriceWidget();
};

FORCEINLINE uint32 GetTypeHash(const UUMGCustomizationItemPriceWidget) { return 0; }
