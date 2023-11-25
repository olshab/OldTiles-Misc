#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ArchiveEditorViewInterface.h"
#include "CoreArchiveQuestMapWidget.h"
#include "EEditorMode.h"
#include "TomeQuestEditorSaveDelegate.h"
#include "LinePair.h"
#include "CoreArchiveQuestEditorWidget.generated.h"

class UVerticalBox;
class UCoreArchiveQuestNodeWidget;
class UCoreButtonWidget;
class UCheckBox;
class UCoreKeyListenerButtonWidget;
class UBorder;
class UEditableTextBox;
class UCoreArchiveQuestPathWidget;
class UOverlay;
class UDBDTextBlock;

UCLASS(EditInlineNew)
class DBDUIVIEWSCORE_API UCoreArchiveQuestEditorWidget : public UCoreArchiveQuestMapWidget, public IArchiveEditorViewInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, Transient)
	TArray<FLinePair> _gridLinesListVertical;

	UPROPERTY(BlueprintReadOnly, Transient)
	TArray<FLinePair> _gridLinesListHorizontal;

	UPROPERTY(meta=(BindWidget))
	UCoreArchiveQuestNodeWidget* _activeNode;

	UPROPERTY(meta=(BindWidget))
	UCoreArchiveQuestPathWidget* _pathInCreation;

	UPROPERTY()
	FTomeQuestEditorSaveDelegate _questEditorSaveDelegate;

	UPROPERTY(BlueprintReadOnly)
	bool _isCreatingPath;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UBorder* EditorBorder;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCheckBox* MoveNodesRadioCheckbox;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCheckBox* LinkNodesRadioCheckbox;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCheckBox* GridVisibilityCheckbox;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCheckBox* SnapGridCheckbox;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UEditableTextBox* GridTileWidthInputPixelsTextBox;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UEditableTextBox* GridTileWidthInputPercentTextBox;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UEditableTextBox* GridTileHeightInputPixelsTextBox;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UEditableTextBox* GridTileHeightInputPercentTextBox;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCoreKeyListenerButtonWidget* RefreshGridButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UOverlay* NodeCoordinateContainer;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UEditableTextBox* NodeXInputPixels;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UEditableTextBox* NodeXInputPercent;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UEditableTextBox* NodeYInputPixels;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UEditableTextBox* NodeYInputPercent;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCoreKeyListenerButtonWidget* SubmitButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCoreKeyListenerButtonWidget* SaveQuestMapButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UVerticalBox* SaveInfoContainer;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDTextBlock* PathTextBlock;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float GridTileHeightValuePercent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float GridTileWidthValuePercent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool IsSnapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool IsGridVisible;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	EEditorMode Mode;

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SetHighlightedGridLines(int32 verticalIndex, int32 horizontalIndex);

	UFUNCTION(BlueprintImplementableEvent)
	void SetGridLinesArray(const TArray<FLinePair>& gridArrayVertical, const TArray<FLinePair>& gridArrayHorizontal);

private:
	UFUNCTION()
	void OnSnapGridChecked(bool checked);

	UFUNCTION()
	void OnSaveGraphClick(UCoreButtonWidget* buttonTarget);

	UFUNCTION()
	void OnRefreshGridClick(UCoreButtonWidget* buttonTarget);

protected:
	UFUNCTION()
	void OnPathClicked(UCoreButtonWidget* buttonTarget);

private:
	UFUNCTION()
	void OnNodeYPixelChanged(const FText& text);

	UFUNCTION()
	void OnNodeYPercentChanged(const FText& text);

	UFUNCTION()
	void OnNodeXPixelChanged(const FText& text);

	UFUNCTION()
	void OnNodeXPercentChanged(const FText& text);

	UFUNCTION()
	void OnNodeSubmitClick(UCoreButtonWidget* buttonTarget);

	UFUNCTION()
	void OnNodeBeginDrag(const FName& id);

	UFUNCTION()
	void OnMoveNodesModeChecked(bool checked);

	UFUNCTION()
	void OnLinkNodesModeChecked(bool checked);

	UFUNCTION()
	void OnGridVisbilityChecked(bool checked);

	UFUNCTION()
	void OnGridTileWidthPixelChanged(const FText& text);

	UFUNCTION()
	void OnGridTileWidthPercentChanged(const FText& text);

	UFUNCTION()
	void OnGridTileHeightPixelChanged(const FText& text);

	UFUNCTION()
	void OnGridTileHeightPercentChanged(const FText& text);

protected:
	UFUNCTION(BlueprintCallable)
	void NodeDragged(const FVector2D& position);

	UFUNCTION(BlueprintCallable)
	void IntermediatePathMove(const FVector2D& position);

public:
	UCoreArchiveQuestEditorWidget();
};

FORCEINLINE uint32 GetTypeHash(const UCoreArchiveQuestEditorWidget) { return 0; }
