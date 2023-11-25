#pragma once
#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "BlueprintMergeToolSettings.generated.h"

UCLASS(Config=Editor, DefaultConfig, meta=(DisplayName="Blueprint Merge Settings"))
class BLUEPRINTMERGETOOL_API UBlueprintMergeToolSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	FORCEINLINE static const UBlueprintMergeToolSettings* Get()
	{
		return GetDefault<UBlueprintMergeToolSettings>();
	};

public:
	UPROPERTY(EditAnywhere, Config)
	FString PathToMergingList;

	UPROPERTY(EditAnywhere, Config)
	FString PackagePathToMergedBlueprints;  /** for example, "/Game/MergedTiles/buffer" */

	UPROPERTY(EditAnywhere, Config)
	bool bMakeMeshesTranslucent;

	UPROPERTY(EditAnywhere, Config)
	FString DummyMaterialPackageName;  /** "/Game/Materials/Transparent" */

	UPROPERTY(EditAnywhere, Config)
	bool bReplaceActorSpawners;

	UPROPERTY(EditAnywhere, Config)
	FString ActorSpawnersPackagePath;

	UPROPERTY(EditAnywhere, Config)
	FString CopiedComponentPostfix;  /** "_MERGED" */
};
