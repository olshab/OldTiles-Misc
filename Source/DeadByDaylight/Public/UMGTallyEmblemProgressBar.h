#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateBrush.h"
#include "MobileBaseUserWidget.h"
#include "EEmblemQuality.h"
#include "UObject/SoftObjectPtr.h"
#include "UObject/NoExportTypes.h"
#include "UMGTallyEmblemProgressBar.generated.h"

class UProgressBar;
class UCanvasPanel;
class UUMGTallyEmblemMarker;

UCLASS(Abstract, EditInlineNew)
class UUMGTallyEmblemProgressBar : public UMobileBaseUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UProgressBar* ProgressBar;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCanvasPanel* QualityContainer;

	UPROPERTY(EditDefaultsOnly)
	TSoftClassPtr<UUMGTallyEmblemMarker> EmblemQualityClass;

	UPROPERTY(EditDefaultsOnly)
	FVector2D _emblemQualityAlignment;

	UPROPERTY(EditDefaultsOnly, NoClear)
	TMap<EEmblemQuality, FSlateBrush> _qualityFillImages;

public:
	UUMGTallyEmblemProgressBar();
};

FORCEINLINE uint32 GetTypeHash(const UUMGTallyEmblemProgressBar) { return 0; }
