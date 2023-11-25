#pragma once

#include "CoreMinimal.h"
#include "Collectable.h"
#include "AkObservedPlayerSoundLoop.h"
#include "ELamentConfigurationState.h"
#include "EAttachToSocketNameEnum.h"
#include "Templates/SubclassOf.h"
#include "GameplayTagContainer.h"
#include "DBDTunableRowHandle.h"
#include "GameEventData.h"
#include "UObject/NoExportTypes.h"
#include "Engine/EngineTypes.h"
#include "LamentConfiguration.generated.h"

class USpherePlayerOverlapComponent;
class ULamentConfigurationSpawnStrategy;
class UK25CollectLamentConfigurationInteraction;
class UDBDOutlineComponent;
class UInteractor;
class UMaterialHelper;
class UAnimationMontageSlave;
class ULamentConfigurationOutlineStrategy;
class ULamentConfigurationChainHuntComponent;
class UMontagePlayer;
class AAnimationFollowerActor;
class AK25LamentConfigurationTeleportIndicator;
class ACamperPlayer;
class UBoxComponent;
class ASlasherPlayer;
class UPrimitiveComponent;
class AActor;

UCLASS()
class ALamentConfiguration : public ACollectable
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta=(BindWidget))
	USpherePlayerOverlapComponent* _interactable;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UInteractor* _collectableInteractor;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UK25CollectLamentConfigurationInteraction* _survivorCollectItemInteraction;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UK25CollectLamentConfigurationInteraction* _killerCollectItemInteraction;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UDBDOutlineComponent* _outlineComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UMaterialHelper* _materialHelper;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	ULamentConfigurationOutlineStrategy* _outlineStrategy;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	ULamentConfigurationSpawnStrategy* _spawnStrategy;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	ULamentConfigurationChainHuntComponent* _chainHuntComponent;

	UPROPERTY(EditAnywhere)
	float _dotProductMinValue;

	UPROPERTY(EditDefaultsOnly)
	EAttachToSocketNameEnum _survivorAttachmentSocket;

	UPROPERTY(EditDefaultsOnly)
	EAttachToSocketNameEnum _killerAttachmentSocket;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
	UAnimationMontageSlave* _montageFollower;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
	UMontagePlayer* _montagePlayer;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AAnimationFollowerActor> _chainAnimationActorClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AK25LamentConfigurationTeleportIndicator> _lamentConfigurationTeleportIndicatorClass;

	UPROPERTY(EditDefaultsOnly)
	FName _chainAnimationFollowerAttachmentSocketName;

	UPROPERTY(EditDefaultsOnly)
	FAkObservedPlayerSoundLoop _possessionSoundLoop;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FDBDTunableRowHandle _respawnTimeAfterLamentConfigurationSolved;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FDBDTunableRowHandle _respawnTimeAfterKillerPickUp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FDBDTunableRowHandle _respawnTimeAfterSurvivorFreeBySelf;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FDBDTunableRowHandle _respawnTimeAfterSurvivorFreeByAttack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FDBDTunableRowHandle _numberChainsToLaunchUponKillerPickUpLamentConfiguration;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FDBDTunableRowHandle _hostageInteractionTime;

private:
	UPROPERTY(Transient)
	ELamentConfigurationState _localLamentConfigurationState;

	UPROPERTY(ReplicatedUsing=OnRep_LamentConfigurationState, Transient)
	ELamentConfigurationState _lamentconfigurationState;

	UPROPERTY(Transient)
	AAnimationFollowerActor* _chainAnimationActor;

	UPROPERTY(ReplicatedUsing=OnRep_SurvivorHeldHostage, Transient)
	ACamperPlayer* _survivorHeldHostage;

	UPROPERTY(EditDefaultsOnly, Export)
	UBoxComponent* _standingOnLamentConfigurationCollisionChecker;

	UPROPERTY(EditDefaultsOnly)
	float _timeAllowedToStandOnCubeBeforeTeleport;

	UPROPERTY(EditDefaultsOnly)
	float _solvedLamentConfigurationDropDistanceToCollectorCentimeters;

	UPROPERTY(EditDefaultsOnly)
	float _failedLamentConfigurationSolveDropDistanceToCollectorCentimeters;

	UPROPERTY(Replicated)
	bool _solved;

	UPROPERTY(Replicated)
	bool _releasedByAttack;

	UPROPERTY(Transient)
	AK25LamentConfigurationTeleportIndicator* _lamentConfigurationTeleportIndicator;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void TriggerKillerPickUpSFX(const TArray<ACamperPlayer*>& affectedSurvivors);

private:
	UFUNCTION()
	void OnRep_SurvivorHeldHostage(ACamperPlayer* oldSurvivorHeldHostage);

	UFUNCTION()
	void OnRep_LamentConfigurationState();

	UFUNCTION()
	void OnCamperEscaped(FGameplayTag gameEventType, const FGameEventData& gameEventData);

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_TriggerSolvedSFX();

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_TriggerKillerPickUpSFX(const TArray<ACamperPlayer*>& affectedSurvivors);

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_DownedSurvivorHoldingLamentConfiguration(ACamperPlayer* survivor);

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_CorrectLamentConfigurationPosition(const FVector& newPosition);

public:
	UFUNCTION(BlueprintPure)
	float GetChainHuntProgressPercentage() const;

protected:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void Cosmetic_TriggerSurvivorPickUpSFX();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void Cosmetic_TriggerSpawnedSFX();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void Cosmetic_TriggerSolvedSFX();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void Cosmetic_TriggerRespawnDuringChainHuntSFX();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void Cosmetic_TriggerOnSurvivorEscapedWithLamentConfigurationSFX();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void Cosmetic_TriggerDisappearsSFX();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void Cosmetic_OnKillerDownedSurvivorHoldingLamentConfiguration(ASlasherPlayer* killer, ACamperPlayer* survivorDowned);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void Cosmetic_OnHoldingSurvivorHostageStart(float hostageDuration);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void Cosmetic_OnHoldingSurvivorHostageEnd(bool hasEndedThroughKillerAttack);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void Cosmetic_OnChainHuntStartedEffects();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void Cosmetic_OnChainHuntEndedEffects();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void Cosmetic_OnChainHuntChargeStart(float chargeTime);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void Cosmetic_OnChainHuntChargeEnd();

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void Cosmetic_EndSolvingCube(bool hasBeenSolved);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void Cosmetic_BeginSolvingCube();

	UFUNCTION()
	void Authority_RespawnLamentConfiguration(bool triggerChainHuntUponSpawning);

private:
	UFUNCTION()
	void Authority_OnSurvivorHitByControlledProjectile(FGameplayTag gameEventType, const FGameEventData& gameEventData);

	UFUNCTION()
	void Authority_OnOverlapEnd(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex);

	UFUNCTION()
	void Authority_OnOverlapBegin(UPrimitiveComponent* overlappedComponent, AActor* other, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult);

	UFUNCTION()
	void Authority_OnIntroCompletedOrLevelReadyToPlay();

	UFUNCTION()
	void Authority_OnGameEnded(FGameplayTag gameEventType, const FGameEventData& gameEventData);

	UFUNCTION()
	void Authority_OnEndGameOver(FGameplayTag gameEventType, const FGameEventData& gameEventData);

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	ALamentConfiguration();
};

FORCEINLINE uint32 GetTypeHash(const ALamentConfiguration) { return 0; }
