#pragma once

#include "CoreMinimal.h"
#include "UMGBaseButtonWidget.h"
#include "UMGLandingPageButtonWidget.generated.h"

class UCanvasPanel;
class URichTextBlock;
class UTextBlock;
class UImage;

UCLASS(Abstract, EditInlineNew)
class UUMGLandingPageButtonWidget : public UUMGBaseButtonWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCanvasPanel* BigTag;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCanvasPanel* SmallTag;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* TagText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	URichTextBlock* BannerTitleText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* BannerImage;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* TitleColorBg;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* BorderColor;

public:
	UUMGLandingPageButtonWidget();
};

FORCEINLINE uint32 GetTypeHash(const UUMGLandingPageButtonWidget) { return 0; }
