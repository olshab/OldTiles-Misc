#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "EDialogConditionSubject.h"
#include "DialogClipSettings.h"
#include "DialogEventSettings.generated.h"

USTRUCT(BlueprintType)
struct FDialogEventSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag GameEventTrigger;

	UPROPERTY(EditDefaultsOnly)
	EDialogConditionSubject ConditionSubject;

	UPROPERTY(EditDefaultsOnly)
	bool OnlyPlayIfLocallyObserved;

	UPROPERTY(EditDefaultsOnly)
	TArray<FDialogClipSettings> Clips;

	UPROPERTY(EditDefaultsOnly)
	bool OverrideCurrentAudio;

	UPROPERTY(EditDefaultsOnly)
	float DelayUntilPlay;

	UPROPERTY(EditDefaultsOnly)
	float PlayProbability;

	UPROPERTY(EditDefaultsOnly)
	int32 EventPriority;

public:
	DEADBYDAYLIGHT_API FDialogEventSettings();
};

FORCEINLINE uint32 GetTypeHash(const FDialogEventSettings) { return 0; }
