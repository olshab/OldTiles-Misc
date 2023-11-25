// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PSKImportOptions.h"
#include "Factories/Factory.h"
#include "PSKFactory.generated.h"

UCLASS()
class UNREALPSKPSA_API UPSKFactory : public UFactory
{
	GENERATED_BODY()
public:
	UPSKFactory()
	{
		bEditorImport = true;
		bText = false;

		Formats.Add(FactoryExtension + ";" + FactoryDescription);

		SupportedClass = FactoryClass;
		SettingsImporter = CreateDefaultSubobject<UPSKImportOptions>(TEXT("SceneComp"));
	}
	
	UObject* Import(const FString Filename, UObject* Parent, const FName Name, const EObjectFlags Flags, USkeleton* Skeleton) const;
	static void ProcessSkeleton(const FSkeletalMeshImportData&    ImportData,
	                            const USkeleton*                  Skeleton,
	                            FReferenceSkeleton&               OutRefSkeleton,
	                            int32&                            OutSkeletalDepth);

	UPSKImportOptions* SettingsImporter;

protected:
	UClass* FactoryClass = USkeletalMesh::StaticClass();
	FString FactoryExtension = "psk";
	FString FactoryDescription = "ActorX Skeletal Mesh";
	

	virtual bool FactoryCanImport(const FString& Filename) override
	{
		const auto Extension = FPaths::GetExtension(Filename);
		return Extension.Equals(FactoryExtension);
	}
	
	virtual UObject* FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Params, FFeedbackContext* Warn, bool& bOutOperationCanceledSkeleton) override
	{
		return Import(Filename, InParent, FName(*InName.ToString().Replace(TEXT("_LOD0"), TEXT(""))), Flags, SettingsImporter->Skeleton.Get());
	}

};
