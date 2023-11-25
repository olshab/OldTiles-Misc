#pragma once

#include "CoreMinimal.h"
#include "MobileBaseUserWidget.h"
#include "EActionOnFriendType.h"
#include "UMGBaseFriendListContextualMenuWidget.generated.h"

class UUMGFriendButtonWidget;
class UAkAudioEvent;

UCLASS(Abstract, EditInlineNew)
class DBDUIVIEWSMOBILE_API UUMGBaseFriendListContextualMenuWidget : public UMobileBaseUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta=(BindWidget))
	UUMGFriendButtonWidget* InviteToPartyButton;

	UPROPERTY(meta=(BindWidget))
	UUMGFriendButtonWidget* MuteButton;

	UPROPERTY(meta=(BindWidget))
	UUMGFriendButtonWidget* UnmuteButton;

	UPROPERTY(meta=(BindWidget))
	UUMGFriendButtonWidget* RemoveFriendButton;

	UPROPERTY(meta=(BindWidget))
	UUMGFriendButtonWidget* RemovePlayerFromPartyButton;

	UPROPERTY(EditAnywhere)
	UAkAudioEvent* TransitionOutAnimationSound;

protected:
	UFUNCTION(BlueprintCallable)
	void HandleActionTriggered(EActionOnFriendType actionType);

public:
	UUMGBaseFriendListContextualMenuWidget();
};

FORCEINLINE uint32 GetTypeHash(const UUMGBaseFriendListContextualMenuWidget) { return 0; }
