#pragma once

#include "CoreMinimal.h"
#include "DBDBaseMatchGameMode.h"
#include "OnPlayersLoadoutsCreated.h"
#include "Templates/SubclassOf.h"
#include "EGameState.h"
#include "DBDGameMode.generated.h"

class UStatusEffect;
class APlayerState;
class APlayerController;
class APlayerStart;
class UNavmeshGeneratorComponent;
class ADBDPlayerState;

UCLASS(NonTransient)
class DEADBYDAYLIGHT_API ADBDGameMode : public ADBDBaseMatchGameMode
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintAssignable)
	FOnPlayersLoadoutsCreated OnPlayersLoadoutsCreated;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, NoClear)
	TSubclassOf<APlayerController> _killerPlayerControllerClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, NoClear)
	TSubclassOf<APlayerController> _survivorPlayerControllerClass;

	UPROPERTY()
	TArray<APlayerStart*> _initialPlayerStarts;

private:
	UPROPERTY(EditAnywhere)
	int32 KillerCreationPositionOrder;

	UPROPERTY(Transient, Export)
	UStatusEffect* _gateBlockedStatus;

	UPROPERTY(Transient, Export)
	UNavmeshGeneratorComponent* _navmeshGeneratorComponent;

protected:
	UFUNCTION(BlueprintCallable)
	void SetPlayerCount(int32 playerAmount);

public:
	UFUNCTION()
	void RegisterOnPlayerStateChanged(APlayerState* playerState);

	UFUNCTION()
	void OnPlayerGameStateChanged(ADBDPlayerState* playerState, EGameState playerGameState);

protected:
	UFUNCTION(BlueprintCallable)
	void LevelLoaded(const FString& levelName);

public:
	UFUNCTION(BlueprintPure)
	bool IsEscapeOpen() const;

protected:
	UFUNCTION(BlueprintCallable)
	void InitializeEscapeRequirements();

	UFUNCTION(BlueprintCallable)
	void HostGame();

	UFUNCTION(BlueprintPure)
	bool AreLoadoutsCreated() const;

public:
	ADBDGameMode();
};

FORCEINLINE uint32 GetTypeHash(const ADBDGameMode) { return 0; }
