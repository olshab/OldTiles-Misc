#pragma once

#include "CoreMinimal.h"
#include "AIPointOfInterestTargetInterface.h"
#include "Interactable.h"
#include "UObject/NoExportTypes.h"
#include "EscapeDoor.generated.h"

class ACamperPlayer;
class UChargeableComponent;
class UBlockableComponent;
class ADBDPlayer;
class USceneComponent;
class UObject;
class UAkComponent;
class UEscapeDoorAnimInstance;
class USpotLightComponent;
class UAIPerceptionStimuliSourceComponent;
class AActor;
class UChargeableInteractionDefinition;
class UBoxComponent;
class USkeletalMeshComponent;

UCLASS()
class DEADBYDAYLIGHT_API AEscapeDoor : public AInteractable, public IAIPointOfInterestTargetInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FVector> EscapePositions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UObject*> EscapeFire;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(BindWidget))
	UChargeableComponent* _killerOpenChargeable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(BindWidget))
	UChargeableComponent* _openChargeable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
	UAkComponent* _ak_audio_escape;

	UPROPERTY(BlueprintReadWrite, Transient)
	UEscapeDoorAnimInstance* _escapeDoorAnimInstance;

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	USceneComponent* _rootComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing=OnRep_Activated)
	bool _activated;

private:
	UPROPERTY(Export)
	USpotLightComponent* _spotlight;

	UPROPERTY(Transient)
	TArray<TWeakObjectPtr<ACamperPlayer>> _localOverlappingSurvivors;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Export, meta=(AllowPrivateAccess=true))
	UAIPerceptionStimuliSourceComponent* _perceptionStimuliComponent;

	UPROPERTY(Transient, Export)
	UBlockableComponent* _doorSwitchBlockableComponent;

public:
	UFUNCTION(BlueprintCallable)
	void SetIsActivated(bool isActivated);

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void OnUnblockDoorSwitchCosmetic();

private:
	UFUNCTION()
	void OnRep_Activated(bool oldActivated);

protected:
	UFUNCTION(BlueprintCallable)
	void OnPlayerExitExitArea(ADBDPlayer* player);

	UFUNCTION(BlueprintCallable)
	void OnPlayerEnterExitArea(ADBDPlayer* player);

public:
	UFUNCTION(BlueprintImplementableEvent)
	void OnExitOpenChanged(bool opened);

	UFUNCTION(BlueprintCallable)
	void OnExitGateOpened(ADBDPlayer* player);

	UFUNCTION(BlueprintImplementableEvent)
	void OnExitActivationChanged(bool activated);

protected:
	UFUNCTION(BlueprintCallable)
	void OnEscapeZoneEndOverlap(AActor* overlappingActor);

	UFUNCTION(BlueprintCallable)
	void OnEscapeZoneBeginOverlap(AActor* overlappingActor);

	UFUNCTION(BlueprintImplementableEvent)
	void OnBlockDoorSwitchCosmetic();

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, BlueprintCosmetic)
	void LightAllLights();

	UFUNCTION(BlueprintPure)
	bool IsDoorSwitchBlocked() const;

	UFUNCTION(BlueprintPure)
	bool IsActivated() const;

	UFUNCTION(BlueprintImplementableEvent)
	USceneComponent* GetSwitchSceneComponent() const;

	UFUNCTION(BlueprintPure, BlueprintNativeEvent)
	FVector GetParadiseServerLocation() const;

	UFUNCTION(BlueprintPure)
	float GetOpenTime() const;

	UFUNCTION(BlueprintImplementableEvent)
	UChargeableInteractionDefinition* GetOpenEscapeInteraction();

	UFUNCTION(BlueprintPure)
	bool GetIsOpen() const;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	UBoxComponent* GetExitArea() const;

public:
	UFUNCTION(BlueprintImplementableEvent)
	FVector GetEscapeSwitchFloorLocation() const;

	UFUNCTION(BlueprintPure, BlueprintNativeEvent)
	USkeletalMeshComponent* GetDoorSkeletalMeshComponent() const;

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	AEscapeDoor();
};

FORCEINLINE uint32 GetTypeHash(const AEscapeDoor) { return 0; }
