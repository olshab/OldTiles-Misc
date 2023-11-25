#pragma once

#include "CoreMinimal.h"
#include "UMGBaseSideMainMenuButton.h"
#include "UObject/ScriptInterface.h"
#include "UMGMenuBaseBanner.generated.h"

class ISlateTextureAtlasInterface;
class UImage;
class UTextBlock;

UCLASS(Abstract, EditInlineNew)
class UUMGMenuBaseBanner : public UUMGBaseSideMainMenuButton
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* BannerImage;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* Title;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TScriptInterface<ISlateTextureAtlasInterface> DefaultBanner;

public:
	UUMGMenuBaseBanner();
};

FORCEINLINE uint32 GetTypeHash(const UUMGMenuBaseBanner) { return 0; }
