#pragma once

#include "CoreMinimal.h"
#include "CoreBaseUserWidget.h"
#include "CustomizationRewardViewData.h"
#include "Templates/SubclassOf.h"
#include "CustomizationItemGridContainer.generated.h"

class UCoreSelectableButtonWidget;
class UCoreCustomizationRewardWidget;
class UGridPanel;
class UDBDScrollBox;
class UCoreKeyListenerInputPromptWidget;

UCLASS(EditInlineNew)
class UCustomizationItemGridContainer : public UCoreBaseUserWidget
{
	GENERATED_BODY()

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemClickedDelegate, const int32, selectedIndex);

protected:
	UPROPERTY(EditAnywhere, NoClear)
	TSubclassOf<UCoreCustomizationRewardWidget> _customizationRewardWidgetClass;

	UPROPERTY(EditAnywhere)
	bool _setSmallTemplate;

	UPROPERTY(EditAnywhere)
	int32 _columnCountInGrid;

	UPROPERTY(EditAnywhere)
	float _customizationTileScale;

	UPROPERTY(EditAnywhere)
	int32 _rowCountToShowScrollBar;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UGridPanel* GridContainer;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDScrollBox* ScrollBox;

	UPROPERTY(BlueprintReadOnly)
	FText _scrollLabelText;

public:
	UFUNCTION(BlueprintCallable)
	void SetSmallTemplate(const bool setSmallTemplate);

	UFUNCTION(BlueprintCallable)
	void SetSelectedItem(const int32 selectedIndex);

	UFUNCTION(BlueprintCallable)
	void SetScrollPrompt(UCoreKeyListenerInputPromptWidget* displayPrompt);

	UFUNCTION(BlueprintCallable)
	void SetData(const TArray<FCustomizationRewardViewData>& customizationRewardsData, const int32 selectedIndex);

protected:
	UFUNCTION()
	void OnItemClicked(UCoreSelectableButtonWidget* buttonTarget, bool isSelected);

public:
	UFUNCTION(BlueprintPure=false, BlueprintCallable)
	void HideMilestonePointIcons() const;

protected:
	UFUNCTION(BlueprintPure=false, BlueprintCallable)
	void ClearGrid() const;

public:
	UCustomizationItemGridContainer();
};

FORCEINLINE uint32 GetTypeHash(const UCustomizationItemGridContainer) { return 0; }
