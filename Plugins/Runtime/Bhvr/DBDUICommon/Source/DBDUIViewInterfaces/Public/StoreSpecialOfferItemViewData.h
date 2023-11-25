#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StoreItemViewData.h"
#include "StoreSpecialOfferItemViewData.generated.h"

UCLASS()
class DBDUIVIEWINTERFACES_API UStoreSpecialOfferItemViewData : public UStoreItemViewData
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Transient)
	FDateTime SpecialOfferEndTime;

	UPROPERTY(BlueprintReadOnly, Transient)
	UStoreItemViewData* Item;

public:
	UStoreSpecialOfferItemViewData();
};

FORCEINLINE uint32 GetTypeHash(const UStoreSpecialOfferItemViewData) { return 0; }
