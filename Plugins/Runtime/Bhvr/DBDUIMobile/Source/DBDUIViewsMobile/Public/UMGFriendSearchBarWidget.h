#pragma once

#include "CoreMinimal.h"
#include "MobileBaseUserWidget.h"
#include "UMGFriendSearchBarWidget.generated.h"

class UUMGBaseButtonWidget;
class UEditableTextBox;

UCLASS(Abstract, EditInlineNew)
class UUMGFriendSearchBarWidget : public UMobileBaseUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta=(BindWidget))
	UEditableTextBox* InputTextField;

	UPROPERTY(meta=(BindWidget))
	UUMGBaseButtonWidget* SearchButton;

private:
	UFUNCTION()
	void HandleTextInputChanged(const FText& textInput);

	UFUNCTION()
	void HandleSearchButtonClicked();

public:
	UUMGFriendSearchBarWidget();
};

FORCEINLINE uint32 GetTypeHash(const UUMGFriendSearchBarWidget) { return 0; }
