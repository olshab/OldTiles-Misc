#pragma once

#include "CoreMinimal.h"
#include "UMGFriendBaseTabListWidget.h"
#include "UMGFriendListTabWidget.generated.h"

class UUMGExpandableListWidget;

UCLASS(Abstract, EditInlineNew)
class DBDUIVIEWSMOBILE_API UUMGFriendListTabWidget : public UUMGFriendBaseTabListWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta=(BindWidget))
	UUMGExpandableListWidget* SentInviteToParty;

	UPROPERTY(meta=(BindWidget))
	UUMGExpandableListWidget* ConnectedFriendsExpandableList;

	UPROPERTY(meta=(BindWidget))
	UUMGExpandableListWidget* DisconnectedFriendsExpandableList;

public:
	UUMGFriendListTabWidget();
};

FORCEINLINE uint32 GetTypeHash(const UUMGFriendListTabWidget) { return 0; }
