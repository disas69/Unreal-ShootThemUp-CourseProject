// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

using UnrealBuildTool;

public class ShootThemUpTarget : TargetRules
{
	public ShootThemUpTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange(new[] { "ShootThemUp" });
	}
}