#pragma once

#include "CoreMinimal.h"
#include "UMGBaseButtonWidget.h"
#include "Styling/SlateBrush.h"
#include "EFriendTypeButton.h"
#include "UMGFriendButtonWidget.generated.h"

class UCanvasPanel;
class UTextBlock;
class UImage;

UCLASS(Abstract, EditInlineNew)
class DBDUIVIEWSMOBILE_API UUMGFriendButtonWidget : public UUMGBaseButtonWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta=(BindWidget))
	UCanvasPanel* InteractableButtonStatePanel;

	UPROPERTY(meta=(BindWidget))
	UCanvasPanel* NonInteractableButtonStatePanel;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* NonInteractableExplanationText;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* NonInteractableActionText;

	UPROPERTY(Transient)
	bool _isInteractable;

	UPROPERTY(meta=(BindWidget))
	UImage* NonInteractableImage;

	UPROPERTY(EditDefaultsOnly, NoClear)
	TMap<EFriendTypeButton, FSlateBrush> _nonInteractableImages;

public:
	UUMGFriendButtonWidget();
};

FORCEINLINE uint32 GetTypeHash(const UUMGFriendButtonWidget) { return 0; }
