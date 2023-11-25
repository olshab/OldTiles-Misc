#pragma once

#include "CoreMinimal.h"
#include "UObject/SoftObjectPtr.h"
#include "GameFramework/Actor.h"
#include "OriginalMaterials.h"
#include "UObject/NoExportTypes.h"
#include "FadeManager.generated.h"

class UDataTable;
class UMaterialInterface;
class UMeshComponent;

UCLASS()
class DEADBYDAYLIGHT_API AFadeManager : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(Transient, Export)
	TSet<UMeshComponent*> _meshComponents;

	UPROPERTY(Transient)
	UDataTable* _fadeMaterials;

	UPROPERTY(Transient)
	TMap<TSoftObjectPtr<UMaterialInterface>, TSoftObjectPtr<UMaterialInterface>> _originalToFade;

	UPROPERTY(Transient)
	TMap<TSoftObjectPtr<UMaterialInterface>, TSoftObjectPtr<UMaterialInterface>> _fadeToOriginal;

	UPROPERTY(Transient)
	TArray<FOriginalMaterials> _fadedMeshes;

public:
	UFUNCTION(BlueprintCallable)
	void RemoveFadeMaterials();

	UFUNCTION(BlueprintCallable)
	void FadeAt(FVector CameraLocation);

	UFUNCTION(Exec)
	void DBD_ActivateFadeCamera(bool isActivated);

public:
	AFadeManager();
};

FORCEINLINE uint32 GetTypeHash(const AFadeManager) { return 0; }
