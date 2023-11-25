#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Templates/SubclassOf.h"
#include "RewardWrapperViewData.h"
#include "CoreRewardWrapperWidget.generated.h"

class UCoreCharacterRewardWidget;
class UCoreCustomizationRewardWidget;
class USizeBox;
class UPanelWidget;
class UCoreCurrencyProgressionRewardWidget;
class UScaleBox;
class UCoreRewardWidget;

UCLASS(EditInlineNew)
class DBDUIVIEWSCORE_API UCoreRewardWrapperWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, NoClear)
	TSubclassOf<UCoreCharacterRewardWidget> CharacterRewardWidget;

	UPROPERTY(EditAnywhere, NoClear)
	TSubclassOf<UCoreCurrencyProgressionRewardWidget> CurrencyProgressionRewardWidget;

	UPROPERTY(EditAnywhere, NoClear)
	TSubclassOf<UCoreCustomizationRewardWidget> CustomizationRewardWidget;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UPanelWidget* RewardContainer;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	USizeBox* SizeBox;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UScaleBox* ScaleBox;

private:
	UPROPERTY(Transient, Export)
	UCoreRewardWidget* _rewardWidget;

public:
	UFUNCTION(BlueprintCallable)
	void SetScaleUserSpecified(float scale);

	UFUNCTION(BlueprintCallable)
	void SetScaleToFit(float size);

	UFUNCTION(BlueprintCallable)
	void SetIsLocked(bool isLocked, bool playAnimation);

	UFUNCTION(BlueprintCallable)
	void SetIsClickable(bool isClickable);

	UFUNCTION(BlueprintCallable)
	void SetData(const FRewardWrapperViewData& viewData);

	UFUNCTION(BlueprintCallable)
	UCoreRewardWidget* GetRewardWidget();

	UFUNCTION(BlueprintCallable)
	void ClearData();

public:
	UCoreRewardWrapperWidget();
};

FORCEINLINE uint32 GetTypeHash(const UCoreRewardWrapperWidget) { return 0; }
