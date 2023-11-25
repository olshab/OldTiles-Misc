#pragma once

#include "CoreMinimal.h"
#include "Collectable.h"
#include "Templates/SubclassOf.h"
#include "DBDTunableRowHandle.h"
#include "K32Power.generated.h"

class AK32KillerPodVisionController;
class UK32PowerChargePresentationPowerFadeComponent;
class UK32AntiCampZoneIdentifierComponent;
class UInteractor;
class UBoxPlayerOverlapComponent;
class AK32KillerPodTargetIndicator;
class UK32PowerChargePresentationItemProgressComponent;
class AK32KillerPodSpawningIndicator;
class UStatusEffect;
class UAimingCrosshairComponent;
class ACamperPlayer;
class UChargeableComponent;
class UAuthoritativeActorPoolComponent;
class UK32EmpScoreComponent;

UCLASS()
class AK32Power : public ACollectable
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
	UInteractor* _interactor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
	UBoxPlayerOverlapComponent* _interactionVolume;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
	UK32PowerChargePresentationItemProgressComponent* _powerChargePresentationItemProgressComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
	UK32PowerChargePresentationPowerFadeComponent* _powerChargePresentationPowerFadeComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UK32AntiCampZoneIdentifierComponent* _antiCampZoneIdentifierComponent;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AK32KillerPodVisionController> _killerPodVisionControllerClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AK32KillerPodTargetIndicator> _killerPodTargetIndicatorClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AK32KillerPodSpawningIndicator> _killerPodSpawningIndicatorClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UStatusEffect> _blindnessProtectionStatusEffect;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UStatusEffect> _undetectableWhileInPodsStatusEffect;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UStatusEffect> _overclockStatusEffectClass;

	UPROPERTY(EditDefaultsOnly)
	FDBDTunableRowHandle _addon16RecentlyTeleportedTime;

private:
	UPROPERTY(Replicated, Transient)
	AK32KillerPodVisionController* _killerPodVisionController;

	UPROPERTY(Transient)
	AK32KillerPodTargetIndicator* _killerPodTargetIndicator;

	UPROPERTY(Transient)
	AK32KillerPodSpawningIndicator* _killerPodSpawningIndicator;

	UPROPERTY(Replicated, Transient, Export)
	UAimingCrosshairComponent* _aimingCrosshairComponent;

	UPROPERTY(Transient, Export)
	UChargeableComponent* _killerProjectileSpawnChargeableComponent;

	UPROPERTY(VisibleAnywhere, NoClear, Export)
	UAuthoritativeActorPoolComponent* _empPool;

	UPROPERTY(VisibleAnywhere, NoClear, Export)
	UK32EmpScoreComponent* _empScoreComponent;

	UPROPERTY(Transient)
	ACamperPlayer* _recentlyTeleportedToSurvivor;

	UPROPERTY(EditDefaultsOnly)
	FDBDTunableRowHandle _maxTrackedTimeSinceTeleportToSurvivor;

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	AK32Power();
};

FORCEINLINE uint32 GetTypeHash(const AK32Power) { return 0; }
