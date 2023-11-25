#pragma once

#include "CoreMinimal.h"
#include "EGameplayElementType.h"
#include "UObject/SoftObjectPtr.h"
#include "KillerItemProperty.generated.h"

class UIterativeWeightAdjustmentStrategy;
class AActor;
class UCurveFloat;

USTRUCT(BlueprintType)
struct FKillerItemProperty
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	TSoftClassPtr<AActor> Object;

	UPROPERTY(EditAnywhere)
	UCurveFloat* Population;

	UPROPERTY(EditAnywhere)
	EGameplayElementType _gameplayElementType;

	UPROPERTY(EditAnywhere)
	TSoftClassPtr<UIterativeWeightAdjustmentStrategy> IterativeWeightAdjustmentStrategyClass;

	UPROPERTY(EditAnywhere)
	int32 _tileSpawnPointPriority;

public:
	DEADBYDAYLIGHT_API FKillerItemProperty();
};

FORCEINLINE uint32 GetTypeHash(const FKillerItemProperty) { return 0; }
