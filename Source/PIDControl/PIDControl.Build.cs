
using System.IO;
using UnrealBuildTool;

public class PIDControl: ModuleRules
{
	public PIDControl(ReadOnlyTargetRules Target) : base(Target)
	{
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
            new string[] {
                "Core",
                "CoreUObject",
                "Engine"
            });

		PrivateDependencyModuleNames.AddRange(new string[] { });
	}
}
