#pragma once

#include "CoreMinimal.h"
#include "ActorPairQueryHeightRange.h"
#include "Components/ActorComponent.h"
#include "TunableStat.h"
#include "RaycastProperties.h"
#include "K33TurretKillerAttackComponent.generated.h"

UCLASS(meta=(BlueprintSpawnableComponent))
class UK33TurretKillerAttackComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(Replicated)
	bool _isAttacking;

	UPROPERTY(EditDefaultsOnly)
	TArray<FRaycastProperties> _bipedRaycastProperties;

	UPROPERTY(EditDefaultsOnly)
	TArray<FRaycastProperties> _quadrupedRaycastProperties;

	UPROPERTY(EditDefaultsOnly)
	FTunableStat _killerDetectionRadius;

	UPROPERTY(EditDefaultsOnly)
	FActorPairQueryHeightRange _killerDetectionHeightRange;

	UPROPERTY(EditDefaultsOnly)
	float _sphereTraceRadius;

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UK33TurretKillerAttackComponent();
};

FORCEINLINE uint32 GetTypeHash(const UK33TurretKillerAttackComponent) { return 0; }
