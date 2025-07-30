// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AW_FPPInteractSystem : ModuleRules
{
	public AW_FPPInteractSystem(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AW_InteractionSystem"
		});
	}
}