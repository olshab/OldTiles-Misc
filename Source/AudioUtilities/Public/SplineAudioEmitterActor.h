#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SplineAudioEmitterActor.generated.h"

class UAkComponent;
class USceneComponent;
class USplineComponent;

UCLASS()
class AUDIOUTILITIES_API ASplineAudioEmitterActor : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	USceneComponent* _root;

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	USplineComponent* _theSpline;

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UAkComponent* _emitter;

public:
	ASplineAudioEmitterActor();
};

FORCEINLINE uint32 GetTypeHash(const ASplineAudioEmitterActor) { return 0; }
