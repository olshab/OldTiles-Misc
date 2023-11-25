#pragma once

#include "CoreMinimal.h"
#include "MobileBaseUserWidget.h"
#include "WiggleWidget.generated.h"

UCLASS(Abstract, EditInlineNew)
class UWiggleWidget : public UMobileBaseUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	float TimeBetweenAnimationStart;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UMobileBaseUserWidget* WiggleButtonLeft;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UMobileBaseUserWidget* WiggleButtonRight;

protected:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void BecomeUnavailable();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void BecomeAvailable();

public:
	UWiggleWidget();
};

FORCEINLINE uint32 GetTypeHash(const UWiggleWidget) { return 0; }
