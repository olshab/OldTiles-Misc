// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FToolBarBuilder;
class FMenuBuilder;

class FJsonValue;
class FJsonObject;

class UParticleSystem;
class UParticleEmitter;
class UParticleLODLevel;
class UParticleModule;
class UParticleModuleTypeDataBase;
class UDistribution;


class FParticleSystemGeneratorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command. */
	void PluginButtonClicked();
	
private:

	void RegisterMenus();


private:
	TSharedPtr<class FUICommandList> PluginCommands;


private:
	UParticleSystem* ParticleSystem;
	UParticleEmitter* CurrentEmitter;
	UParticleLODLevel* CurrentLODLevel;
	UParticleModule* CurrentModule;

	TArray<TSharedPtr<FJsonValue>> ImportTable;

private:
	void Main();

	UObject* ResolveImportObject(int32 PackageIndex);

	void SetPropertyValue(FProperty* InProperty, void* PropertyValuePtr, TSharedPtr<FJsonValue> Value);
	void SetObjectProperties(UObject* Object, TSharedPtr<FJsonObject> ObjectProperties);

	/** Utility functions */
	FORCEINLINE UPackage* GetPackage(const FString& PackageName)
	{
		UPackage* Package = FindPackage(nullptr, *PackageName);
		if (!Package)
		{
			Package = LoadPackage(nullptr, *PackageName, LOAD_None);
		}

		return Package;
	}

	FORCEINLINE FString GetAssetName(const FString& PackageName)
	{
		/** Assuming PackageName is in the following format: "/Game/MyFolder/MyAsset" */
		FString AssetName;
		if (PackageName.Split(TEXT("/"), NULL, &AssetName, ESearchCase::CaseSensitive, ESearchDir::FromEnd))
			return AssetName;

		return TEXT("DummyAsset");
	}

	/** Particle System generation */
	UParticleSystem* CreateParticle(const FString& ParticleSystemPackageName, TSharedPtr<FJsonObject> ParticleProperties);

	UParticleEmitter* CreateEmitter(UClass* EmitterClass,
		TSharedPtr<FJsonObject> EmitterProperties,
		TSharedPtr<FJsonObject> RequiredModuleProperties,
		TSharedPtr<FJsonObject> SpawnModuleProperties
	);

	UParticleModule* CreateModule(UClass* ModuleClass, TSharedPtr<FJsonObject> ModuleProperties);

	UParticleModuleTypeDataBase* CreateTypeDataModule(
		UClass* TypeDataModuleClass,
		TSharedPtr<FJsonObject> TypeDataModuleProperties
	);

	UParticleModule* CreateSpawnModule(UClass* ModuleClass, TSharedPtr<FJsonObject> ModuleProperties);

	UDistribution* CreateDistributionOfClass(const FString& DistributionClassName);
	void SetDistributionProperties(UDistribution* Distribution, TSharedPtr<FJsonObject> DistributionProperties);

	void AddDefaultModules();
	void RemoveModules();
};
