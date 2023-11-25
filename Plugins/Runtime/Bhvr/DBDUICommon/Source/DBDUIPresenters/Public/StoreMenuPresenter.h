#pragma once

#include "CoreMinimal.h"
#include "EStoreMenuState.h"
#include "Presenter.h"
#include "Templates/SubclassOf.h"
#include "StoreMenuPresenter.generated.h"

class UStoreCollectionsSubPresenter;
class UShopManager;
class UUserWidget;
class UStoreCharactersSubPresenter;
class UStoreSubPresenter;
class UStoreFeaturedSubPresenter;
class UStoreBundlesSubPresenter;

UCLASS(EditInlineNew)
class DBDUIPRESENTERS_API UStoreMenuPresenter : public UPresenter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> StoreMenuWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName DisplayStandName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float InStoreCameraTransitionDurationSeconds;

private:
	UPROPERTY(Transient)
	UStoreFeaturedSubPresenter* _storeFeaturedSubPresenter;

	UPROPERTY(Transient)
	UStoreCollectionsSubPresenter* _storeCollectionsSubPresenter;

	UPROPERTY(Transient)
	UStoreBundlesSubPresenter* _storeBundlesSubPresenter;

	UPROPERTY(Transient)
	UStoreCharactersSubPresenter* _storeCharactersSubPresenter;

	UPROPERTY(Transient)
	UStoreSubPresenter* _activeSubPresenter;

	UPROPERTY(Transient)
	UShopManager* _shopManager;

private:
	UFUNCTION()
	void OpenRedeemCodePopup();

	UFUNCTION()
	void OnMenuTabSelected(EStoreMenuState menuState, bool alreadySelected);

	UFUNCTION()
	void OnBackAction();

	UFUNCTION()
	void OnAllStoreDataLoadComplete(bool success);

public:
	UStoreMenuPresenter();
};

FORCEINLINE uint32 GetTypeHash(const UStoreMenuPresenter) { return 0; }
