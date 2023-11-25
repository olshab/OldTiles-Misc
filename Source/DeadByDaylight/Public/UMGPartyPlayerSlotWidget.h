#pragma once

#include "CoreMinimal.h"
#include "MobileBaseUserWidget.h"
#include "EPartyPlayerSlotWidgetState.h"
#include "Fonts/SlateFontInfo.h"
#include "UMGPartyPlayerSlotWidget.generated.h"

class UCanvasPanel;
class UUMGBaseButtonWidget;
class UTextBlock;
class UWidgetSwitcher;
class UImage;
class UWidget;

UCLASS(Abstract, EditInlineNew)
class DEADBYDAYLIGHT_API UUMGPartyPlayerSlotWidget : public UMobileBaseUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* PlayerName;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* AdditionalInformationText;

	UPROPERTY(meta=(BindWidget))
	UImage* FriendIcon;

	UPROPERTY(meta=(BindWidget))
	UUMGBaseButtonWidget* KickPlayerButton;

	UPROPERTY(EditDefaultsOnly)
	FSlateFontInfo CharacterNameStyle;

	UPROPERTY(EditDefaultsOnly)
	FSlateFontInfo PlayerInMatchStyle;

	UPROPERTY(EditDefaultsOnly)
	float PlayerInMatchOpacity;

	UPROPERTY(EditDefaultsOnly)
	float PlayerInLobbyOpacity;

	UPROPERTY(meta=(BindWidget))
	UWidget* PlayerInformationContainer;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCanvasPanel* ReadyIconsCanvas;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCanvasPanel* RequestRoleIconsCanvas;

	UPROPERTY(meta=(BindWidget))
	UWidgetSwitcher* RoleSwitcher;

	UPROPERTY(meta=(BindWidget))
	UImage* LeaderIcon;

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SetVisualsFromState(EPartyPlayerSlotWidgetState widgetState);

private:
	UFUNCTION()
	void HandleKickPlayerButtonEvent();

public:
	UUMGPartyPlayerSlotWidget();
};

FORCEINLINE uint32 GetTypeHash(const UUMGPartyPlayerSlotWidget) { return 0; }
