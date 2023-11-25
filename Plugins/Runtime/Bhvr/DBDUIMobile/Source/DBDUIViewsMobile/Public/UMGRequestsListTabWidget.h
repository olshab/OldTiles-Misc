#pragma once

#include "CoreMinimal.h"
#include "UMGFriendBaseTabListWidget.h"
#include "UMGRequestsListTabWidget.generated.h"

class UUMGExpandableListWidget;

UCLASS(Abstract, EditInlineNew)
class DBDUIVIEWSMOBILE_API UUMGRequestsListTabWidget : public UUMGFriendBaseTabListWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta=(BindWidget))
	UUMGExpandableListWidget* FriendRequestExpandableList;

	UPROPERTY(meta=(BindWidget))
	UUMGExpandableListWidget* PendingExpandableList;

public:
	UUMGRequestsListTabWidget();
};

FORCEINLINE uint32 GetTypeHash(const UUMGRequestsListTabWidget) { return 0; }
