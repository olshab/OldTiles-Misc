#pragma once

#include "CoreMinimal.h"
#include "MobileBaseUserWidget.h"
#include "UObject/SoftObjectPtr.h"
#include "FriendWidgetList.h"
#include "ActionOnFriend.h"
#include "EActionOnFriendType.h"
#include "UMGAtlantaFriendListScreen.generated.h"

class UHorizontalBox;
class UUMGBaseButtonWidget;
class UUMGBaseFriendListContextualMenuWidget;
class UUMGFriendListTabWidget;
class UUMGBaseFriendListElement;
class UUMGSuggestionsListTabWidget;
class UWidgetSwitcher;
class UTextBlock;
class UUMGFriendSearchBarWidget;
class UUMGRequestsListTabWidget;
class UUMGFriendTabButtonWidget;
class UExpandableArea;

UCLASS(Abstract, EditInlineNew)
class UUMGAtlantaFriendListScreen : public UMobileBaseUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta=(BindWidget))
	UWidgetSwitcher* ListSwitcher;

	UPROPERTY(meta=(BindWidget))
	UWidgetSwitcher* SearchResultSwitcher;

	UPROPERTY(meta=(BindWidget))
	UUMGBaseFriendListElement* NonFriendSearchResult;

	UPROPERTY(meta=(BindWidget))
	UUMGBaseFriendListElement* RequestReceivedSearchResult;

	UPROPERTY(meta=(BindWidget))
	UUMGBaseFriendListElement* RequestSentSearchResult;

	UPROPERTY(meta=(BindWidget))
	UUMGBaseFriendListElement* FriendSearchResult;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* SearchFailureText;

	UPROPERTY(meta=(BindWidget))
	UUMGBaseButtonWidget* CloseButton;

	UPROPERTY(meta=(BindWidget))
	UUMGFriendSearchBarWidget* SearchBar;

	UPROPERTY(meta=(BindWidget))
	UHorizontalBox* ButtonTabContainer;

	UPROPERTY(meta=(BindWidget))
	UUMGFriendListTabWidget* FriendListTabWidget;

	UPROPERTY(meta=(BindWidget))
	UUMGSuggestionsListTabWidget* SuggestionListTabWidget;

	UPROPERTY(meta=(BindWidget))
	UUMGRequestsListTabWidget* RequestListTabWidget;

	UPROPERTY(meta=(BindWidget))
	UUMGFriendTabButtonWidget* FriendsTabButton;

	UPROPERTY(meta=(BindWidget))
	UUMGFriendTabButtonWidget* SuggestionsTabButton;

	UPROPERTY(meta=(BindWidget))
	UUMGFriendTabButtonWidget* RequestsTabButton;

	UPROPERTY(Transient, meta=(BindWidget))
	UUMGBaseFriendListContextualMenuWidget* CurrentContextualMenuWidget;

	UPROPERTY(EditInstanceOnly)
	TSoftClassPtr<UUMGBaseFriendListElement> FriendWidget;

	UPROPERTY(EditInstanceOnly)
	TSoftClassPtr<UUMGBaseFriendListElement> RequestSentWidget;

	UPROPERTY(EditInstanceOnly)
	TSoftClassPtr<UUMGBaseFriendListElement> FriendRequestReceivedWidget;

	UPROPERTY(EditInstanceOnly)
	TSoftClassPtr<UUMGBaseFriendListElement> FriendsSuggestionWidget;

	UPROPERTY(EditInstanceOnly)
	TSoftClassPtr<UUMGBaseFriendListElement> FriendsSuggestion;

	UPROPERTY(EditInstanceOnly)
	TSoftClassPtr<UUMGBaseFriendListElement> FriendPartyInviteWidgetClass;

	UPROPERTY(EditInstanceOnly)
	TSoftClassPtr<UUMGBaseFriendListContextualMenuWidget> ContextualMenuInvite;

	UPROPERTY(EditInstanceOnly)
	TSoftClassPtr<UUMGBaseFriendListContextualMenuWidget> ContextualMenuConfirmDeclineAction;

private:
	UPROPERTY()
	TMap<FString, FFriendWidgetList> _existingFriendListWidgets;

	UPROPERTY(Export)
	TMap<FString, UUMGBaseFriendListElement*> _existingFriendInvitePartyWidget;

private:
	UFUNCTION()
	void VerifyReceivedFriendRequestFocus(UExpandableArea* expandableArea, bool bIsExpanded);

	UFUNCTION()
	void OnFinishedOutAnimation();

	UFUNCTION()
	void HandleTabButtonClicked(uint8 tabIndex);

	UFUNCTION()
	void HandleSearchInputChanged(const FText& inputText);

	UFUNCTION()
	void HandleSearchButtonClicked();

	UFUNCTION()
	void HandleOnActionOnFriend(const FActionOnFriend& actionOnFriend);

	UFUNCTION()
	void HandleContextualMenuAction(EActionOnFriendType action);

	UFUNCTION()
	void HandleCloseButtonClicked();

public:
	UUMGAtlantaFriendListScreen();
};

FORCEINLINE uint32 GetTypeHash(const UUMGAtlantaFriendListScreen) { return 0; }
