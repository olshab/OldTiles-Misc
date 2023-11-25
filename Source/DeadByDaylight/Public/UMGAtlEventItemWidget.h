#pragma once

#include "CoreMinimal.h"
#include "MobileBaseUserWidget.h"
#include "EventItemsContentTypeUIData.h"
#include "UMGAtlEventItemWidget.generated.h"

class UImage;
class UTextBlock;
class UCanvasPanel;

UCLASS(Abstract, EditInlineNew)
class UUMGAtlEventItemWidget : public UMobileBaseUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta=(BindWidget))
	UImage* SquareImageBackground;

	UPROPERTY(meta=(BindWidget))
	UImage* SquareRarityBackground;

	UPROPERTY(meta=(BindWidget))
	UImage* SquareIcon;

	UPROPERTY(meta=(BindWidget))
	UImage* PortraitImageBackground;

	UPROPERTY(meta=(BindWidget))
	UImage* PortraitRarityBackground;

	UPROPERTY(meta=(BindWidget))
	UImage* PortraitIcon;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* NameText;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* QuantityText;

	UPROPERTY(meta=(BindWidget))
	UCanvasPanel* PortraitCanvas;

	UPROPERTY(meta=(BindWidget))
	UCanvasPanel* SquareCanvas;

	UPROPERTY(EditDefaultsOnly)
	TArray<FEventItemsContentTypeUIData> ContentTypeUIData;

public:
	UUMGAtlEventItemWidget();
};

FORCEINLINE uint32 GetTypeHash(const UUMGAtlEventItemWidget) { return 0; }
