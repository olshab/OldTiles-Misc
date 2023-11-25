#pragma once

#include "CoreMinimal.h"
#include "CinematicViewInterface.h"
#include "CoreBaseUserWidget.h"
#include "UObject/NoExportTypes.h"
#include "CoreBinkVideoPlayerWidget.generated.h"

class UDBDImage;
class UBinkMediaPlayer;
class UScaleBox;
class UUITweenInstance;
class UCanvasPanel;
class USizeBox;
class UImage;

UCLASS(EditInlineNew)
class DBDUIVIEWSCORE_API UCoreBinkVideoPlayerWidget : public UCoreBaseUserWidget, public ICinematicViewInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Export)
	UCanvasPanel* VideoBinkCanvas;

	UPROPERTY(BlueprintReadOnly, Export)
	UDBDImage* VideoBinkBG;

	UPROPERTY(BlueprintReadOnly, Export)
	USizeBox* VideoBinkSizeBox;

	UPROPERTY(BlueprintReadOnly, Export)
	UScaleBox* VideoBinkScaleBox;

	UPROPERTY(BlueprintReadOnly, Export)
	UImage* VideoBinkImage;

private:
	UPROPERTY(Transient)
	UBinkMediaPlayer* _binkMediaPlayer;

public:
	UFUNCTION(BlueprintCallable)
	void SetSize_Implementation(FVector2D size);

	UFUNCTION()
	void OnSubtitlesChanged(const TArray<FString>& subtitlesText);

	UFUNCTION()
	void OnMediaOpened(const FString& openedUrl);

	UFUNCTION()
	void OnMediaClosed();

private:
	UFUNCTION()
	void OnFadeOutAnimationComplete(UUITweenInstance* tween);

	UFUNCTION()
	void OnFadeInAnimationComplete(UUITweenInstance* tween);

public:
	UFUNCTION()
	void OnEndReached();

	UFUNCTION(BlueprintCallable)
	void FadeOutAnimation_Implementation(const float fadeOutDuration, const float delay);

	UFUNCTION(BlueprintCallable)
	void FadeInAnimation_Implementation(const float fadeInDuration, const float delay);

public:
	UCoreBinkVideoPlayerWidget();
};

FORCEINLINE uint32 GetTypeHash(const UCoreBinkVideoPlayerWidget) { return 0; }
