#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AnimationPreviewSubsystem.generated.h"

UCLASS()
class DEADBYDAYLIGHT_API UAnimationPreviewSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UAnimationPreviewSubsystem();
};

FORCEINLINE uint32 GetTypeHash(const UAnimationPreviewSubsystem) { return 0; }
