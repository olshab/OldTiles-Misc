#pragma once
#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "ParticleSystemGeneratorSettings.generated.h"

UCLASS(Config=Editor, DefaultConfig, meta=(DisplayName="Particle System Generation Settings"))
class PARTICLESYSTEMGENERATOR_API UParticleSystemGeneratorSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	FORCEINLINE static const UParticleSystemGeneratorSettings* Get()
	{
		return GetDefault<UParticleSystemGeneratorSettings>();
	};

public:
	UPROPERTY(EditAnywhere, Config)
	FString ParticleDumpFilePath;

	UPROPERTY(EditAnywhere, Config)
	FString ParticleSystemPackagePath;
};
