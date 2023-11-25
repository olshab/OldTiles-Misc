#pragma once

#include "CoreMinimal.h"
#include "CustomTransformation.h"
#include "UObject/SoftObjectPtr.h"
#include "ItemUIData.generated.h"

class UTexture2D;

USTRUCT(BlueprintType)
struct FItemUIData
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	FText DisplayName;

	UPROPERTY(EditAnywhere)
	FText Description;

	UPROPERTY(EditAnywhere)
	TArray<FString> IconFilePathList;

	UPROPERTY(EditAnywhere)
	TArray<TSoftObjectPtr<UTexture2D>> IconAssetList;

	UPROPERTY(EditAnywhere)
	FCustomTransformation CustomTransformation;

	UPROPERTY(EditAnywhere)
	uint32 PlatformsUnlicensedNameOverride;

	UPROPERTY(EditAnywhere)
	uint32 PlatformsUnlicensedDescriptionOverride;

	UPROPERTY(EditAnywhere)
	uint32 PlatformsForIconUnlicensedFilePathListOverride;

	UPROPERTY(EditAnywhere)
	TArray<FString> IconUnlicensedFilePathListOverride;

	UPROPERTY(EditAnywhere)
	bool LicenseExpirationOverride;

	UPROPERTY(EditAnywhere)
	FText DisplayNameUnlicensedOverride;

	UPROPERTY(EditAnywhere)
	FText DescriptionUnlicensedOverride;

	UPROPERTY(EditAnywhere)
	int32 AssociatedCharacterIndex;

public:
	DEADBYDAYLIGHT_API FItemUIData();
};

FORCEINLINE uint32 GetTypeHash(const FItemUIData) { return 0; }
