// Copyright Epic Games, Inc. All Rights Reserved.

#include "BlueprintUncooker.h"
#include "BlueprintUncookerStyle.h"
#include "BlueprintUncookerCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"

#include "UObject/Package.h"
#include "AssetRegistryModule.h"
#include "AssetData.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "Toolkits/AssetEditorManager.h"
#include "Engine/Blueprint.h"
#include "Engine/SimpleConstructionScript.h"
#include "Engine/InheritableComponentHandler.h"
#include "Engine/SCS_Node.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/PointLightComponent.h"
#include "Components/ChildActorComponent.h"
#include "Components/SceneComponent.h"
#include "Misc/FileHelper.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonSerializer.h"
#include "HAL/FileManagerGeneric.h"
#include "PSKXFactory.h"
#include "Factories/MaterialInstanceConstantFactoryNew.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Factories/TextureFactory.h"
#include "BlueprintUncookerSettings.h"

static const FName BlueprintUncookerTabName("BlueprintUncooker");

#define LOCTEXT_NAMESPACE "FBlueprintUncookerModule"

void FBlueprintUncookerModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FBlueprintUncookerStyle::Initialize();
	FBlueprintUncookerStyle::ReloadTextures();

	FBlueprintUncookerCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FBlueprintUncookerCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FBlueprintUncookerModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FBlueprintUncookerModule::RegisterMenus));
}

void FBlueprintUncookerModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FBlueprintUncookerStyle::Shutdown();

	FBlueprintUncookerCommands::Unregister();
}

void FBlueprintUncookerModule::PluginButtonClicked()
{
	Settings = UBlueprintUncookerSettings::Get();

	DumpsDirectory = Settings->DumpsDirectory + TEXT("\\Dumps"); 
	FFileManagerGeneric FileManager;

	/** Import all referenced meshes */
	bool bImportMeshes = true;
	if (bImportMeshes)
	{
		FString MeshesDirectory = DumpsDirectory;
		MeshesDirectory.Append(TEXT("\\Meshes"));

		if (FileManager.DirectoryExists(*MeshesDirectory))
			ImportMeshesFromDirectory(MeshesDirectory, Settings->AssetPathForImportedMeshes);
	}

	TArray<FString> BlueprintDumps;
	FileManager.FindFiles(BlueprintDumps, *DumpsDirectory, TEXT("*.json"));
	for (FString& BlueprintDump : BlueprintDumps)
	{
		FString DumpDirectory = DumpsDirectory;
		DumpDirectory.AppendChar(TEXT('\\'));
		DumpDirectory.Append(BlueprintDump);

		UBlueprint* Blueprint = CreateBlueprint(DumpDirectory);
		if (!Blueprint)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to create Blueprint"));
			continue;
		}
		AddComponentsToBlueprint(Blueprint);
		AddOverrideRecords(Blueprint);

		FKismetEditorUtilities::CompileBlueprint(Blueprint);
	}
}

void FBlueprintUncookerModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FBlueprintUncookerCommands::Get().PluginAction, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FBlueprintUncookerCommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}


FString FBlueprintUncookerModule::GetAssetName(const FString& PackageName)
{
	FString AssetName;
	bool SplitSuccess = PackageName.Split(FString(TEXT("/")), nullptr, &AssetName, ESearchCase::CaseSensitive, ESearchDir::FromEnd);

	if (!SplitSuccess)
		UE_LOG(LogTemp, Error, TEXT("GetAssetName failed!"));

	return AssetName;
}

bool FBlueprintUncookerModule::NodeSetParent(USimpleConstructionScript* SCS, USCS_Node* Node, const FName ParentNodeName = TEXT(""))
{
	if (!Node)
		return false;

	if (ParentNodeName.ToString().IsEmpty() || ParentNodeName.IsNone())
	{
		SCS->AddNode(Node);
		return true;
	}

	USCS_Node* NodeInCurrentSCS = SCS->FindSCSNode(ParentNodeName);
	if (NodeInCurrentSCS)  /* If parent node not in any parent classes */
	{
		NodeInCurrentSCS->AddChildNode(Node);
		return true;
	}

	UBlueprintGeneratedClass* ParentClass = nullptr;
	USimpleConstructionScript* CurrentSCS = SCS;
	do
	{
		ParentClass = Cast<UBlueprintGeneratedClass>(CurrentSCS->GetParentClass());
		if (!ParentClass)
		{
			UE_LOG(LogTemp, Error, TEXT("Can't find parent node for %s (cast to parent BP class failed)"), *Node->GetVariableName().ToString());
			return false;
		}
		USimpleConstructionScript* ParentSCS = ParentClass->SimpleConstructionScript;
		CurrentSCS = ParentSCS;

		NodeInCurrentSCS = CurrentSCS->FindSCSNode(ParentNodeName);
		if (NodeInCurrentSCS)
		{
			UE_LOG(LogTemp, Display, TEXT("Parent node %s found in class %s"), *ParentNodeName.ToString(), *ParentClass->GetName());
			SCS->AddNode(Node);
			Node->SetParent(NodeInCurrentSCS);
			return true;
		}

	} while (ParentClass);

	return false;
}

UBlueprint* FBlueprintUncookerModule::CreateBlueprint(const FString& JsonFilePath)
{
	FString JsonContents;
	if (!FFileHelper::LoadFileToString(JsonContents, *JsonFilePath))
	{
		UE_LOG(LogTemp, Error, TEXT("Can't load string from file %s"), *JsonFilePath);
		return nullptr;
	}

	TSharedPtr<FJsonObject> JsonObject;
	if (!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(JsonContents), JsonObject))
	{
		UE_LOG(LogTemp, Error, TEXT("Can't deserialize Json file: %s"), *JsonFilePath);
		return nullptr;
	}

	_assetInfo = JsonObject;

	/** Get info about parent class */
	FString ParentClassPackageName = _assetInfo->GetStringField(TEXT("ParentClassPackage"));
	FString ParentClassName = _assetInfo->GetStringField(TEXT("ParentClass"));

	UPackage* ParentClassPackage = GetPackage(*ParentClassPackageName);
	UClass* ParentClass = FindObjectFast<UClass>(ParentClassPackage, *ParentClassName);

	if (!ParentClassPackage || !ParentClass)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find Parent Class: %s (%s). Using AActor instead"), *ParentClassName, *ParentClassPackageName);
		ParentClass = AActor::StaticClass();
		// return nullptr;
	}

	/** Blueprint asset to create */
	FString BlueprintPackageName = _assetInfo->GetStringField(TEXT("PackageName"));
	FString BlueprintAssetName = GetAssetName(BlueprintPackageName);

	/** Don't create already existing blueprint */
	UPackage* Package = GetPackage(BlueprintPackageName);
	if (Package)
	{
		UE_LOG(LogTemp, Error, TEXT("Blueprint %s already exists"), *BlueprintPackageName);
		return nullptr;
	}

	Package = CreatePackage(*BlueprintPackageName);

	UBlueprint* Blueprint = FKismetEditorUtilities::CreateBlueprint(
		ParentClass,
		Package,
		*BlueprintAssetName,
		EBlueprintType::BPTYPE_Normal,
		UBlueprint::StaticClass(),
		UBlueprintGeneratedClass::StaticClass()
	);
	if (!Blueprint)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create UBlueprint: %s"), *BlueprintAssetName);
		return nullptr;
	}

	FAssetRegistryModule::AssetCreated(Blueprint);
	// FAssetEditorManager::Get().OpenEditorForAsset(Blueprint);
	Package->FullyLoad();
	Package->SetDirtyFlag(true);
	FKismetEditorUtilities::CompileBlueprint(Blueprint);

	return Blueprint;
}

void FBlueprintUncookerModule::AddComponentsToBlueprint(UBlueprint* Blueprint)
{
	const TArray<TSharedPtr<FJsonValue>> Components = _assetInfo->GetArrayField(TEXT("Components"));
	USimpleConstructionScript* SCS = Blueprint->SimpleConstructionScript;

	for (TSharedPtr<FJsonValue> ComponentValue : Components)
	{
		TSharedPtr<FJsonObject> Component = ComponentValue->AsObject();

		FString InternalVariableName = Component->GetStringField(TEXT("InternalVariableName"));
		FString ParentNodeName = Component->GetStringField(TEXT("ParentNodeName"));
		int32 ComponentClassIndex = Component->GetIntegerField(TEXT("ComponentClass"));
		TSharedPtr<FJsonObject> Properties = Component->GetObjectField(TEXT("Properties"));

		/** There is DefaultSceneRoot already when we create blueprint instantiated from AActor */
		if (InternalVariableName.Equals("DefaultSceneRoot"))
		{
			PopulateComponentWithProperties(SCS->FindSCSNode(TEXT("DefaultSceneRoot"))->ComponentTemplate, Properties);
			continue;
		}

		UClass* ComponentClass = Cast<UClass>(DeserializeObjectProperty(ComponentClassIndex, Component));
		if (!ComponentClass)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to get component class for %s. Creating dummy scene instead"), *InternalVariableName);
			USCS_Node* DummyNode = AddDummyComponent(SCS, InternalVariableName, ParentNodeName);
			checkf(DummyNode, TEXT("Failed to create dummy scene node for component \"%s\" (blueprint \"%s\")"), 
				*InternalVariableName, *Blueprint->GetName());

			PopulateComponentWithProperties(DummyNode->ComponentTemplate, Properties);
			continue;
		}

		USCS_Node* Node = SCS->CreateNode(ComponentClass, *InternalVariableName);
		if (!Node)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to create SCS Node %s"), *InternalVariableName);
			continue;
		}

		if (!NodeSetParent(SCS, Node, *ParentNodeName))
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to set parent for Node %s (parent is %s)"), *InternalVariableName, *ParentNodeName);
			continue;
		}

		/** Add properties in ComponentTemplate*/
		PopulateComponentWithProperties(Node->ComponentTemplate, Properties);
	}
}

void FBlueprintUncookerModule::AddOverrideRecords(UBlueprint* Blueprint)
{
	const TArray<TSharedPtr<FJsonValue>> OverrideRecords = _assetInfo->GetArrayField(TEXT("ComponentOverrideRecords"));
	UInheritableComponentHandler* ComponentHandler = Blueprint->GetInheritableComponentHandler(true); // Blueprint->InheritableComponentHandler;
	USimpleConstructionScript* SCS = Blueprint->SimpleConstructionScript;

	for (TSharedPtr<FJsonValue> RecordValue : OverrideRecords)
	{
		TSharedPtr<FJsonObject> Record = RecordValue->AsObject();

		FString SCSVariableName = Record->GetStringField(TEXT("SCSVariableName"));
		int32 ComponentClassIndex = Record->GetIntegerField(TEXT("ComponentClass"));
		TSharedPtr<FJsonObject> Properties = Record->GetObjectField(TEXT("Properties"));
		/*
		UClass* ComponentClass = Cast<UClass>(DeserializeObjectProperty(ComponentClassIndex, Record));
		if (!ComponentClass)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to get component class for %s"), *SCSVariableName);
			continue;
		}
		*/
		USCS_Node* InheritedNode = FindInheritedNode(SCS, SCSVariableName);
		if (!InheritedNode)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to find inherited SCS Node %s"), *SCSVariableName);
			continue;
		}
		
		FComponentKey ComponentKey(InheritedNode);
		//UActorComponent* ComponentTemplate = ComponentHandler->CreateOverridenComponentTemplate(ComponentKey);
		UActorComponent* ComponentTemplate = ComponentHandler->GetOverridenComponentTemplate(ComponentKey);
		if (!ComponentTemplate)
			ComponentTemplate = ComponentHandler->CreateOverridenComponentTemplate(ComponentKey);
		
		/** Add properties in ComponentTemplate*/
		PopulateComponentWithProperties(ComponentTemplate, Properties);
		//PopulateComponentWithProperties(InheritedNode->ComponentTemplate, Properties);
	}
}

USCS_Node* FBlueprintUncookerModule::FindInheritedNode(USimpleConstructionScript* SCS, const FString& SCSVariableName)
{
	UBlueprintGeneratedClass* ParentClass = nullptr;
	USimpleConstructionScript* CurrentSCS = SCS;

	do
	{
		ParentClass = Cast<UBlueprintGeneratedClass>(CurrentSCS->GetParentClass());
		if (!ParentClass)
		{
			UE_LOG(LogTemp, Error, TEXT("Can't find inherited node %s (cast to parent BP class failed)"), *SCSVariableName);
			return nullptr;
		}
		USimpleConstructionScript* ParentSCS = ParentClass->SimpleConstructionScript;
		CurrentSCS = ParentSCS;

		USCS_Node* InheritedNode = CurrentSCS->FindSCSNode(*SCSVariableName);
		if (InheritedNode)
			return InheritedNode;

	} while (ParentClass);

	return nullptr;
}

USCS_Node* FBlueprintUncookerModule::AddDummyComponent(USimpleConstructionScript* SCS, const FString& InternalVariableName, const FString& ParentNodeName)
{
	USCS_Node* DummyNode = SCS->CreateNode(USceneComponent::StaticClass(), *InternalVariableName);

	if (!NodeSetParent(SCS, DummyNode, *ParentNodeName))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to set parent for Node %s (parent is %s)"), *InternalVariableName, *ParentNodeName);
		return nullptr;
	}

	return DummyNode;
}

bool FBlueprintUncookerModule::PopulateComponentWithProperties(UActorComponent* ComponentTemplate, TSharedPtr<FJsonObject> Properties)
{
	TArray<FString> PropertyNames;
	Properties->Values.GetKeys(PropertyNames);

	for (const FString& JsonProperty : PropertyNames)
	{
		FProperty* Property = ComponentTemplate->GetClass()->FindPropertyByName(*JsonProperty);
		if (!Property)
		{
			UE_LOG(LogTemp, Error, TEXT("%s doesn't have property with the name %s"), *ComponentTemplate->GetName(), *JsonProperty);
			continue;
		}

		SetPropertyValue(
			Property,
			Property->ContainerPtrToValuePtr<void>(ComponentTemplate),
			Properties->GetField<EJson::None>(JsonProperty)
		);
	}

	return true;
}

void FBlueprintUncookerModule::SetPropertyValue(FProperty* InProperty, void* PropertyValuePtr, TSharedPtr<FJsonValue> Value)
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
		/*
		 * FByteProperty can possibly be 255-value enumeration variable,
		 * so we should perform this check before FNumericProperty
		*/

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

		UObject* Object = DeserializeObjectProperty(PackageIndex, nullptr);
		if (Object == nullptr)
			UE_LOG(LogTemp, Warning, TEXT("Failed to load object for property %s"), *InProperty->GetName());

		ObjectProperty->SetObjectPropertyValue(PropertyValuePtr, Object);

		return;
	}

	UE_LOG(LogTemp, Error, TEXT("Failed to resolve FProperty type for property %s"), *InProperty->GetName())
}

UObject* FBlueprintUncookerModule::DeserializeObjectProperty(int32 PackageIndex, TSharedPtr<FJsonObject> JsonImportTable)
{
	if (PackageIndex >= 0)
		return nullptr;

	const TArray<TSharedPtr<FJsonValue>> ImportTable = _assetInfo->GetArrayField(TEXT("ImportTable"));
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

	UObject* OuterObject = DeserializeObjectProperty(OuterIndex, JsonImportTable);
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

UPackage* FBlueprintUncookerModule::GetPackage(const FString& PackageName)
{
	UPackage* Package = FindPackage(nullptr, *PackageName);
	if (!Package)
	{
		Package = LoadPackage(nullptr, *PackageName, LOAD_None);
	}

	return Package;
}

void FBlueprintUncookerModule::ResolveProperty(FProperty* InProperty, void* PropertyValuePtr)
{
	if (FArrayProperty* ArrayProperty = CastField<FArrayProperty>(InProperty))
	{
		UE_LOG(LogTemp, Warning, TEXT("ArrayProperty: %s"), *InProperty->GetName());

		FScriptArrayHelper Array(ArrayProperty, PropertyValuePtr);
		FProperty* ElementProperty = ArrayProperty->Inner;

		UE_LOG(LogTemp, Warning, TEXT("Start of array"));
		for (int32 i = 0; i < Array.Num(); i++)
			ResolveProperty(ElementProperty, Array.GetRawPtr(i));

		UE_LOG(LogTemp, Warning, TEXT("End of array"));

		return;
	}

	if (FStructProperty* StructProperty = CastField<FStructProperty>(InProperty))
	{
		UE_LOG(LogTemp, Warning, TEXT("StructProperty: %s"), *InProperty->GetName());
		UScriptStruct* Struct = StructProperty->Struct;

		UE_LOG(LogTemp, Warning, TEXT("Start of struct"));
		for (FProperty* Property = Struct->PropertyLink; Property; Property = Property->PropertyLinkNext)
			ResolveProperty(Property, Property->ContainerPtrToValuePtr<void>(PropertyValuePtr));

		UE_LOG(LogTemp, Warning, TEXT("End of struct"));

		return;
	}

	if (FBoolProperty* BoolProperty = CastField<FBoolProperty>(InProperty))
	{
		UE_LOG(LogTemp, Warning, TEXT("BoolProperty: %s"), *InProperty->GetName());
		return;
	}

	if (FByteProperty* ByteProperty = CastField<FByteProperty>(InProperty))
	{
		UE_LOG(LogTemp, Warning, TEXT("ByteProperty: %s"), *InProperty->GetName());
		return;
	}

	if (FEnumProperty* EnumProperty = CastField<FEnumProperty>(InProperty))
	{
		UE_LOG(LogTemp, Warning, TEXT("EnumProperty: %s"), *InProperty->GetName());
		return;
	}

	if (FNumericProperty* NumericProperty = CastField<FNumericProperty>(InProperty))
	{
		if (NumericProperty->IsFloatingPoint())
		{
			UE_LOG(LogTemp, Warning, TEXT("FloatingPointProperty: %s"), *InProperty->GetName());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("IntegerProperty: %s"), *InProperty->GetName());
		}

		return;
	}

	if (FNameProperty* NameProperty = CastField<FNameProperty>(InProperty))
	{
		UE_LOG(LogTemp, Warning, TEXT("NameProperty: %s"), *InProperty->GetName());
		return;
	}

	if (FStrProperty* StrProperty = CastField<FStrProperty>(InProperty))
	{
		UE_LOG(LogTemp, Warning, TEXT("StrProperty: %s"), *InProperty->GetName());
		return;
	}

	if (FTextProperty* TextProperty = CastField<FTextProperty>(InProperty))
	{
		UE_LOG(LogTemp, Warning, TEXT("TextProperty: %s"), *InProperty->GetName());
		return;
	}

	if (FObjectProperty* ObjectProperty = CastField<FObjectProperty>(InProperty))
	{
		UE_LOG(LogTemp, Warning, TEXT("ObjectProperty: %s"), *InProperty->GetName());
		return;
	}

	UE_LOG(LogTemp, Error, TEXT("Failed to resolve FProperty type for property %s"), *InProperty->GetName())
}

void FBlueprintUncookerModule::ImportMeshesFromDirectory(const FString& PskDirectory, const FString& AssetPath)
{
	FFileManagerGeneric FileManager;
	TArray<FString> PskFiles;
	FileManager.FindFiles(PskFiles, *PskDirectory, TEXT("*.pskx"));

	for (FString& PskFilename : PskFiles)
	{
		FString PskFullPath = PskDirectory;
		PskFullPath.AppendChar(TEXT('\\'));
		PskFullPath.Append(PskFilename);

		FString AssetName;
		PskFilename.Split(TEXT("."), &AssetName, nullptr, ESearchCase::CaseSensitive, ESearchDir::FromEnd);
		checkf(!AssetName.IsEmpty(), TEXT("Failed to get Asset Name from .pskx file: %s"), *PskFilename);

		UStaticMesh* ImportedMesh = ImportMesh(AssetName, PskFullPath, AssetPath);
		
		/** Create Material Instances for that mesh */
		AddMaterials(
			ImportedMesh, 
			Settings->AssetPathForCreatedMaterialInstances, 
			Settings->ParentMaterialForCreatedMaterialInstances
		);
	}
}

UStaticMesh* FBlueprintUncookerModule::ImportMesh(const FString& MeshName, const FString& PskFullPath, const FString& GamePath)
{
	FString PackageName = GamePath;
	PackageName.Append(TEXT("/"));
	PackageName.Append(MeshName);

	/** Don't import the mesh if it already exists in this folder */
	UPackage* Package = GetPackage(PackageName);
	if (Package)
		return nullptr;

	Package = CreatePackage(*PackageName);
	UPSKXFactory* Factory = NewObject<UPSKXFactory>(GetTransientPackage(), FName(NAME_None));

	bool bOperationCancelled = false;
	UObject* ImportedMesh = Factory->ImportObject(
		UStaticMesh::StaticClass(),
		Package,
		*MeshName,
		RF_Public | RF_Standalone,
		PskFullPath,
		TEXT(""),
		bOperationCancelled
	);

	return CastChecked<UStaticMesh>(ImportedMesh);
}

void FBlueprintUncookerModule::AddMaterials(UStaticMesh* StaticMesh, const FString& MI_AssetPath, const FString& ParentMaterialPackageName)
{
	/** First of all, obtain existing instances so we don't need to create them again */
	TMap<FString, FString> ExistingMaterialInstances;

	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	TArray<FAssetData> AssetData;
	FARFilter Filter;
	Filter.ClassNames.Add(UMaterialInstanceConstant::StaticClass()->GetFName());
	Filter.PackagePaths.Add(*Settings->AssetPathToSearchForMaterialInstances);
	Filter.bRecursivePaths = true;
	AssetRegistryModule.Get().GetAssets(Filter, AssetData);

	for (const FAssetData& Asset : AssetData)
		ExistingMaterialInstances.Add(Asset.AssetName.ToString(), Asset.PackageName.ToString());

	TArray<FStaticMaterial> StaticMaterials = StaticMesh->GetStaticMaterials();
	for (int i = 0; i < StaticMaterials.Num(); i++)
	{
		FString* MI_PackageName = ExistingMaterialInstances.Find(StaticMaterials[i].MaterialSlotName.ToString());
		if (MI_PackageName)  // if instance already exists
		{
			UPackage* MatInstPackage = GetPackage(*MI_PackageName);
			UMaterialInterface* MatInst = Cast<UMaterialInterface>(StaticFindObjectFast(
				UMaterialInterface::StaticClass(),
				MatInstPackage,
				*StaticMaterials[i].MaterialSlotName.ToString()
			));

			StaticMesh->SetMaterial(i, MatInst);
		}
		else
		{
			FString MaterialInstancePackageName = MI_AssetPath + TEXT("/") + StaticMaterials[i].MaterialSlotName.ToString();
			StaticMesh->SetMaterial(i, CreateMaterialInstance(MaterialInstancePackageName, ParentMaterialPackageName));
		}
	}
}

UMaterialInterface* FBlueprintUncookerModule::CreateMaterialInstance(const FString& MaterialInstancePackageName, const FString& ParentMaterialPackageName)
{
	FString MaterialName = GetAssetName(MaterialInstancePackageName);
	UTexture* DiffuseTexture = GetTextureFromDump(MaterialName, Settings->AssetPathForImportedTextures);

	/** Create MaterialInstanceConstant derived from ParentMaterial */
	UPackage* ParentMaterialPackage = GetPackage(ParentMaterialPackageName);
	UMaterialInterface* ParentMaterial = Cast<UMaterialInterface>(StaticFindObjectFast(
		UMaterialInterface::StaticClass(), 
		ParentMaterialPackage,
		*GetAssetName(ParentMaterialPackageName)
	));

	UPackage* Package = CreatePackage(*MaterialInstancePackageName);
	UMaterialInstanceConstantFactoryNew* Factory = NewObject<UMaterialInstanceConstantFactoryNew>(GetTransientPackage(), FName(NAME_None));
	Factory->InitialParent = ParentMaterial;

	UMaterialInstanceConstant* MatInstance = (UMaterialInstanceConstant*)Factory->FactoryCreateNew(
		UMaterialInstanceConstant::StaticClass(),
		Package,
		*MaterialName,
		RF_Standalone | RF_Public,
		nullptr,
		nullptr
	);

	if (MatInstance)
	{
		// FadeDistance
		MatInstance->SetScalarParameterValueEditorOnly(FMaterialParameterInfo(TEXT("018_FadeRadiusDistance")), 18000.f);

		// Diffuse Texture
		if (DiffuseTexture == NULL)
		{
			UPackage* DiffuseTexturePackage = GetPackage(Settings->DefaultDiffuseTexturePackageName);
			DiffuseTexture = Cast<UTexture>(StaticFindObjectFast(UTexture::StaticClass(), DiffuseTexturePackage, TEXT("Diffuse")));
		}
		MatInstance->SetTextureParameterValueEditorOnly(FMaterialParameterInfo(TEXT("Main_BaseColor")), DiffuseTexture);

		// Normal Texture
		UPackage* NormalTexturePackage = GetPackage(Settings->DefaultNormalTexturePackageName);
		UTexture* NormalTexture = Cast<UTexture>(StaticFindObjectFast(UTexture::StaticClass(), NormalTexturePackage, TEXT("FlatNormal")));
		MatInstance->SetTextureParameterValueEditorOnly(FMaterialParameterInfo(TEXT("Main_Normal")), NormalTexture);

		// ORM Texture
		UPackage* ORMTexturePackage = GetPackage(Settings->DefaultORMTexturePackageName);
		UTexture* ORMTexture = Cast<UTexture>(StaticFindObjectFast(UTexture::StaticClass(), ORMTexturePackage, TEXT("Yellow")));
		MatInstance->SetTextureParameterValueEditorOnly(FMaterialParameterInfo(TEXT("Main_ORM")), ORMTexture);

		// Notify the asset registry
		FAssetRegistryModule::AssetCreated(MatInstance);
		MatInstance->MarkPackageDirty();

		return MatInstance;
	}
	
	return nullptr;
}

UTexture* FBlueprintUncookerModule::GetTextureFromDump(const FString& MaterialName, const FString& DefaultTexturesPath)
{
	FString MaterialDumpsDirectory = DumpsDirectory + TEXT("\\Materials");
	FFileManagerGeneric FileManager;

	if (!FileManager.DirectoryExists(*MaterialDumpsDirectory))
		return nullptr;

	FString MaterialDumpFile = MaterialDumpsDirectory + TEXT("\\") + MaterialName + TEXT(".txt");
	//checkf(FileManager.FileExists(*MaterialDumpFile), TEXT("Failed to find dump file for material %s"), *MaterialName);
	if (!FileManager.FileExists(*MaterialDumpFile))
	{
		// If dump file doesn't exist, then it is just Material, not MaterialInstanceConstant
		// Then we are gonna create material instance with default white basecolor texture
		return NULL;
	}

	FString DiffuseTexturesFile;
	if (!FFileHelper::LoadFileToString(DiffuseTexturesFile, *MaterialDumpFile))
	{
		UE_LOG(LogTemp, Error, TEXT("Can't load string from file %s"), *MaterialDumpFile);
		return nullptr;
	}

	TArray<FString> DiffuseTextures;
	DiffuseTexturesFile.ParseIntoArrayLines(DiffuseTextures, true);

	if (DiffuseTextures.Num() == 0)
		return nullptr;

	/** Assuming first texture is Main_BaseColor */
	const FString TextureName = DiffuseTextures[0];
	UTexture* DiffuseTexture = FindOrImportTexture(
		TextureName,
		*DefaultTexturesPath,
		DumpsDirectory + TEXT("\\Textures")
	);

	return DiffuseTexture;
}

UTexture* FBlueprintUncookerModule::FindOrImportTexture(const FString& TextureName, const FString& AssetPath, const FString& ExportedTexturesDirectory)
{	
	if (TextureName.StartsWith(TEXT("/Game"), ESearchCase::CaseSensitive))
	{
		UPackage* ExistingPackage = GetPackage(TextureName);
		FString AssetName = GetAssetName(TextureName);
		UTexture* ExistingTexture = Cast<UTexture>(StaticFindObjectFast(UTexture::StaticClass(), ExistingPackage, *AssetName));

		return ExistingTexture;
	}

	/** Import texture from dumps directory */
	const FString TextureFilePath = ExportedTexturesDirectory + TEXT("\\") + TextureName + TEXT(".png");

	FString PackageName = AssetPath + TEXT("/") + TextureName;
	UPackage* TexturePackage = NULL;

	// Check if we have already imported that texture
	TexturePackage = GetPackage(PackageName);
	if (TexturePackage != NULL)
	{
		UTexture* ExistingTexture = Cast<UTexture>(StaticFindObjectFast(UTexture::StaticClass(), TexturePackage, *TextureName));
		checkf(ExistingTexture != NULL, TEXT("There is package %s already but it's not a UTexture"), *PackageName);

		return ExistingTexture;
	}

	TArray<uint8> DataBinary;
	FFileHelper::LoadFileToArray(DataBinary, *TextureFilePath);

	TexturePackage = CreatePackage(*PackageName);
	UTexture* ImportedTexture = NULL;

	if (DataBinary.Num() > 0)
	{
		const uint8* PtrTexture = DataBinary.GetData();
		UTextureFactory* TextureFact = NewObject<UTextureFactory>();
		TextureFact->AddToRoot();

		ImportedTexture = (UTexture*)TextureFact->FactoryCreateBinary(
			UTexture2D::StaticClass(), 
			TexturePackage,
			*TextureName,
			RF_Standalone | RF_Public, 
			NULL, 
			TEXT("png"),
			PtrTexture, 
			PtrTexture + DataBinary.Num(), 
			NULL);

		if (ImportedTexture != NULL)
		{
			// Notify the asset registry
			FAssetRegistryModule::AssetCreated(ImportedTexture);

			// Set the dirty flag so this package will get saved later
			TexturePackage->SetDirtyFlag(true);
		}
		TextureFact->RemoveFromRoot();

		return ImportedTexture;
	}

	return nullptr;
}


#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FBlueprintUncookerModule, BlueprintUncooker)
