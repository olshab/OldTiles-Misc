#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AITrackedEnemyData.h"
#include "DBDAIEnemyTrackerComponent.generated.h"

class UAIEnemyTracker;
class ACharacter;

UCLASS(BlueprintType, meta=(BlueprintSpawnableComponent))
class DBDBOTS_API UDBDAIEnemyTrackerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Export)
	UAIEnemyTracker* EnemyTracker;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float UpdateInterval;

private:
	UPROPERTY(Transient)
	TMap<TWeakObjectPtr<ACharacter>, FAITrackedEnemyData> _trackedEnemiesData;

public:
	UDBDAIEnemyTrackerComponent();
};

FORCEINLINE uint32 GetTypeHash(const UDBDAIEnemyTrackerComponent) { return 0; }
