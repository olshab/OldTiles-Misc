#pragma once

#include "CoreMinimal.h"
#include "VideoPlayer.h"
#include "GameFramework/Actor.h"
#include "StreamVideoPlayer.generated.h"

class UAudioComponent;
class UMediaPlayer;
class UStreamMediaSource;
class UMediaSoundComponent;
class UUMGStreamVideoWidget;

UCLASS()
class DEADBYDAYLIGHT_API AStreamVideoPlayer : public AActor, public IVideoPlayer
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Transient)
	UMediaPlayer* MediaPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Transient, meta=(BindWidget))
	UMediaSoundComponent* SoundComponent;

	UPROPERTY(Transient, meta=(BindWidget))
	UUMGStreamVideoWidget* StreamVideoWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Transient)
	UStreamMediaSource* StreamMediaSource;

private:
	UPROPERTY(Transient, Export)
	UAudioComponent* _audioComponent;

private:
	UFUNCTION()
	void OnVideoAssetLoaded();

	UFUNCTION()
	void OnSkipButtonTriggered();

	UFUNCTION()
	void OnMediaOpened(const FString& openedUrl);

	UFUNCTION()
	void OnMediaClosed();

	UFUNCTION()
	void OnEndReached();

public:
	AStreamVideoPlayer();
};

FORCEINLINE uint32 GetTypeHash(const AStreamVideoPlayer) { return 0; }
