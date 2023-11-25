#pragma once

#include "CoreMinimal.h"
#include "MobileBaseUserWidget.h"
#include "UMGAtlantaEventsDescription.generated.h"

class UCanvasPanel;
class UUMGBaseButtonWidget;
class UUMGAtlantaBaseEventsTemplate;
class UAtlantaEventsTemplateDataAsset;
class UTextBlock;

UCLASS(Abstract, EditInlineNew)
class UUMGAtlantaEventsDescription : public UMobileBaseUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	UAtlantaEventsTemplateDataAsset* widgetData;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCanvasPanel* ItemsRewards;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* Title;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* Description;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* TimePeriodTitle;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* TimePeriodStart;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* TimePeriodEnd;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGBaseButtonWidget* DeepLinkButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCanvasPanel* TimePeriodCanvas;

private:
	UPROPERTY(Transient, Export)
	UUMGAtlantaBaseEventsTemplate* _eventTemplate;

private:
	UFUNCTION()
	void HandleButtonClicked();

public:
	UUMGAtlantaEventsDescription();
};

FORCEINLINE uint32 GetTypeHash(const UUMGAtlantaEventsDescription) { return 0; }
