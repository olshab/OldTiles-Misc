#pragma once

#include "CoreMinimal.h"
#include "CoreBaseUserWidget.h"
#include "CustomizationItemPreviewAreaViewData.h"
#include "CoreImagePreviewAreaWidget.generated.h"

class UDBDImage;
class UDBDRichTextBlock;
class UCustomizationItemGridContainer;

UCLASS(EditInlineNew)
class UCoreImagePreviewAreaWidget : public UCoreBaseUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDImage* PreviewArea;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDRichTextBlock* ItemContainerText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCustomizationItemGridContainer* ItemContainer;

public:
	UFUNCTION(BlueprintCallable)
	void SetData(const FCustomizationItemPreviewAreaViewData& viewData);

protected:
	UFUNCTION()
	void OnItemClicked(const int32 selectedIndex);

public:
	UCoreImagePreviewAreaWidget();
};

FORCEINLINE uint32 GetTypeHash(const UCoreImagePreviewAreaWidget) { return 0; }
