#pragma once

#include "CoreMinimal.h"
#include "StoreCharactersMenuTabSelectedDelegate.h"
#include "StoreCharactersViewInterface.h"
#include "CoreBaseUserWidget.h"
#include "CoreStoreCharactersWidget.generated.h"

class UCoreTabContainerWidget;
class UDBDTextBlock;
class UCoreSelectableButtonWidget;

UCLASS(EditInlineNew)
class DBDUIVIEWSCORE_API UCoreStoreCharactersWidget : public UCoreBaseUserWidget, public IStoreCharactersViewInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Export)
	UCoreTabContainerWidget* MenuTabs;

protected:
	UPROPERTY()
	FStoreCharactersMenuTabSelectedDelegate _menuTabSelectedDelegate;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDTextBlock* SelectedCharacterName;

protected:
	UFUNCTION()
	void OnMenuTabSelectedAgain(UCoreSelectableButtonWidget* selectedButton);

	UFUNCTION()
	void OnMenuTabSelected(UCoreSelectableButtonWidget* selectedButton);

public:
	UCoreStoreCharactersWidget();
};

FORCEINLINE uint32 GetTypeHash(const UCoreStoreCharactersWidget) { return 0; }
