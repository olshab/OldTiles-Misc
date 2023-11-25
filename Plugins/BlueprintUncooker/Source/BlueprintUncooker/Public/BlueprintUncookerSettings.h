#pragma once
#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "BlueprintUncookerSettings.generated.h"

UCLASS(Config=Editor, DefaultConfig, meta=(DisplayName="Blueprint Uncooker Settings"))
class BLUEPRINTUNCOOKER_API UBlueprintUncookerSettings : public UDeveloperSettings 
{
	GENERATED_BODY()

public:
	FORCEINLINE static const UBlueprintUncookerSettings* Get() 
	{
		return GetDefault<UBlueprintUncookerSettings>();
	};

public:
	UPROPERTY(EditAnywhere, Config, Category="Blueprint Uncooker")
	FString DumpsDirectory;  /** "C:\Users\Oleg\Desktop\dumper" */

	UPROPERTY(EditAnywhere, Config)
	FString AssetPathForImportedMeshes;  /** "/Game/NewTiles/Meshes/buffer" */

	UPROPERTY(EditAnywhere, Config)
	FString AssetPathForCreatedMaterialInstances;  /** "/Game/NewTiles/Materials/buffer" */

	UPROPERTY(EditAnywhere, Config)
	FString ParentMaterialForCreatedMaterialInstances;  /** "/Game/Materials/Masters/MI_Structures_V2" */

	UPROPERTY(EditAnywhere, Config)
	FString AssetPathToSearchForMaterialInstances;  /** "/Game/NewTiles" */

	UPROPERTY(EditAnywhere, Config)
	FString AssetPathForImportedTextures;  /** "/Game/NewTiles/Textures/buffer" */

	UPROPERTY(EditAnywhere, Config)
	FString DefaultDiffuseTexturePackageName;  /** "/Game/NewTiles/Textures/00-Common/Diffuse" */

	UPROPERTY(EditAnywhere, Config)
	FString DefaultNormalTexturePackageName;  /** "/Game/NewTiles/Textures/00-Common/FlatNormal" */

	UPROPERTY(EditAnywhere, Config)
	FString DefaultORMTexturePackageName;  /** "/Game/NewTiles/Textures/00-Common/Yellow" */
};
