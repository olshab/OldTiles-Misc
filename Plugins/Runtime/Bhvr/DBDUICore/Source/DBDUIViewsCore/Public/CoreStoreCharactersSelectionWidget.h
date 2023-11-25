#pragma once

#include "CoreMinimal.h"
#include "CoreBaseUserWidget.h"
#include "StoreCharactersSelectionViewInterface.h"
#include "StoreCharacterSelectedDelegate.h"
#include "Templates/SubclassOf.h"
#include "CoreStoreCharactersSelectionWidget.generated.h"

class UCoreSelectableButtonWidget;
class UCoreStoreCharacterItemWidget;
class UUniformGridPanel;
class UScrollBox;

UCLASS(EditInlineNew)
class DBDUIVIEWSCORE_API UCoreStoreCharactersSelectionWidget : public UCoreBaseUserWidget, public IStoreCharactersSelectionViewInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	FStoreCharacterSelectedDelegate _characterSelectedDelegate;

	UPROPERTY(EditAnywhere, NoClear)
	TSubclassOf<UCoreStoreCharacterItemWidget> _tileWidgetClass;

	UPROPERTY(EditAnywhere)
	int32 _numberOfColumns;

	UPROPERTY(EditAnywhere)
	float _tileScale;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UScrollBox* Scroll;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUniformGridPanel* Container;

	UPROPERTY(Transient, Export)
	TArray<UCoreStoreCharacterItemWidget*> _tiles;

	UPROPERTY(Transient, meta=(BindWidget))
	UCoreStoreCharacterItemWidget* _selectedTile;

protected:
	UFUNCTION()
	void OnCharacterSelected(UCoreSelectableButtonWidget* buttonTarget, bool isSelected);

public:
	UCoreStoreCharactersSelectionWidget();
};

FORCEINLINE uint32 GetTypeHash(const UCoreStoreCharactersSelectionWidget) { return 0; }
