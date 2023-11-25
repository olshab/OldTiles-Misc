// Copyright Epic Games, Inc. All Rights Reserved.

#include "ParticleSystemGenerator.h"
#include "ParticleSystemGeneratorStyle.h"
#include "ParticleSystemGeneratorCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"

#include "UObject/Package.h"
#include "UObject/NoExportTypes.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Toolkits/AssetEditorManager.h"
#include "Misc/FileHelper.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonSerializer.h"

#include "Factories/ParticleSystemFactoryNew.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleEmitter.h"
#include "Particles/ParticleSpriteEmitter.h"
#include "Particles/ParticleLODLevel.h"
#include "Particles/Lifetime/ParticleModuleLifetime.h"
#include "Particles/Color/ParticleModuleColorOverLife.h"
#include "Math/InterpCurve.h"
#include "Particles/ParticleModuleRequired.h"
#include "Particles/RotationRate/ParticleModuleRotationRate.h"
#include "Particles/Spawn/ParticleModuleSpawn.h"
#include "Distributions/DistributionFloatConstant.h"
#include "Distributions/DistributionFloatConstantCurve.h"
#include "Distributions/DistributionFloatUniform.h"
#include "Distributions/DistributionVectorConstant.h"
#include "Distributions/DistributionVectorUniform.h"
#include "Particles/Parameter/ParticleModuleParameterDynamic.h"
#include "Particles/TypeData/ParticleModuleTypeDataBase.h"
#include "Particles/TypeData/ParticleModuleTypeDataGpu.h"
#include "Particles/Spawn/ParticleModuleSpawnPerUnit.h"
#include "ParticleSystemGeneratorSettings.h"

class UParticleModuleSpawnPerUnit;

static const FName ParticleSystemGeneratorTabName("ParticleSystemGenerator");

#define LOCTEXT_NAMESPACE "FParticleSystemGeneratorModule"

void FParticleSystemGeneratorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FParticleSystemGeneratorStyle::Initialize();
	FParticleSystemGeneratorStyle::ReloadTextures();

	FParticleSystemGeneratorCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FParticleSystemGeneratorCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FParticleSystemGeneratorModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FParticleSystemGeneratorModule::RegisterMenus));
}

void FParticleSystemGeneratorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FParticleSystemGeneratorStyle::Shutdown();

	FParticleSystemGeneratorCommands::Unregister();
}

void FParticleSystemGeneratorModule::PluginButtonClicked()
{
	Main();
}

void FParticleSystemGeneratorModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FParticleSystemGeneratorCommands::Get().PluginAction, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FParticleSystemGeneratorCommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}


void FParticleSystemGeneratorModule::Main()
{
	const UParticleSystemGeneratorSettings* Settings = UParticleSystemGeneratorSettings::Get();
	FString JsonFilePath = Settings->ParticleDumpFilePath;

	if (JsonFilePath.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get dump file path from config"));
		return;
	}

	FString JsonContents;
	if (!FFileHelper::LoadFileToString(JsonContents, *JsonFilePath))
	{
		UE_LOG(LogTemp, Error, TEXT("Can't load string from file %s"), *JsonFilePath);
		return;
	}

	TSharedPtr<FJsonObject> JsonObject;
	if (!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(JsonContents), JsonObject))
	{
		UE_LOG(LogTemp, Error, TEXT("Can't deserialize Json file: %s"), *JsonFilePath);
		return;
	}

	FString AssetName = JsonObject->GetStringField(TEXT("ParticleSystemAssetName"));
	ImportTable = JsonObject->GetArrayField(TEXT("ImportTable"));


	/** Particle system generation */
	FString ParticleSystemPackagePath = Settings->ParticleSystemPackagePath;
	if (ParticleSystemPackagePath.IsEmpty())
		ParticleSystemPackagePath = TEXT("/Game/Effects/ParticleSystems");

	FString ParticleSystemPackageName = ParticleSystemPackagePath + TEXT('/') + AssetName;

	TSharedPtr<FJsonObject> ParticleSystemProperties = JsonObject->GetObjectField(TEXT("ParticleSystemProperties"));
	if (JsonObject == NULL)
		return;

	if (CreateParticle(ParticleSystemPackageName, ParticleSystemProperties) == NULL)
	{
		UE_LOG(LogTemp, Fatal, TEXT("Failed to create particle system asset with path %s"), TEXT("/Game/Effects/Fire"));
		return;
	}

	TArray<TSharedPtr<FJsonValue>> Emitters = JsonObject->GetArrayField(TEXT("Emitters"));
	for (TSharedPtr<FJsonValue> EmitterValue : Emitters)
	{
		TSharedPtr<FJsonObject> Emitter = EmitterValue->AsObject();
		if (Emitter == NULL)
			continue;

		TSharedPtr<FJsonObject> EmitterProperties = Emitter->GetObjectField(TEXT("EmitterProperties"));
		TSharedPtr<FJsonObject> RequiredModuleProperties = Emitter->GetObjectField(TEXT("RequiredModule"));
		TSharedPtr<FJsonObject> SpawnModuleProperties = Emitter->GetObjectField(TEXT("SpawnModule"));

		if (EmitterProperties == NULL || RequiredModuleProperties == NULL || SpawnModuleProperties == NULL)
			continue;

		if (CreateEmitter(UParticleSpriteEmitter::StaticClass(), EmitterProperties, RequiredModuleProperties, SpawnModuleProperties) == NULL)
		{
			UE_LOG(LogTemp, Fatal, TEXT("Failed to create emitter"));
			return;
		}
				
		if (Emitter->HasField(TEXT("TypeDataModule")))
		{
			TSharedPtr<FJsonObject> TypeDataModuleProperties = Emitter->GetObjectField(TEXT("TypeDataModule"));

			const FString TypeDataModuleClassName = TypeDataModuleProperties->GetStringField(TEXT("TypeDataModuleType"));
			UClass* TypeDataModuleClass = FindObjectFast<UClass>(GetPackage(TEXT("/Script/Engine")), *TypeDataModuleClassName);
			CreateTypeDataModule(TypeDataModuleClass, TypeDataModuleProperties);
		}

		TArray<TSharedPtr<FJsonValue>> Modules = Emitter->GetArrayField(TEXT("Modules"));
		for (TSharedPtr<FJsonValue> ModuleValue : Modules)
		{
			TSharedPtr<FJsonObject> Module = ModuleValue->AsObject();

			const FString ModuleClassName = Module->GetStringField(TEXT("ModuleType"));
			UClass* ModuleClass = FindObjectFast<UClass>(GetPackage(TEXT("/Script/Engine")), *ModuleClassName);

			TSharedPtr<FJsonObject> ModuleProperties = Module->GetObjectField(TEXT("ModuleProperties"));
			CreateModule(ModuleClass, ModuleProperties);
		}
	}

	ParticleSystem->PostEditChange();
	ParticleSystem->PostLoad();

	GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->OpenEditorForAsset(ParticleSystem);

#if 0
	UParticleModuleTypeDataBase* TypeData = CreateTypeDataModule(UParticleModuleTypeDataGpu::StaticClass());
	UParticleModuleTypeDataGpu* TypeDataGpu = Cast<UParticleModuleTypeDataGpu>(TypeData);

	// RemoveModules();
	UParticleModule* Module = CreateModule(UParticleModuleRotationRate::StaticClass());
	UDistribution* Dist = CreateDistributionOfClass(TEXT("DistributionFloatUniformCurve"));
	UParticleModuleRotationRate* RotRate = Cast<UParticleModuleRotationRate>(Module);
	RotRate->StartRotationRate.Distribution = Cast<UDistributionFloat>(Dist);
	SetDistributionProperties(Dist);

	GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->OpenEditorForAsset(ParticleSystem);
	ParticleSystem->PostLoad();
#endif
#if 0
	UParticleSystem* ParticleSystem = LoadObject<UParticleSystem>(NULL, TEXT("/Game/Effects/Particle.Particle"), NULL, LOAD_None, NULL);

	/** The start of creating new emitter... */
	ParticleSystem->PreEditChange(NULL);

	UClass* NewEmitterClass = UParticleSpriteEmitter::StaticClass();
	UParticleEmitter* NewEmitter = NewObject<UParticleEmitter>(ParticleSystem, NewEmitterClass, NAME_None, RF_NoFlags);
	check(NewEmitter);

	UParticleLODLevel* LODLevel = NewEmitter->GetLODLevel(0);
	if (LODLevel == NULL)
	{
		NewEmitter->CreateLODLevel(0);
		LODLevel = NewEmitter->GetLODLevel(0);
	}
	check(LODLevel);
	LODLevel->RequiredModule->Material = LoadObject<UMaterialInterface>(NULL, TEXT("/Engine/EngineMaterials/DefaultParticle.DefaultParticle"), NULL, LOAD_None, NULL);

	NewEmitter->EmitterEditorColor = FColor::MakeRandomColor();
	NewEmitter->EmitterEditorColor.A = 255;

	NewEmitter->SetToSensibleDefaults();  // this adds some default modules to that emitter
	NewEmitter->UpdateModuleLists();
	NewEmitter->PostEditChange();
	/* The end of creating new emitter...*/

	ParticleSystem->Emitters.Add(NewEmitter);

	/** Set only one LOD */
	if (ParticleSystem->LODDistances.Num() == 0)
	{
		ParticleSystem->LODDistances.AddZeroed(1);
	}

	if (ParticleSystem->LODSettings.Num() == 0)
	{
		ParticleSystem->LODSettings.AddUninitialized(1);
		ParticleSystem->LODSettings[0] = FParticleSystemLOD::CreateParticleSystemLOD();
	}

	ParticleSystem->PostEditChange();


	/** Trying to add new module */
	ParticleSystem->PreEditChange(NULL);

	UParticleEmitter* CurrentEmitter = ParticleSystem->Emitters[0];
	CurrentEmitter->PreEditChange(NULL);

	UParticleLODLevel* CurrentLODLevel = CurrentEmitter->GetLODLevel(0);
	UParticleModuleRotationRate* RotationRate = NewObject<UParticleModuleRotationRate>(CurrentEmitter->GetOuter());
	UE_LOG(LogTemp, Warning, TEXT("Outer is %s"), *RotationRate->StartRotationRate.Distribution->GetOuter()->GetName());

	RotationRate->StartRotationRate.Distribution = NewObject<UDistributionFloatConstantCurve>(RotationRate);
	if (RotationRate->StartRotationRate.Distribution != NULL)
	{
		// Add two points, one at time 0.0f and one at 1.0f
		for (int32 Key = 0; Key < 2; Key++)
		{
			int32 KeyIndex = RotationRate->StartRotationRate.Distribution->CreateNewKey(Key * 1.0f);
			if (Key == 0)
				RotationRate->StartRotationRate.Distribution->SetKeyOut(0, KeyIndex, 1.0f);
			else
				RotationRate->StartRotationRate.Distribution->SetKeyOut(0, KeyIndex, 0.0f);
		}

		RotationRate->StartRotationRate.Distribution->bIsDirty = true;
	}

	RotationRate->LODValidity = 1;  // for highest LOD level
	CurrentLODLevel->Modules.Add(RotationRate);

	/** Add Dynamic Parameter module */
	UClass* ModuleClass = UParticleModuleParameterDynamic::StaticClass();
	FStaticConstructObjectParameters Params(ModuleClass);
	Params.Outer = CurrentEmitter->GetOuter();

	UObject* CreatedObject = StaticConstructObject_Internal(Params);
	UParticleModuleParameterDynamic* ParameterDynamic = CastChecked<UParticleModuleParameterDynamic>(CreatedObject);

	ParameterDynamic->LODValidity = 1;
	CurrentLODLevel->Modules.Add(ParameterDynamic);
#endif
}

UObject* FParticleSystemGeneratorModule::ResolveImportObject(int32 PackageIndex)
{
	if (PackageIndex >= 0)
		return nullptr;

	TSharedPtr<FJsonObject> Import = ImportTable[-PackageIndex - 1]->AsObject();

	FString ClassPackageName = Import->GetStringField(TEXT("ClassPackage"));
	FString ClassName = Import->GetStringField(TEXT("ClassName"));
	int32 OuterIndex = Import->GetIntegerField(TEXT("OuterIndex"));
	FString ObjectName = Import->GetStringField(TEXT("ObjectName"));

	/** Imports that have OuterIndex = 0 are just path to the asset */
	if (OuterIndex == 0)
	{
		UPackage* Package = GetPackage(*ObjectName);
		if (!Package)
			UE_LOG(LogTemp, Error, TEXT("Can't deserialize package: %s"), *ObjectName);

		return Package;
	}

	/** Otherwise, go through the entire UObject chain until we find an import with OuterIndex = 0*/
	UPackage* ClassPackage = GetPackage(ClassPackageName);
	if (!ClassPackage)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't deserialize ClassPackage: %s"), *ClassPackageName);
		return nullptr;
	}

	UClass* Class = FindObjectFast<UClass>(ClassPackage, *ClassName);
	if (!Class)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't deserialize ClassName: %s"), *ClassName);
		return nullptr;
	}

	UObject* OuterObject = ResolveImportObject(OuterIndex);
	if (!OuterObject)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't deserialize Outer Object for object: %s"), *ObjectName);
		return nullptr;
	}

	UObject* ResultObject = StaticFindObjectFast(Class, OuterObject, *ObjectName);
	if (!ResultObject)
		UE_LOG(LogTemp, Error, TEXT("Can't deserialize object: %s"), *ObjectName);

	return ResultObject;
}

void FParticleSystemGeneratorModule::SetPropertyValue(FProperty* InProperty, void* PropertyValuePtr, TSharedPtr<FJsonValue> Value)
{
	if (FArrayProperty* ArrayProperty = CastField<FArrayProperty>(InProperty))
	{
		FScriptArrayHelper Array(ArrayProperty, PropertyValuePtr);

		Array.EmptyValues();

		const TArray<TSharedPtr<FJsonValue>>& JsonArrayValues = Value->AsArray();
		for (const TSharedPtr<FJsonValue>& JsonArrayValue : JsonArrayValues)
		{
			int32 NewIndex = Array.AddValue();
			uint8* ArrayValuePtr = Array.GetRawPtr(NewIndex);
			SetPropertyValue(ArrayProperty->Inner, ArrayValuePtr, JsonArrayValue);
		}

		return;
	}

	if (FStructProperty* StructProperty = CastField<FStructProperty>(InProperty))
	{
		UScriptStruct* Struct = StructProperty->Struct;
		if (Struct->GetName().Contains(TEXT("RawDistribution"), ESearchCase::CaseSensitive))
		{
			/* If this struct property is FRawDistributionFloat or FRawDistributionVector */
			FObjectProperty* Distribution = CastFieldChecked<FObjectProperty>(Struct->FindPropertyByName(TEXT("Distribution")));

			TSharedPtr<FJsonObject> DistributionAsObject = Value->AsObject();
			UDistribution* NewDist = CreateDistributionOfClass(DistributionAsObject->GetStringField(TEXT("DistributionType")));
			SetDistributionProperties(NewDist, DistributionAsObject->GetObjectField(TEXT("DistributionProperties")));

			Distribution->SetObjectPropertyValue(Distribution->ContainerPtrToValuePtr<void>(PropertyValuePtr), NewDist);
			//SetDistributionProperties(Distribution, Distribution->ContainerPtrToValuePtr<void>(PropertyValuePtr), Value->AsObject());

			return;
		}

		TArray<FString> JsonProperties;
		Value->AsObject()->Values.GetKeys(JsonProperties);

		for (FString& JsonProperty : JsonProperties)
		{
			FProperty* Property = Struct->FindPropertyByName(*JsonProperty);
			if (Property == nullptr)
			{
				UE_LOG(LogTemp, Error, TEXT("Can't find property %s from JSON in ScriptStruct"), *JsonProperty);
				continue;
			}

			SetPropertyValue(
				Property,
				Property->ContainerPtrToValuePtr<void>(PropertyValuePtr),
				Value->AsObject()->GetField<EJson::None>(JsonProperty)
			);
		}

		return;
	}

	if (FBoolProperty* BoolProperty = CastField<FBoolProperty>(InProperty))
	{
		BoolProperty->SetPropertyValue(PropertyValuePtr, Value->AsBool());

		return;
	}

	if (FByteProperty* ByteProperty = CastField<FByteProperty>(InProperty))
	{
		UEnum* IntPropertyEnum = ByteProperty->GetIntPropertyEnum();
		if (IntPropertyEnum)
		{
			FString EnumValue = Value->AsString();
			ByteProperty->SetIntPropertyValue(PropertyValuePtr, IntPropertyEnum->GetValueByNameString(EnumValue));
		}
		else
		{
			int64 ByteValue = (int64)Value->AsNumber();
			ByteProperty->SetIntPropertyValue(PropertyValuePtr, ByteValue);
		}

		return;
	}

	if (FEnumProperty* EnumProperty = CastField<FEnumProperty>(InProperty))
	{
		FNumericProperty* UnderlyingProperty = EnumProperty->GetUnderlyingProperty();
		UEnum* Enum = EnumProperty->GetEnum();

		FString EnumValue = Value->AsString();
		UnderlyingProperty->SetIntPropertyValue(PropertyValuePtr, Enum->GetValueByNameString(EnumValue));

		return;
	}

	if (FNumericProperty* NumericProperty = CastField<FNumericProperty>(InProperty))
	{
		if (NumericProperty->IsFloatingPoint())
			NumericProperty->SetFloatingPointPropertyValue(PropertyValuePtr, Value->AsNumber());
		else
			NumericProperty->SetIntPropertyValue(PropertyValuePtr, (int64)Value->AsNumber());

		return;
	}

	if (FNameProperty* NameProperty = CastField<FNameProperty>(InProperty))
	{
		FName* NamePtr = static_cast<FName*>(PropertyValuePtr);
		*NamePtr = *Value->AsString();

		return;
	}

	if (FStrProperty* StrProperty = CastField<FStrProperty>(InProperty))
	{
		FString* StrPtr = static_cast<FString*>(PropertyValuePtr);
		*StrPtr = *Value->AsString();

		return;
	}

	if (FTextProperty* TextProperty = CastField<FTextProperty>(InProperty))
	{
		FText* TextPtr = static_cast<FText*>(PropertyValuePtr);
		*TextPtr = FText::FromString(Value->AsString());

		return;
	}

	if (FObjectProperty* ObjectProperty = CastField<FObjectProperty>(InProperty))
	{
		int32 PackageIndex = (int32)Value->AsNumber();
		UObject* Object = NULL;

		if (PackageIndex < 0)
		{
			Object = ResolveImportObject(PackageIndex);
			if (Object == nullptr)
				UE_LOG(LogTemp, Warning, TEXT("Failed to load object for property %s"), *InProperty->GetName());

		}

		ObjectProperty->SetObjectPropertyValue(PropertyValuePtr, Object);

		return;
	}

	UE_LOG(LogTemp, Error, TEXT("Failed to resolve FProperty type for property %s"), *InProperty->GetName())
}

void FParticleSystemGeneratorModule::SetObjectProperties(UObject* Object, TSharedPtr<FJsonObject> ObjectProperties)
{
	TArray<FString> PropertyNames;
	ObjectProperties->Values.GetKeys(PropertyNames);

	for (const FString& JsonProperty : PropertyNames)
	{
		if (JsonProperty.Equals(TEXT("DistributionType")) || JsonProperty.Equals(TEXT("ModuleType")))
			continue;

		FProperty* Property = Object->GetClass()->FindPropertyByName(*JsonProperty);
		if (!Property)
		{
			UE_LOG(LogTemp, Error, TEXT("%s doesn't have property with the name %s"), *Object->GetName(), *JsonProperty);
			continue;
		}

		SetPropertyValue(
			Property,
			Property->ContainerPtrToValuePtr<void>(Object),
			ObjectProperties->GetField<EJson::None>(JsonProperty)
		);
	}
}

UParticleSystem* FParticleSystemGeneratorModule::CreateParticle(const FString& ParticleSystemPackageName, TSharedPtr<FJsonObject> ParticleProperties)
{
	UParticleSystemFactoryNew* Factory = NewObject<UParticleSystemFactoryNew>();
	const FString AssetName = GetAssetName(ParticleSystemPackageName);

	UPackage* Package = CreatePackage(*ParticleSystemPackageName);
	EObjectFlags Flags = RF_Public | RF_Standalone;

	UObject* CreatedObject = Factory->FactoryCreateNew(UParticleSystem::StaticClass(), Package, *AssetName, Flags, NULL, NULL);
	if (CreatedObject)
	{
		UParticleSystem* Particle = CastChecked<UParticleSystem>(CreatedObject);


		/** SETUP THE PROPERTIES HERE */
		SetObjectProperties(Particle, ParticleProperties);
		// ...



		FAssetRegistryModule::AssetCreated(Particle);
		Package->MarkPackageDirty();

		ParticleSystem = Particle;
		return ParticleSystem;
	}

	return NULL;
}

UParticleEmitter* FParticleSystemGeneratorModule::CreateEmitter(UClass* EmitterClass,
		TSharedPtr<FJsonObject> EmitterProperties,
		TSharedPtr<FJsonObject> RequiredModuleProperties,
		TSharedPtr<FJsonObject> SpawnModuleProperties
)
{
	check(ParticleSystem);
	check(EmitterClass);
	check(EmitterClass->IsChildOf(UParticleEmitter::StaticClass()));

	ParticleSystem->PreEditChange(NULL);

	UParticleEmitter* NewEmitter = NewObject<UParticleEmitter>(ParticleSystem, EmitterClass, NAME_None, RF_NoFlags);
	check(NewEmitter);
	this->CurrentEmitter = NewEmitter;


	/** SETUP Emitter PROPERTIES HERE */
	SetObjectProperties(NewEmitter, EmitterProperties);
	// ...



	UParticleLODLevel* LODLevel = NewEmitter->GetLODLevel(0);
	if (LODLevel == NULL)
	{
		NewEmitter->CreateLODLevel(0);
		LODLevel = NewEmitter->GetLODLevel(0);
	}
	check(LODLevel);


	/** SETUP RequiredModule and SpawnModule PROPERTIES HERE */
	UParticleModule* RequiredModule = LODLevel->RequiredModule;
	UParticleModule* SpawnModule = LODLevel->SpawnModule;

	//LODLevel->RequiredModule->Material = LoadObject<UMaterialInterface>(NULL, TEXT("/Engine/EngineMaterials/DefaultParticle.DefaultParticle"), NULL, LOAD_None, NULL);

	CurrentModule = RequiredModule;
	SetObjectProperties(RequiredModule, RequiredModuleProperties->GetObjectField(TEXT("ModuleProperties")));
	CurrentModule = SpawnModule;
	SetObjectProperties(SpawnModule, SpawnModuleProperties->GetObjectField(TEXT("ModuleProperties")));
	// ...


	NewEmitter->EmitterEditorColor = FColor::MakeRandomColor();
	NewEmitter->EmitterEditorColor.A = 255;

	// NewEmitter->SetToSensibleDefaults();  // this adds some default modules to that emitter
	// AddDefaultModules();
	NewEmitter->UpdateModuleLists();
	NewEmitter->PostEditChange();

	ParticleSystem->Emitters.Add(NewEmitter);

	/** Set only one LOD */
	if (ParticleSystem->LODDistances.Num() == 0)
	{
		ParticleSystem->LODDistances.AddZeroed(1);
	}

	if (ParticleSystem->LODSettings.Num() == 0)
	{
		ParticleSystem->LODSettings.AddUninitialized(1);
		ParticleSystem->LODSettings[0] = FParticleSystemLOD::CreateParticleSystemLOD();
	}

	ParticleSystem->PostEditChange();

	return NewEmitter;
}

UParticleModule* FParticleSystemGeneratorModule::CreateModule(UClass* ModuleClass, TSharedPtr<FJsonObject> ModuleProperties)
{
	check(CurrentEmitter);
	check(ModuleClass);
	check(ModuleClass->IsChildOf(UParticleModule::StaticClass()));

	ParticleSystem->PreEditChange(NULL);
	CurrentEmitter->PreEditChange(NULL);
	CurrentLODLevel = CurrentEmitter->GetLODLevel(0);

	UParticleModule* NewModule = NewObject<UParticleModule>(CurrentEmitter->GetOuter(), ModuleClass);

	if (NewModule == NULL)
	{
		UE_LOG(LogTemp, Fatal, TEXT("Failed to create module of class %s"), *ModuleClass->GetName());
		return NULL;
	}
	CurrentModule = NewModule;


	/** SETUP THE PROPERTIES HERE */
	SetObjectProperties(NewModule, ModuleProperties);
	// ...


	NewModule->LODValidity = 1;
	CurrentLODLevel->Modules.Add(NewModule);

#if 0
	UParticleModuleRotationRate* RotationRate = NewObject<UParticleModuleRotationRate>(CurrentEmitter->GetOuter());
	UE_LOG(LogTemp, Warning, TEXT("Outer is %s"), *RotationRate->StartRotationRate.Distribution->GetOuter()->GetName());

	RotationRate->StartRotationRate.Distribution = NewObject<UDistributionFloatConstantCurve>(RotationRate);
	if (RotationRate->StartRotationRate.Distribution != NULL)
	{
		// Add two points, one at time 0.0f and one at 1.0f
		for (int32 Key = 0; Key < 2; Key++)
		{
			int32 KeyIndex = RotationRate->StartRotationRate.Distribution->CreateNewKey(Key * 1.0f);
			if (Key == 0)
				RotationRate->StartRotationRate.Distribution->SetKeyOut(0, KeyIndex, 1.0f);
			else
				RotationRate->StartRotationRate.Distribution->SetKeyOut(0, KeyIndex, 0.0f);
		}

		RotationRate->StartRotationRate.Distribution->bIsDirty = true;
	}

	RotationRate->LODValidity = 1;  // for highest LOD level
	CurrentLODLevel->Modules.Add(RotationRate);

	/** Add Dynamic Parameter module */
	UClass* ModuleClass = UParticleModuleParameterDynamic::StaticClass();
	FStaticConstructObjectParameters Params(ModuleClass);
	Params.Outer = CurrentEmitter->GetOuter();

	UObject* CreatedObject = StaticConstructObject_Internal(Params);
	UParticleModuleParameterDynamic* ParameterDynamic = CastChecked<UParticleModuleParameterDynamic>(CreatedObject);

	ParameterDynamic->LODValidity = 1;
	CurrentLODLevel->Modules.Add(ParameterDynamic);
#endif

	CurrentEmitter->UpdateModuleLists();

	CurrentEmitter->PostEditChange();
	ParticleSystem->PostEditChange();

	return NewModule;
}

UParticleModule* FParticleSystemGeneratorModule::CreateSpawnModule(UClass* ModuleClass, TSharedPtr<FJsonObject> ModuleProperties)
{
	check(CurrentEmitter);
	check(ModuleClass);
	check(ModuleClass->IsChildOf(UParticleModule::StaticClass()));

	ParticleSystem->PreEditChange(NULL);
	CurrentEmitter->PreEditChange(NULL);

	UParticleModule* NewModule = NewObject<UParticleModule>(ParticleSystem, ModuleClass);

	if (NewModule == NULL)
	{
		UE_LOG(LogTemp, Fatal, TEXT("Failed to create module of class %s"), *ModuleClass->GetName());
		return NULL;
	}
	CurrentModule = NewModule;


	/** SETUP THE PROPERTIES HERE */
	SetObjectProperties(NewModule, ModuleProperties);
	// ...


	NewModule->LODValidity = 1;

	CurrentEmitter->UpdateModuleLists();
	CurrentEmitter->PostEditChange();
	ParticleSystem->PostEditChange();

	return NewModule;
}

UParticleModuleTypeDataBase* FParticleSystemGeneratorModule::CreateTypeDataModule(UClass* TypeDataModuleClass, TSharedPtr<FJsonObject> TypeDataModuleProperties)
{
	check(CurrentEmitter);
	check(TypeDataModuleClass);
	check(TypeDataModuleClass->IsChildOf(UParticleModuleTypeDataBase::StaticClass()));

	ParticleSystem->PreEditChange(NULL);
	CurrentEmitter->PreEditChange(NULL);
	CurrentLODLevel = CurrentEmitter->GetLODLevel(0);

	UParticleModuleTypeDataBase* NewTypeData = NewObject<UParticleModuleTypeDataBase>(ParticleSystem, TypeDataModuleClass);
	check(NewTypeData);
	CurrentModule = NewTypeData;

	
	/** SETUP THE PROPERTIES HERE */
	TSharedPtr<FJsonObject> TypeDataProperties = TypeDataModuleProperties->GetObjectField(TEXT("TypeDataProperties"));
	if (TypeDataProperties != NULL)
		SetObjectProperties(NewTypeData, TypeDataProperties);

	UParticleModuleTypeDataGpu* TypeDataGpu = Cast<UParticleModuleTypeDataGpu>(NewTypeData);
	if (TypeDataGpu != NULL)
	{
		/** Setup RequiredModule and SpawnModule */
		UParticleModuleRequired* RequiredModule = NewObject<UParticleModuleRequired>(ParticleSystem);
		check(RequiredModule);
		RequiredModule->SetToSensibleDefaults(CurrentEmitter);
		TypeDataGpu->EmitterInfo.RequiredModule = RequiredModule;

		RequiredModule->bUseLocalSpace = false;
		RequiredModule->bKillOnDeactivate = false;
		RequiredModule->bKillOnCompleted = false;
		RequiredModule->EmitterDuration = 1.0f;
		RequiredModule->EmitterLoops = 0;
		RequiredModule->ParticleBurstMethod = EPBM_Instant;
		RequiredModule->ModuleEditorColor = FColor::MakeRandomColor();
		RequiredModule->InterpolationMethod = PSUVIM_None;
		RequiredModule->SubImages_Horizontal = 1;
		RequiredModule->SubImages_Vertical = 1;
		RequiredModule->bScaleUV = false;
		RequiredModule->RandomImageTime = 0.0f;
		RequiredModule->RandomImageChanges = 0;
		RequiredModule->bEnabled = true;
		RequiredModule->LODValidity = 1;

		UParticleModuleSpawn* SpawnModule = NewObject<UParticleModuleSpawn>(ParticleSystem);
		check(SpawnModule);
		TypeDataGpu->EmitterInfo.SpawnModule = SpawnModule;
		SpawnModule->LODValidity = 1;
		UDistributionFloatConstant* ConstantSpawn = Cast<UDistributionFloatConstant>(SpawnModule->Rate.Distribution);
		ConstantSpawn->Constant = 10;
		ConstantSpawn->bIsDirty = true;
		SpawnModule->BurstList.Empty();


		// from TypeDataModuleProperties get RequiredModuleProperties
		if (TypeDataGpu->EmitterInfo.RequiredModule != NULL)
		{
			TSharedPtr<FJsonObject> RequiredModuleProperties = TypeDataModuleProperties->GetObjectField(TEXT("RequiredModule"));
			if (RequiredModuleProperties != NULL)
				SetObjectProperties(TypeDataGpu->EmitterInfo.RequiredModule, RequiredModuleProperties->GetObjectField(TEXT("ModuleProperties")));
		}

		// from TypeDataModuleProperties get SpawnModuleProperties
		if (TypeDataGpu->EmitterInfo.SpawnModule != NULL)
		{
			TSharedPtr<FJsonObject> SpawnModuleProperties = TypeDataModuleProperties->GetObjectField(TEXT("SpawnModule"));
			if (SpawnModuleProperties != NULL)
				SetObjectProperties(TypeDataGpu->EmitterInfo.SpawnModule, SpawnModuleProperties->GetObjectField(TEXT("ModuleProperties")));
		}

		// from TypeDataModuleProperties get SpawnPerUnitModuleProperties
		if (TypeDataGpu->EmitterInfo.SpawnPerUnitModule != NULL)
		{
			TSharedPtr<FJsonObject> SpawnPerUnitModuleProperties = TypeDataModuleProperties->GetObjectField(TEXT("SpawnPerUnitModule"));
			if (SpawnPerUnitModuleProperties != NULL)
				SetObjectProperties(TypeDataGpu->EmitterInfo.SpawnPerUnitModule, SpawnPerUnitModuleProperties->GetObjectField(TEXT("ModuleProperties")));
		}

		// from TypeDataModuleProperties get SpawnModules
		// Resolve SpawnModule class, create it and set its properties (ModuleProperties)
		TArray<TSharedPtr<FJsonValue>> SpawnModules = TypeDataModuleProperties->GetArrayField(TEXT("SpawnModules"));
		for (TSharedPtr<FJsonValue> SpawnModuleValue : SpawnModules)
		{
			TSharedPtr<FJsonObject> Module = SpawnModuleValue->AsObject();
			if (SpawnModule == NULL)
				continue;

			const FString ModuleClassName = Module->GetStringField(TEXT("ModuleType"));
			UClass* ModuleClass = FindObjectFast<UClass>(GetPackage(TEXT("/Script/Engine")), *ModuleClassName);

			TSharedPtr<FJsonObject> ModuleProperties = Module->GetObjectField(TEXT("ModuleProperties"));
			if (ModuleProperties != NULL)
				CreateSpawnModule(ModuleClass, ModuleProperties);
		}
	}
	// ...


	NewTypeData->LODValidity = 1;
	CurrentLODLevel->TypeDataModule = NewTypeData;

	CurrentEmitter->UpdateModuleLists();

	CurrentEmitter->PostEditChange();
	ParticleSystem->PostEditChange();

	return NewTypeData;
}

UDistribution* FParticleSystemGeneratorModule::CreateDistributionOfClass(const FString& DistributionClassName)
{
	check(CurrentModule);

	UClass* DistClass = FindObjectFast<UClass>(GetPackage(TEXT("/Script/Engine")), *DistributionClassName);

	if (DistClass != NULL)
	{
		check(DistClass->IsChildOf(UDistribution::StaticClass()));

		UDistribution* Distribution = NewObject<UDistribution>(CurrentModule, DistClass);
		return Distribution;
	}

	return NULL;
}

void FParticleSystemGeneratorModule::SetDistributionProperties(UDistribution* Distribution, TSharedPtr<FJsonObject> DistributionProperties)
{
	check(Distribution);
	check(CurrentModule);


	/** SETUP THE PROPERTIES HERE */
	// ...
	SetObjectProperties(Distribution, DistributionProperties);


	/* UDistribution doesn't have bIsDirty property, so we need to cast it either to
	 * UDistributionFloat or UDistributionVector
	 */
	if (Distribution->GetClass()->IsChildOf<UDistributionFloat>())
	{
		UDistributionFloat* DistFloat = Cast<UDistributionFloat>(Distribution);
		DistFloat->bIsDirty = true;
	}
	else if (Distribution->GetClass()->IsChildOf<UDistributionVector>())
	{
		UDistributionVector* DistVector = Cast<UDistributionVector>(Distribution);
		DistVector->bIsDirty = true;
	}
}

void FParticleSystemGeneratorModule::AddDefaultModules()
{
	CurrentEmitter->PreEditChange(NULL);
	CurrentLODLevel = CurrentEmitter->GetLODLevel(0);

	UParticleModuleSpawn* SpawnModule = CurrentLODLevel->SpawnModule;
	UDistributionFloatConstant* SpawnRateDistribution = Cast<UDistributionFloatConstant>(SpawnModule->Rate.Distribution);
	if (SpawnRateDistribution != NULL)
	{
		SpawnRateDistribution->Constant = 3.0f;
		SpawnRateDistribution->bIsDirty = true;
	}

	UParticleModuleLifetime* LifetimeModule = NewObject<UParticleModuleLifetime>(CurrentEmitter->GetOuter());
	UDistributionFloatUniform* LifetimeDistribution = Cast<UDistributionFloatUniform>(LifetimeModule->Lifetime.Distribution);
	if (LifetimeDistribution != NULL)
	{
		LifetimeDistribution->Min = 1.0f;
		LifetimeDistribution->Max = 1.0f;
		LifetimeDistribution->bIsDirty = true;
	}
	LifetimeModule->LODValidity = 1;
	CurrentLODLevel->Modules.Add(LifetimeModule);

	// to be continued...

	CurrentEmitter->PostEditChange();
}

void FParticleSystemGeneratorModule::RemoveModules()
{
	ParticleSystem->PreEditChange(NULL);

	CurrentEmitter->GetLODLevel(0)->Modules.Empty();

	CurrentEmitter->UpdateModuleLists();
	CurrentEmitter->PostEditChange();
	ParticleSystem->PostEditChange();
}


#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FParticleSystemGeneratorModule, ParticleSystemGenerator)