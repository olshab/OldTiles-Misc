#pragma once

#include "CoreMinimal.h"
#include "UMGBaseButtonWidget.h"
#include "UMGBaseTabButtonWidget.generated.h"

class URichTextBlock;
class UCanvasPanel;
class UTextBlock;
class UImage;

UCLASS(Abstract, EditInlineNew)
class DBDUIVIEWSMOBILE_API UUMGBaseTabButtonWidget : public UUMGBaseButtonWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta=(BindWidget))
	URichTextBlock* TabText;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* NotificationCountText;

	UPROPERTY(meta=(BindWidget))
	UCanvasPanel* NotificationPanel;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* TabButtonSelected;

	UPROPERTY(EditInstanceOnly)
	uint8 TabIndex;

	UPROPERTY(EditInstanceOnly)
	FText TitleOfTab;

private:
	UPROPERTY(Transient)
	FString _tabTextParameter;

public:
	UUMGBaseTabButtonWidget();
};

FORCEINLINE uint32 GetTypeHash(const UUMGBaseTabButtonWidget) { return 0; }
