#pragma once

#include "CoreMinimal.h"
#include "MobileBaseUserWidget.h"
#include "Styling/SlateColor.h"
#include "EAIDifficultyLevel.h"
#include "UMGPartyBotSlotWidget.generated.h"

class UCanvasPanel;
class UUMGBaseButtonWidget;
class UTextBlock;
class UImage;

UCLASS(Abstract, EditInlineNew)
class DEADBYDAYLIGHT_API UUMGPartyBotSlotWidget : public UMobileBaseUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* RoleText;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* BotDifficultyText;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* CharacterNameText;

	UPROPERTY(meta=(BindWidget))
	UUMGBaseButtonWidget* EditButton;

	UPROPERTY(meta=(BindWidget))
	UImage* EditIcon;

	UPROPERTY(meta=(BindWidget))
	UUMGBaseButtonWidget* InvitePartyButton;

	UPROPERTY(meta=(BindWidget))
	UCanvasPanel* InvitePartyCanvas;

	UPROPERTY(EditDefaultsOnly)
	TMap<EAIDifficultyLevel, FSlateColor> DifficultyColors;

private:
	UFUNCTION()
	void HandleInvitePartyButtonEvent();

	UFUNCTION()
	void HandleEditButtonEvent();

public:
	UUMGPartyBotSlotWidget();
};

FORCEINLINE uint32 GetTypeHash(const UUMGPartyBotSlotWidget) { return 0; }
