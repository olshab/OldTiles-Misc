#pragma once

#include "CoreMinimal.h"
#include "MobileBaseUserWidget.h"
#include "DownloadProgression.h"
#include "UMGDownloadProgressionWidget.generated.h"

class UProgressBar;
class UTextBlock;

UCLASS(EditInlineNew)
class UUMGDownloadProgressionWidget : public UMobileBaseUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UProgressBar* ProgressBar;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* DownloadPercentage;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* DownloadDescription;

public:
	UFUNCTION()
	void UpdateProgression(const FDownloadProgression& downloadProgression);

public:
	UUMGDownloadProgressionWidget();
};

FORCEINLINE uint32 GetTypeHash(const UUMGDownloadProgressionWidget) { return 0; }
