#pragma once

#include "CoreMinimal.h"
#include "MobileBaseUserWidget.h"
#include "UMGPromoPackSelectedItemWidget.generated.h"

class UNamedSlot;
class UImage;
class UUMGHtmlRichText;
class UUMGPromoPackItemWidget;
class UTextBlock;
class UScrollBox;

UCLASS(Abstract, EditInlineNew)
class UUMGPromoPackSelectedItemWidget : public UMobileBaseUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGHtmlRichText* ItemDescription;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* ItemTypeIcon;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* ItemName;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* ItemSubtitle;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UNamedSlot* SelectedItemSlot;

	UPROPERTY(Transient, meta=(BindWidget))
	UUMGPromoPackItemWidget* SelectedItem;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UScrollBox* ScrollBox;

public:
	UUMGPromoPackSelectedItemWidget();
};

FORCEINLINE uint32 GetTypeHash(const UUMGPromoPackSelectedItemWidget) { return 0; }
