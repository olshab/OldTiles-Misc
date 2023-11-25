// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UnrealPSKPSA : ModuleRules
{
	public UnrealPSKPSA(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
#if UE_4_24_OR_LATER
		bLegacyPublicIncludePaths = false;
		ShadowVariableWarningLevel = WarningLevel.Off;
#endif    
        PublicDefinitions.Add("WIN32_LEAN_AND_MEAN");

        PublicDependencyModuleNames.AddRange(new[] {
			"Core",
		});

		PrivateDependencyModuleNames.AddRange(new[] {
			"CoreUObject",
			"Engine",
			"Slate",
			"SlateCore",
			"ProceduralMeshComponent",
			"UnrealEd",
			"Projects",
			"MeshDescription",
            "RawMesh",
			"RenderCore",
			"MeshBuilder",
			"MeshUtilitiesCommon", 
			"EditorScriptingUtilities", 
			"GeometricObjects",
		});
	}
}
