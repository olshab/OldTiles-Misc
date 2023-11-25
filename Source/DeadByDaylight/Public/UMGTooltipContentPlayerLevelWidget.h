#pragma once

#include "CoreMinimal.h"
#include "MobileBaseUserWidget.h"
#include "UMGTooltipContentPlayerLevelWidget.generated.h"

class UUMGLevelBannerWidget;
class URichTextBlock;
class UTextBlock;

UCLASS(Abstract, EditInlineNew)
class UUMGTooltipContentPlayerLevelWidget : public UMobileBaseUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly)
	FText PlayerLevelText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGLevelBannerWidget* LevelBanner;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	URichTextBlock* LevelExperienceRichText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* ExperienceToNextLevelText;

public:
	UFUNCTION()
	void SetInfo(const int32 playerLevel, const int32 playerPrestige, const int32 currentExperience, const int32 nextLevelExperience);

public:
	UUMGTooltipContentPlayerLevelWidget();
};

FORCEINLINE uint32 GetTypeHash(const UUMGTooltipContentPlayerLevelWidget) { return 0; }
