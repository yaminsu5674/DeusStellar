// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DeusStellar2 : ModuleRules
{
	public DeusStellar2(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG" });
	}
}
