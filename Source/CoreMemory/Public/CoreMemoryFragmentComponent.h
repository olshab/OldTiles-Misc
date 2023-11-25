#pragma once

#include "CoreMinimal.h"
#include "DBDTunableRowHandle.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "Engine/EngineTypes.h"
#include "CoreMemoryFragmentComponent.generated.h"

class ACoreMemoryChallengePlayerSpecificController;
class UPrimitiveComponent;
class ADBDPlayer;
class AActor;

UCLASS(meta=(BlueprintSpawnableComponent))
class UCoreMemoryFragmentComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(ReplicatedUsing=OnRep_OwningPlayer, Transient)
	ADBDPlayer* _owningPlayer;

	UPROPERTY(Replicated, Transient)
	ACoreMemoryChallengePlayerSpecificController* _controller;

	UPROPERTY(EditDefaultsOnly)
	float _lineOfSightTimerRate;

	UPROPERTY(ReplicatedUsing=OnRep_WasTriggered)
	bool _wasTriggered;

	UPROPERTY(EditAnywhere)
	FGameplayTagContainer _killerPreventingTags;

	UPROPERTY(EditAnywhere)
	FGameplayTagContainer _camperPreventingTags;

	UPROPERTY(ReplicatedUsing=OnRep_IsDespawned)
	bool _isDespawned;

	UPROPERTY(EditDefaultsOnly)
	FDBDTunableRowHandle _authority_DisableCollisionDetectionAtSpawn;

private:
	UFUNCTION(Server, Reliable)
	void Server_OnFragmentCollected();

	UFUNCTION()
	void OnRep_WasTriggered();

	UFUNCTION()
	void OnRep_OwningPlayer();

	UFUNCTION()
	void OnRep_IsDespawned();

	UFUNCTION()
	void OnLocallyObservedChanged(bool isLocallyObserved);

	UFUNCTION()
	void OnCollectZoneEntered(UPrimitiveComponent* hitComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult);

public:
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_FragmentDespawnCountdown(float floatVal) const;

private:
	UFUNCTION()
	void Authority_OnTriggerZoneExited(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex);

	UFUNCTION()
	void Authority_OnTriggerZoneEntered(UPrimitiveComponent* hitComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult);

	UFUNCTION()
	void Authority_CheckLineOfSight();

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UCoreMemoryFragmentComponent();
};

FORCEINLINE uint32 GetTypeHash(const UCoreMemoryFragmentComponent) { return 0; }
