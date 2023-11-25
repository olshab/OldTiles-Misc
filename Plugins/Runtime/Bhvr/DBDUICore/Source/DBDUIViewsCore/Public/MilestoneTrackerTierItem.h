#pragma once

#include "CoreMinimal.h"
#include "CoreBaseUserWidget.h"
#include "UObject/SoftObjectPtr.h"
#include "EMilestoneTrackerItemState.h"
#include "MilestoneTrackerItemViewData.h"
#include "MilestoneTrackerTierItem.generated.h"

class UCoreCustomizationRewardWidget;
class UDBDImage;
class UEventPointsWidget;
class UMaterialInstance;

UCLASS(EditInlineNew)
class UMilestoneTrackerTierItem : public UCoreBaseUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCoreCustomizationRewardWidget* Reward;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UEventPointsWidget* EventPointsWidget;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDImage* BackgroundImage;

public:
	UFUNCTION(BlueprintCallable)
	void UpdateBackground(const TSoftObjectPtr<UMaterialInstance> background);

	UFUNCTION(BlueprintImplementableEvent)
	void SetVisualState(const EMilestoneTrackerItemState state);

	UFUNCTION(BlueprintNativeEvent)
	void SetIsOwned(bool isOwned, bool useAnimation);

	UFUNCTION(BlueprintCallable)
	void SetData(const FMilestoneTrackerItemViewData& data);

	UFUNCTION()
	void OnBackgroundImageLoadingStarted();

	UFUNCTION()
	void OnBackgroundImageLoadingCompleted();

	UFUNCTION(BlueprintPure=false, BlueprintCallable)
	void Clear() const;

public:
	UMilestoneTrackerTierItem();
};

FORCEINLINE uint32 GetTypeHash(const UMilestoneTrackerTierItem) { return 0; }
