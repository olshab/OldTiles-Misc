#pragma once

#include "CoreMinimal.h"
#include "CoreBaseUserWidget.h"
#include "PriceTagViewData.h"
#include "CustomizationItemOriginViewData.h"
#include "CustomizationItemOriginWidget.generated.h"

class UDBDImage;
class UCoreCurrencySwitcherWidget;
class UDBDRichTextBlock;
class UCoreInputSwitcherWidget;

UCLASS(EditInlineNew)
class UCustomizationItemOriginWidget : public UCoreBaseUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDRichTextBlock* InstructionText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDImage* InstructionImage;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDRichTextBlock* UnlockTitle;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDRichTextBlock* UnlockSubtitle;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCoreCurrencySwitcherWidget* CurrencyButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCoreInputSwitcherWidget* ArchivesButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCoreInputSwitcherWidget* StoreButton;

protected:
	UFUNCTION(BlueprintNativeEvent)
	void SetStoreState();

	UFUNCTION(BlueprintCallable)
	void SetState(const FCustomizationItemOriginViewData& viewData);

	UFUNCTION(BlueprintNativeEvent)
	void SetMilestonePointsState(const TArray<FText>& args);

public:
	UFUNCTION(BlueprintCallable)
	void SetInputSwitcherEnabled(UCoreInputSwitcherWidget* inputSwitcher, const bool enabled);

protected:
	UFUNCTION(BlueprintNativeEvent)
	void SetGameplayState(const TArray<FText>& args);

	UFUNCTION(BlueprintNativeEvent)
	void SetDefaultState();

public:
	UFUNCTION(BlueprintCallable)
	void SetData(const FCustomizationItemOriginViewData& viewData);

protected:
	UFUNCTION(BlueprintNativeEvent)
	void SetCurrencyPurchaseState(const FPriceTagViewData& currencyData);

	UFUNCTION(BlueprintNativeEvent)
	void SetArchivesState(const TArray<FText>& args);

	UFUNCTION()
	void OnButtonClick();

public:
	UFUNCTION(BlueprintCallable)
	void DisableStoreButton();

	UFUNCTION(BlueprintCallable)
	void DisableInputs();

	UFUNCTION(BlueprintCallable)
	void DisableCurrencyButton();

	UFUNCTION(BlueprintCallable)
	void DisableArchivesButton();

public:
	UCustomizationItemOriginWidget();
};

FORCEINLINE uint32 GetTypeHash(const UCustomizationItemOriginWidget) { return 0; }
