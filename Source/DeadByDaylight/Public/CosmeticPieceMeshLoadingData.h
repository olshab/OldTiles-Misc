#pragma once

#include "CoreMinimal.h"
#include "CosmeticPieceMeshLoadingData.generated.h"

class USkeletalMesh;

USTRUCT(BlueprintType)
struct FCosmeticPieceMeshLoadingData
{
	GENERATED_BODY()

public:
	UPROPERTY(Transient)
	USkeletalMesh* SkeletalMesh;

public:
	DEADBYDAYLIGHT_API FCosmeticPieceMeshLoadingData();
};

FORCEINLINE uint32 GetTypeHash(const FCosmeticPieceMeshLoadingData) { return 0; }
