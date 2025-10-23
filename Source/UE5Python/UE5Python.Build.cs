// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class UE5Python : ModuleRules
{
	// we supports windows platform only
	private string pythonHome = "C:/Python313";
	
	public UE5Python(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
		
		// add python path
		System.Console.WriteLine("Using Python at: " + pythonHome);
		PublicIncludePaths.Add(pythonHome);
		string libPath = GetWindowsPythonLibFile(pythonHome);
		PublicLibraryPaths.Add(Path.GetDirectoryName(libPath));
		PublicAdditionalLibraries.Add(libPath);
	}

	private string GetWindowsPythonLibFile(string basePath)
	{
		for (int i = 14; i >= 0; i--)
		{
			string fileName = string.Format("python3{0}.lib", i);
			string fullPath = Path.Combine(basePath, "libs", fileName);
			if (File.Exists(fullPath))
			{
				return fullPath;
			}
		}
		
		throw new System.Exception("Invalid Python installation, missing .lib files");
	}
}
