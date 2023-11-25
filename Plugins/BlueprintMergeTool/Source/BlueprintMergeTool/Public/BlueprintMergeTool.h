// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FToolBarBuilder;
class FMenuBuilder;

class UBlueprint;
class USCS_Node;

class UBlueprintMergeToolSettings;

class FBlueprintMergeToolModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command. */
	void PluginButtonClicked();

	const UBlueprintMergeToolSettings* Settings;

	const FString PathToMergingList = TEXT("C:\\Users\\Oleg\\Desktop\\merge_list.txt");
	const FString PackagePathToMergedBlueprints = TEXT("/Game/MergedTiles/buffer");

	const bool bMakeMeshesTranslucent = true;
	const FString DummyMaterialPackageName = TEXT("/Game/Materials/Transparent");

	const bool bReplaceActorSpawners = true;
	const FString ActorSpawnersPackagePath = TEXT("/Game/MergedTiles/ActorSpawners");

	const FString CopiedComponentPostfix = TEXT("_MERGED");
	
private:

	void RegisterMenus();

	void Main();

	void MergeBlueprints(const FString& FirstBlueprintPackageName, const FString& SecondBlueprintPackageName);

	FString GetAssetName(const FString& PackageName);

	UPackage* GetPackage(const FString& PackageName);

	void AddComponentToRoot(USCS_Node* Node, UBlueprint* Blueprint);

	void CopyComponent(USCS_Node* NodeToCopyFrom, USCS_Node* ParentNode);

	USCS_Node* FindOrCreateParentNode(USCS_Node* RootNode, const FString& ParentNodeName, bool& bHasBeenCreated);

	UActorComponent* GetComponentBySCSName(USimpleConstructionScript* SCS, const FString& SCSVariableName);

	void HideAllComponents(USimpleConstructionScript* SCS);

	void ChangeMaterialsForMeshes(USimpleConstructionScript* SCS);

	void ReplaceActorSpawners(USimpleConstructionScript* SCS);

	/** Returns PackageName of found blueprint, or empty string if not found */
	FString FindMergedActorSpawner(const FString& BlueprintAssetName);

private:
	TSharedPtr<class FUICommandList> PluginCommands;
};
