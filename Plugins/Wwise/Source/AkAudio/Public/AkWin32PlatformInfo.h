#pragma once

#include "CoreMinimal.h"
#include "AkPlatformInfo.h"
#include "AkWin32PlatformInfo.generated.h"

UCLASS()
class UAkWin32PlatformInfo : public UAkPlatformInfo
{
	GENERATED_BODY()

public:
	UAkWin32PlatformInfo();
};

FORCEINLINE uint32 GetTypeHash(const UAkWin32PlatformInfo) { return 0; }
