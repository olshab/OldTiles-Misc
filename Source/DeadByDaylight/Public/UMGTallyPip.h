#pragma once

#include "CoreMinimal.h"
#include "MobileBaseUserWidget.h"
#include "UMGTallyPip.generated.h"

class UImage;

UCLASS(EditInlineNew)
class UUMGTallyPip : public UMobileBaseUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* Filling;

protected:
	UFUNCTION()
	void HideFilling();

public:
	UUMGTallyPip();
};

FORCEINLINE uint32 GetTypeHash(const UUMGTallyPip) { return 0; }
