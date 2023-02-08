// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Toy : ModuleRules
{
	public Toy(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.Add(ModuleDirectory);
			
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
		});
			
		
		PrivateDependencyModuleNames.AddRange(new string[]{
			"CoreUObject",
			"Engine",
			"Slate",
			"SlateCore",
			"EditorStyle",
			"Game",
			"Projects",
			"GameplayDebugger",
			"PropertyEditor",
			"MainFrame",
			"DesktopPlatform",
			"UnrealEd",
			"AdvancedPreviewScene",
			"InputCore",
			"AssetTools"
		});
		
		
	}
}
