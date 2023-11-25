#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "Templates/SubclassOf.h"
#include "WormholeFatherDeadBody.generated.h"

class UStaticMeshComponent;
class UBoxPlayerOverlapComponent;
class UInteractor;
class UCollectFatherKeyCardInteraction;
class USceneComponent;
class AWormholeFatherKeyCard;
class AActor;

UCLASS()
class AWormholeFatherDeadBody : public AInteractable
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, NoClear, meta=(BindWidget))
	UStaticMeshComponent* _wrmFatherDeadBodyStaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
	USceneComponent* _wrmFatherKeyCardAttachment;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<AWormholeFatherKeyCard> _wrmFatherEasterEggKeyCardStaticClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
	UBoxPlayerOverlapComponent* _wrmFatherKeyCardInteractableZone;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
	UInteractor* _wrmKeyCardFirstCollectionInteractor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
	UCollectFatherKeyCardInteraction* _fatherKeyCardCollectionInteraction;

private:
	UPROPERTY(Replicated)
	AActor* _wrmFatherEasterEggSpawnedKeyCard;

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	AWormholeFatherDeadBody();
};

FORCEINLINE uint32 GetTypeHash(const AWormholeFatherDeadBody) { return 0; }
