#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "CoreMemoryChallengePlayerSpecificController.generated.h"

class UCoreMemoryController;
class UCoreMemoryFragmentComponent;
class ADBDPlayer;

UCLASS()
class ACoreMemoryChallengePlayerSpecificController : public AInfo
{
	GENERATED_BODY()

private:
	UPROPERTY(Replicated, Transient)
	ADBDPlayer* _owningPlayer;

	UPROPERTY(ReplicatedUsing=OnRep_Controller, Transient, Export)
	UCoreMemoryController* _controller;

	UPROPERTY(ReplicatedUsing=OnRep_Fragments, Transient, Export)
	TArray<UCoreMemoryFragmentComponent*> _fragments;

	UPROPERTY(Replicated)
	int32 _numFragmentsToCollect;

public:
	UFUNCTION()
	void StartQuest();

private:
	UFUNCTION()
	void OnRep_Fragments();

	UFUNCTION()
	void OnRep_Controller();

	UFUNCTION()
	void OnPortalReplicated();

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	ACoreMemoryChallengePlayerSpecificController();
};

FORCEINLINE uint32 GetTypeHash(const ACoreMemoryChallengePlayerSpecificController) { return 0; }
