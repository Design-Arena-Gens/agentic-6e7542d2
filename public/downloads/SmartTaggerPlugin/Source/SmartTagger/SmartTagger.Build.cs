using UnrealBuildTool;

public class SmartTagger : ModuleRules
{
    public SmartTagger(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new[] {
                "Core",
                "CoreUObject",
                "Engine"
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new[] {
                "Slate",
                "SlateCore",
                "UnrealEd",
                "EditorSubsystem",
                "AssetTools",
                "Projects"
            }
        );

        if (Target.Type == TargetType.Editor)
        {
            PrivateDependencyModuleNames.Add("LevelEditor");
        }
    }
}
