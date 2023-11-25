#pragma once

#include "CoreMinimal.h"
#include "AnniversaryPlayerComponentInterface.h"
#include "DBDTunableRowHandle.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "SpeedBasedNetSyncedValue.h"
#include "InvitationPlayerComponent.generated.h"

class UTimerObject;
class ADBDPlayer;
class AActor;

UCLASS(Blueprintable, Abstract, meta=(BlueprintSpawnableComponent))
class ANNIVERSARY2023_API UInvitationPlayerComponent : public UActorComponent, public IAnniversaryPlayerComponentInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, Replicated)
	bool _isInEndGame;

	UPROPERTY(Replicated, Transient)
	FSpeedBasedNetSyncedValue _invitationCharges;

	UPROPERTY(ReplicatedUsing=OnRep_InvitationChargesInt, Transient)
	int32 _invitationChargesInt;

	UPROPERTY(ReplicatedUsing=OnRep_CooldownTimer, Transient, meta=(BindWidget))
	UTimerObject* _cooldownTimer;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTagQuery _particleVFXDeactivateTags;

	UPROPERTY(EditDefaultsOnly)
	FDBDTunableRowHandle _invitationChargeGain;

	UPROPERTY(EditDefaultsOnly)
	FDBDTunableRowHandle _maxNumberOfCharges;

	UPROPERTY(EditDefaultsOnly)
	FDBDTunableRowHandle _chargeRechargeRate;

	UPROPERTY(EditDefaultsOnly)
	FDBDTunableRowHandle _abilityCooldown;

	UPROPERTY(EditDefaultsOnly)
	FDBDTunableRowHandle _chargesForReward;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTagQuery _disablingPlayerTargetComponentTagsQuery;

protected:
	UFUNCTION()
	void OnRep_InvitationChargesInt();

	UFUNCTION()
	void OnRep_CooldownTimer();

	UFUNCTION()
	void OnLevelReadyToPlay();

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_CosmeticOnInvitationInteractionActivate(ADBDPlayer* player, AActor* target);

public:
	UFUNCTION(BlueprintPure)
	float GetInvitationCharges() const;

protected:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void Cosmetic_SetVFXParticlesVisibility(bool isVisible);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void Cosmetic_OnPlayerInChaseStateChanged(bool inChase);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void Cosmetic_OnInvitationInteractionReady(bool isReady);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void Cosmetic_OnInvitationInteractionActivate(ADBDPlayer* abilityCaster, AActor* target);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void Cosmetic_OnInvitationChargesIntChanged(int32 invitationCharge);

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UInvitationPlayerComponent();
};

FORCEINLINE uint32 GetTypeHash(const UInvitationPlayerComponent) { return 0; }
