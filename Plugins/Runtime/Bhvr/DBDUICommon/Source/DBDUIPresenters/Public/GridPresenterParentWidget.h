#pragma once

#include "CoreMinimal.h"
#include "PresenterParentWidget.h"
#include "GridPresenterParentWidget.generated.h"

class UGridPanel;

UCLASS(EditInlineNew)
class UGridPresenterParentWidget : public UPresenterParentWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Export)
	UGridPanel* Container;

public:
	UGridPresenterParentWidget();
};

FORCEINLINE uint32 GetTypeHash(const UGridPresenterParentWidget) { return 0; }
