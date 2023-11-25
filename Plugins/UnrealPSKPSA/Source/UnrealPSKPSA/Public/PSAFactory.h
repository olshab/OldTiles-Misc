// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PSAImportOptions.h"
#include "Factories/Factory.h"
#include "PSAFactory.generated.h"

class UPSAImportOptions;

UCLASS()
class UNREALPSKPSA_API UPSAFactory : public UFactory
{
	GENERATED_BODY()
public:
	UPSAFactory()
	{
		bEditorImport = true;
		bText = false;

		Formats.Add(FactoryExtension + ";" + FactoryDescription);

		SupportedClass = FactoryClass;
		SettingsImporter = CreateDefaultSubobject<UPSAImportOptions>(TEXT("SceneComp"));
	}
	
	UObject* Import(const FString Filename, UObject* Parent, const FName Name, const EObjectFlags Flags) const;

	UPROPERTY()
	UPSAImportOptions* SettingsImporter;
	
protected:
	UClass* FactoryClass = UAnimSequence::StaticClass();
	FString FactoryExtension = "psa";
	FString FactoryDescription = "ActorX Animation Sequence";

	virtual bool FactoryCanImport(const FString& Filename) override
	{
		const auto Extension = FPaths::GetExtension(Filename);
		return Extension.Equals(FactoryExtension);
	}
	
	virtual UObject* FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Params, FFeedbackContext* Warn, bool& bOutOperationCanceled) override
	{
		return Import(Filename, InParent, InName, Flags);
	}
};
