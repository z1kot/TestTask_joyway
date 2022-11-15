// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class TestTask_JoyWay : ModuleRules
{
	public TestTask_JoyWay(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });
	}
}
