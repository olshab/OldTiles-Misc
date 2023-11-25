#pragma once

#include "CoreMinimal.h"
#include "MobileBaseUserWidget.h"
#include "UMGCharacterFreeTicketButton.generated.h"

class UImage;
class UWidgetSwitcher;
class UTextBlock;

UCLASS(EditInlineNew)
class UUMGCharacterFreeTicketButton : public UMobileBaseUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UWidgetSwitcher* ButtonSwitcher;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* FreeTicketLeftSecondsText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* FreeTicketLeftSecondsBG;

public:
	UUMGCharacterFreeTicketButton();
};

FORCEINLINE uint32 GetTypeHash(const UUMGCharacterFreeTicketButton) { return 0; }
