#pragma once

#include "CoreMinimal.h"
#include "TooltipWidget.h"
#include "CharacterTooltipViewData.h"
#include "ECharacterDifficulty.h"
#include "CharacterTooltipWidget.generated.h"

class UDBDTextBlock;
class UDBDRichTextBlock;

UCLASS(EditInlineNew)
class DBDUIVIEWSCORE_API UCharacterTooltipWidget : public UTooltipWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDTextBlock* InstructionTB;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDTextBlock* LevelTB;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDTextBlock* LockDetailsTB;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UDBDRichTextBlock* DifficultyRTB;

public:
	UFUNCTION(BlueprintImplementableEvent)
	void SetTooltipData(const FCharacterTooltipViewData& characterViewData);

protected:
	UFUNCTION(BlueprintCallable)
	void SetLockDetails(const FCharacterTooltipViewData& characterViewData);

	UFUNCTION(BlueprintCallable)
	void SetLevel(int32 level);

	UFUNCTION(BlueprintCallable)
	void SetDifficulty(ECharacterDifficulty difficulty);

public:
	UCharacterTooltipWidget();
};

FORCEINLINE uint32 GetTypeHash(const UCharacterTooltipWidget) { return 0; }
