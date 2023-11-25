#pragma once

#include "CoreMinimal.h"
#include "EStoreCharactersMenuState.h"
#include "StoreSubPresenter.h"
#include "Templates/SubclassOf.h"
#include "ECustomizationCategory.h"
#include "StoreCharactersSubPresenter.generated.h"

class UUserWidget;
class UStoreCharacterItemViewData;

UCLASS(BlueprintType)
class DBDUIPRESENTERS_API UStoreCharactersSubPresenter : public UStoreSubPresenter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> StoreCharactersWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName DisplayStandName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float CameraTransitionDurationSeconds;

private:
	UPROPERTY(Transient)
	TArray<UStoreCharacterItemViewData*> _availableCharacters;

	UPROPERTY(Transient)
	UStoreCharacterItemViewData* _selectedCharacter;

private:
	UFUNCTION()
	void OnMenuTabSelected(EStoreCharactersMenuState menuState, bool alreadySelected);

	UFUNCTION()
	void OnDisplayStandPawnLoaded(int32 characterIndex);

	UFUNCTION()
	void OnCustomizationSelected(int32 customizationIndex);

	UFUNCTION()
	void OnCustomizationCategorySelected(ECustomizationCategory category);

	UFUNCTION()
	void OnCharacterSelected(int32 characterIndex);

public:
	UStoreCharactersSubPresenter();
};

FORCEINLINE uint32 GetTypeHash(const UStoreCharactersSubPresenter) { return 0; }
