// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonSerializer.h"

class FToolBarBuilder;
class FMenuBuilder;

class USimpleConstructionScript;
class USCS_Node;
class UBlueprint;
class UMaterialInterface;
class UTexture;
class UBlueprintUncookerSettings;

class FBlueprintUncookerModule : public IModuleInterface
{
private:
	TSharedPtr<FJsonObject> _assetInfo;

	FString DumpsDirectory;
	const UBlueprintUncookerSettings* Settings;

public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command. */
	void PluginButtonClicked();
	
private:

	void RegisterMenus();

	/** For PackageName "/Game/Blueprints/BP_Test" it will return "BP_Test" */
	FString GetAssetName(const FString& PackageName);

	/** Add given SCS_Node to ChildNodes of node with name ParentNodeName */
	bool NodeSetParent(USimpleConstructionScript* SCS, USCS_Node* Node, const FName ParentNodeName);

	/** Create Blueprint asset */
	UBlueprint* CreateBlueprint(const FString& JsonFilePath);  // TSharedPtr<FJsonObject> AssetInfo);

	/** Populate Blueprint asset with components*/
	void AddComponentsToBlueprint(UBlueprint* Blueprint);

	void AddOverrideRecords(UBlueprint* Blueprint);

	USCS_Node* FindInheritedNode(USimpleConstructionScript* SCS, const FString& SCSVariableName);

	/*
	 * If something went wrong during SCS_Node deserialization (failed to get ComponentClass),
	 * create dummy SceneComponent so we won't break components hierarchy
	 */
	USCS_Node* AddDummyComponent(USimpleConstructionScript* SCS, const FString& InternalVariableName, const FString& ParentNodeName);

	/** Set component properties from Json file */
	bool PopulateComponentWithProperties(UActorComponent* ComponentTemplate, TSharedPtr<FJsonObject> Properties);

	void SetPropertyValue(FProperty* InProperty, void* PropertyValuePtr, TSharedPtr<FJsonValue> Value);

	/** Get UObject pointer from given FPackageIndex (valid indices start from -1) */
	UObject* DeserializeObjectProperty(int32 PackageIndex, TSharedPtr<FJsonObject> JsonImportTable);

	/** Get UPackage from given name */
	UPackage* GetPackage(const FString& PackageName);

	/** Cast given FProperty to some child FProperty class */
	void ResolveProperty(FProperty* InProperty, void* PropertyValuePtr);

	void ImportMeshesFromDirectory(const FString& PskDirectory, const FString& AssetPath);

	UStaticMesh* ImportMesh(const FString& MeshName, const FString& PskFullPath, const FString& GamePath);

	void AddMaterials(UStaticMesh* StaticMesh, const FString& MI_AssetPath, const FString& ParentMaterialPackageName);

	UMaterialInterface* CreateMaterialInstance(const FString& MaterialInstancePackageName, const FString& ParentMaterialPackageName);

	UTexture* GetTextureFromDump(const FString& MaterialName, const FString& DefaultTexturesPath);

	UTexture* FindOrImportTexture(const FString& TextureName, const FString& AssetPath, const FString& ExportedTexturesDirectory);

private:
	TSharedPtr<class FUICommandList> PluginCommands;
};
