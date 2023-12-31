using UnrealBuildTool;

public class Barrel2023 : ModuleRules {
	public Barrel2023(ReadOnlyTargetRules Target) : base(Target) {
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		bLegacyPublicIncludePaths = false;
		ShadowVariableWarningLevel = WarningLevel.Warning;

		PublicDependencyModuleNames.AddRange(new string[] {
			"AIModule",
			"Activation",
			"AkAudio",
			"AnimationBudgetAllocator",
			"AnimationUtilities",
			"BinkMediaPlayer",
			"Competence",
			"Core",
			"CoreUObject",
			"CoreUtilities",
			"Customization",
			"DBDAnimationBudgetAllocator",
			"DBDAudio",
			"DBDInput",
			"DBDSharedTypes",
			"DBDUIViewInterfaces",
			"DBDUIViewsMobile",
			"DBDVideoPlayer",
			"DataTableUtilities",
			"DeadByDaylight",
			"Engine",
			"Foliage",
			"GFXUtilities",
			"GameSessionDS",
			"GameflowNotifications",
			"GameplayTagUtilities",
			"GameplayTags",
			"GameplayUtilities",
			"InputCore",
			"InputUtilities",
			"Interaction",
			"LevelSequence",
			"MediaAssets",
			"MovieScene",
			"NavigationSystem",
			"NetworkUtilities",
			"Niagara",
			"OnlineMessagesUtilities",
			"OnlinePresence",
			"OnlineSubsystemUtils",
			"OnlineTransactions",
			"Paper2D",
			"Penalty",
			"PhysicsCore",
			"PhysicsUtilities",
			"PlatformsProviders",
			"Projectile",
			"QueryService",
			"ReversibleActionSystem",
			"RewardUtilities",
			"ScaleformUI",
			"SignificanceUtilities",
			"Slate",
			"SlateCore",
			"SocialParty",
			"SpecialEventUtilities",
			"StatSystem",
			"SystemUtilities",
			"TimeUtilities",
			"Toasts",
			"UMG",
			"VFXUtilities",
		});
	}
}
