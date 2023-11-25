#pragma once

#include "CoreMinimal.h"
#include "DisplayStand.h"
#include "EAtlantaDisplayStandPosition.h"
#include "AtlantaDisplayStand.generated.h"

class USceneComponent;

UCLASS()
class DEADBYDAYLIGHT_API AAtlantaDisplayStand : public ADisplayStand
{
	GENERATED_BODY()

public:
	UPROPERTY(EditInstanceOnly)
	EAtlantaDisplayStandPosition StandPosition;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(BindWidget))
	USceneComponent* SurvivorPositionMarker;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(BindWidget))
	USceneComponent* KillerPositionMarker;

public:
	AAtlantaDisplayStand();
};

FORCEINLINE uint32 GetTypeHash(const AAtlantaDisplayStand) { return 0; }
