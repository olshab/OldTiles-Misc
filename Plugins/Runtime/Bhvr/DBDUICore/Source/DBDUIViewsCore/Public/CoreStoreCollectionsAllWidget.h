#pragma once

#include "CoreMinimal.h"
#include "StoreCollectionsAllViewInterface.h"
#include "CoreBaseUserWidget.h"
#include "CoreStoreCollectionsAllWidget.generated.h"

UCLASS(EditInlineNew)
class UCoreStoreCollectionsAllWidget : public UCoreBaseUserWidget, public IStoreCollectionsAllViewInterface
{
	GENERATED_BODY()

public:
	UCoreStoreCollectionsAllWidget();
};

FORCEINLINE uint32 GetTypeHash(const UCoreStoreCollectionsAllWidget) { return 0; }
