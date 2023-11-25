#pragma once

#include "CoreMinimal.h"
#include "SubPresenter.h"
#include "UObject/ScriptInterface.h"
#include "CustomizationRewardViewData.h"
#include "EventEntryRewardsSubPresenter.generated.h"

class UEventEntryPresenter;
class IEventCollectionViewInterface;

UCLASS()
class UEventEntryRewardsSubPresenter : public USubPresenter
{
	GENERATED_BODY()

protected:
	UPROPERTY(Transient)
	TScriptInterface<IEventCollectionViewInterface> _tabWidget;

	UPROPERTY(Transient)
	TArray<FCustomizationRewardViewData> _rewardsGridData;

	UPROPERTY(Transient)
	TArray<FCustomizationRewardViewData> _previewAreaRewardsData;

	UPROPERTY(Transient, meta=(BindWidget))
	UEventEntryPresenter* _parentPresenter;

protected:
	UFUNCTION()
	void OnRewardGridItemClicked(const int32 selectedIndex);

	UFUNCTION()
	void OnPreviewAreaItemClicked(const int32 selectedIndex);

	UFUNCTION()
	void OnInstructionButtonClicked();

public:
	UEventEntryRewardsSubPresenter();
};

FORCEINLINE uint32 GetTypeHash(const UEventEntryRewardsSubPresenter) { return 0; }
