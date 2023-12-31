#pragma once

#include "CoreMinimal.h"
#include "DBDTableRowBase.h"
#include "UObject/SoftObjectPtr.h"
#include "MaterialMapForFade.generated.h"

class UMaterialInterface;

USTRUCT(BlueprintType)
struct FMaterialMapForFade: public FDBDTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UMaterialInterface> SrcMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UMaterialInterface> DstMaterial;

public:
	DEADBYDAYLIGHT_API FMaterialMapForFade();
};

FORCEINLINE uint32 GetTypeHash(const FMaterialMapForFade) { return 0; }
