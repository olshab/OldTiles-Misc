#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DBDTableRowBase.h"
#include "StoreCollectionData.generated.h"

USTRUCT(BlueprintType)
struct FStoreCollectionData: public FDBDTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString CollectionId;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	uint8 ReleaseStatus;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText CollectionTitle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText CollectionSubtitle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FDateTime ActiveFrom;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FDateTime ActiveUntil;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 SortOrder;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FSoftObjectPath HeroImage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FSoftObjectPath HeroVideo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FSoftObjectPath> AdditionalImages;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FString> Items;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	uint8 Flags;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FDateTime SpecialStartDate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FDateTime SpecialEndDate;

public:
	DEADBYDAYLIGHT_API FStoreCollectionData();
};

FORCEINLINE uint32 GetTypeHash(const FStoreCollectionData) { return 0; }
