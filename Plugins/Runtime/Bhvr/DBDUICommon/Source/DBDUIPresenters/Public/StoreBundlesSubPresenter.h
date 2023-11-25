#pragma once

#include "CoreMinimal.h"
#include "StoreSubPresenter.h"
#include "Templates/SubclassOf.h"
#include "StoreBundlesSubPresenter.generated.h"

class UUserWidget;

UCLASS(BlueprintType)
class DBDUIPRESENTERS_API UStoreBundlesSubPresenter : public UStoreSubPresenter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> StoreBundlesWidgetClass;

public:
	UStoreBundlesSubPresenter();
};

FORCEINLINE uint32 GetTypeHash(const UStoreBundlesSubPresenter) { return 0; }
