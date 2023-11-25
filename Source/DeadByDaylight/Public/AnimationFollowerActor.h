#pragma once

#include "CoreMinimal.h"
#include "AnimationMontageDescriptor.h"
#include "GameFramework/Actor.h"
#include "AnimationFollowerActor.generated.h"

class UMontagePlayer;
class UDBDSkeletalMeshComponentBudgeted;
class UAnimationMontageSlave;

UCLASS()
class DEADBYDAYLIGHT_API AAnimationFollowerActor : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UDBDSkeletalMeshComponentBudgeted* _skeletalMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
	UAnimationMontageSlave* _montageFollower;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
	UMontagePlayer* _montagePlayer;

private:
	UFUNCTION()
	void OnMontageStopped(const FAnimationMontageDescriptor id);

	UFUNCTION()
	void OnMontageStarted(const FAnimationMontageDescriptor id, const float rate);

	UFUNCTION()
	void OnMontageEnd(const FAnimationMontageDescriptor montage, bool interrupted);

protected:
	UFUNCTION()
	void NativeOnMontageStopped(const FAnimationMontageDescriptor id);

	UFUNCTION()
	void NativeOnMontageStarted(const FAnimationMontageDescriptor id, const float rate);

	UFUNCTION()
	void NativeOnMontageEnded(const FAnimationMontageDescriptor montage, bool interrupted);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void Cosmetic_OnMontageStopped();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void Cosmetic_OnMontageStarted();

public:
	AAnimationFollowerActor();
};

FORCEINLINE uint32 GetTypeHash(const AAnimationFollowerActor) { return 0; }
