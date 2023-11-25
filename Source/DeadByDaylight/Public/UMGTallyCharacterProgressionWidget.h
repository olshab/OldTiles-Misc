#pragma once

#include "CoreMinimal.h"
#include "UMGTallyListElementWidget.h"
#include "UMGTallyCharacterProgressionWidget.generated.h"

class UUMGTallyCharacterProgressionBar;
class UTextBlock;
class UImage;

UCLASS(Abstract, EditInlineNew)
class UUMGTallyCharacterProgressionWidget : public UUMGTallyListElementWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUMGTallyCharacterProgressionBar* CharacterProgressionBar;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* TextCharacterCurrentExperience;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* TextExperienceForNextLevel;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* TextExperienceEarned;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* TextCurrentLevel;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* CharacterPicture;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* PrestigeIcon;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* TextCharacterName;

	UPROPERTY(EditAnywhere)
	int32 ExperiencePerSecond;

public:
	UFUNCTION(BlueprintCallable)
	void StartSequence();

private:
	UFUNCTION()
	void StartNewLevel();

public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetToFinalState();

private:
	UFUNCTION()
	void OnFullBarOut();

	UFUNCTION()
	void OnFullBarIn();

public:
	UUMGTallyCharacterProgressionWidget();
};

FORCEINLINE uint32 GetTypeHash(const UUMGTallyCharacterProgressionWidget) { return 0; }
