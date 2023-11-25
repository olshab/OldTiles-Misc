#pragma once

#include "CoreMinimal.h"
#include "MobileBaseUserWidget.h"
#include "PerkSelectionSlotWidget.generated.h"

class UTextBlock;
class UPerkActionButton;
class UUMGHtmlRichText;
class UImage;

UCLASS(Abstract, EditInlineNew)
class UPerkSelectionSlotWidget : public UMobileBaseUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* PerkName;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* TextChoose;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UPerkActionButton* PerkActionButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* SelectedIcon;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGHtmlRichText* DescriptionText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* PictureBackground;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* PicturePerkBackground;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* PictureHighlightFrame;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* PictureTopRightBackground;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* PictureTopRightFrame;

	UPROPERTY(EditDefaultsOnly)
	float HighOpacity;

	UPROPERTY(EditDefaultsOnly)
	float LowOpacity;

	UPROPERTY(EditDefaultsOnly)
	float PerkBackgroundLowOpacity;

	UPROPERTY(EditDefaultsOnly)
	float DescriptionBackgroundLowOpacity;

protected:
	UFUNCTION(BlueprintCallable)
	void OnButtonClicked();

public:
	UPerkSelectionSlotWidget();
};

FORCEINLINE uint32 GetTypeHash(const UPerkSelectionSlotWidget) { return 0; }
