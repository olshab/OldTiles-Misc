#pragma once

#include "CoreMinimal.h"
#include "CoreButtonSelector.h"
#include "Templates/SubclassOf.h"
#include "StoreFeaturedCharacterViewData.h"
#include "CoreStoreFeaturedCharacterContainerWidget.generated.h"

class UHorizontalBox;
class UCoreStoreFeaturedCharacterWidget;

UCLASS(EditInlineNew)
class UCoreStoreFeaturedCharacterContainerWidget : public UCoreButtonSelector
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, NoClear)
	TSubclassOf<UCoreStoreFeaturedCharacterWidget> CharacterTileClass;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UHorizontalBox* Root;

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetCharacters(const TArray<FStoreFeaturedCharacterViewData>& viewDataArray);

private:
	UFUNCTION()
	void OnTransitionRequested(int32 characterIndex);

public:
	UCoreStoreFeaturedCharacterContainerWidget();
};

FORCEINLINE uint32 GetTypeHash(const UCoreStoreFeaturedCharacterContainerWidget) { return 0; }
