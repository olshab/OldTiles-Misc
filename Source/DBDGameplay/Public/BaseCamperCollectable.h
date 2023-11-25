#pragma once

#include "CoreMinimal.h"
#include "Collectable.h"
#include "BaseCamperCollectable.generated.h"

class USurvivorCollectableOutlineUpdateStrategy;
class UDropItemInteraction;
class USpherePlayerOverlapComponent;
class UDBDOutlineComponent;
class UInteractor;
class UCollectItemInteraction;
class UMaterialHelper;
class USphereComponent;

UCLASS()
class DBDGAMEPLAY_API ABaseCamperCollectable : public ACollectable
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta=(BindWidget))
	USpherePlayerOverlapComponent* _interactable;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UInteractor* _collectableInteractor;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UDropItemInteraction* _dropInteraction;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UCollectItemInteraction* _collectInteraction;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(BindWidget))
	USphereComponent* _infectablePrimitive;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UDBDOutlineComponent* _outlineComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UMaterialHelper* _materialHelper;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(BindWidget))
	USurvivorCollectableOutlineUpdateStrategy* _survivorCollectableOutlineUpdateStrategy;

public:
	ABaseCamperCollectable();
};

FORCEINLINE uint32 GetTypeHash(const ABaseCamperCollectable) { return 0; }
