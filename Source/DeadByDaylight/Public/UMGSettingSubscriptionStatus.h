#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UMGSettingSubscriptionStatus.generated.h"

class UWidgetSwitcher;
class UHorizontalBox;
class UOverlay;
class UTextBlock;

UCLASS(Abstract, EditInlineNew)
class UUMGSettingSubscriptionStatus : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	FText SubscriptionStatusText;

	UPROPERTY(EditDefaultsOnly)
	FText StatusText;

	UPROPERTY(EditDefaultsOnly)
	FText InactiveStatusText;

	UPROPERTY(EditDefaultsOnly)
	FText EndText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UWidgetSwitcher* TypeSwitcher;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UHorizontalBox* ActiveWidget;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UOverlay* InactiveWidget;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* TitleText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* DisplayName;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* Status;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* StatusInactive;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* End;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* EndDate;

public:
	UUMGSettingSubscriptionStatus();
};

FORCEINLINE uint32 GetTypeHash(const UUMGSettingSubscriptionStatus) { return 0; }
