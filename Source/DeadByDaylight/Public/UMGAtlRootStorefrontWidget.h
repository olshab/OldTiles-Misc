#pragma once

#include "CoreMinimal.h"
#include "UMGBaseRootStorefrontWidget.h"
#include "UMGAtlRootStorefrontWidget.generated.h"

class UUMGCurrencyWidget;
class UUMGAuricCellsButton;

UCLASS(Abstract, EditInlineNew)
class UUMGAtlRootStorefrontWidget : public UUMGBaseRootStorefrontWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta=(BindWidget))
	UUMGCurrencyWidget* ShardWalletWidget;

	UPROPERTY(meta=(BindWidget))
	UUMGAuricCellsButton* AuricWalletWidget;

public:
	UUMGAtlRootStorefrontWidget();
};

FORCEINLINE uint32 GetTypeHash(const UUMGAtlRootStorefrontWidget) { return 0; }
