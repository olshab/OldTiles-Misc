#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateBrush.h"
#include "MobileBaseUserWidget.h"
#include "UMGAtlantaMatchConfigScreen.generated.h"

class UUMGBaseButtonWidget;
class UHorizontalBox;
class UUMGAtlantaMatchConfigPageScroll;
class UVerticalBox;
class UTextBlock;
class UMatchConfigTabsDataAsset;

UCLASS(Abstract, EditInlineNew)
class DBDUIVIEWSMOBILE_API UUMGAtlantaMatchConfigScreen : public UMobileBaseUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGAtlantaMatchConfigPageScroll* MatchConfigPageScroll;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UHorizontalBox* TabsBox;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UVerticalBox* BotsTabsBox;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGBaseButtonWidget* BackButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* MatchConfigTitle;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* InventoryTitle;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* SelectedTabTitle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMatchConfigTabsDataAsset* TabsDataAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSlateBrush SmallTabSeparation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSlateBrush BigTabSeparation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TabsVerticalPadding;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TabsHorizontalPadding;

protected:
	UFUNCTION()
	void HandleBackButtonClicked();

public:
	UUMGAtlantaMatchConfigScreen();
};

FORCEINLINE uint32 GetTypeHash(const UUMGAtlantaMatchConfigScreen) { return 0; }
