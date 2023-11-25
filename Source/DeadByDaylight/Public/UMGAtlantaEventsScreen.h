#pragma once

#include "CoreMinimal.h"
#include "MobileBaseUserWidget.h"
#include "Templates/SubclassOf.h"
#include "UMGAtlantaEventsScreen.generated.h"

class UTextBlock;
class UUMGAtlantaEventsDescription;
class UWrapBox;
class UUMGAtlantaEventsTab;

UCLASS(Abstract, EditInlineNew)
class UUMGAtlantaEventsScreen : public UMobileBaseUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* PageTitle;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UWrapBox* WrapBox;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGAtlantaEventsDescription* DescriptionWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUMGAtlantaEventsTab> EventsTabWBPReference;

private:
	UPROPERTY(Export)
	TArray<UUMGAtlantaEventsTab*> _eventsArray;

protected:
	UFUNCTION(BlueprintCallable)
	void HandleEventTabClicked(const FString& id);

	UFUNCTION(BlueprintCallable)
	void BroadcastOnCloseButtonClicked();

private:
	UFUNCTION()
	void BroadcastDeepLinkRequest(const FString& id);

public:
	UUMGAtlantaEventsScreen();
};

FORCEINLINE uint32 GetTypeHash(const UUMGAtlantaEventsScreen) { return 0; }
