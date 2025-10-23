// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE5Python.h"

#define LOCTEXT_NAMESPACE "FUE5PythonModule"

void FUE5PythonModule::StartupModule()
{
	//GConfig->GetString()

	FPaths::ProjectContentDir();

	FString ProjectScriptsPath = FPaths::Combine(FPaths::ProjectContentDir(), UTF8_TO_TCHAR("Scripts"));
	if (!FPaths::DirectoryExists(ProjectScriptsPath))
	{
		FPlatformFileManager::Get().GetPlatformFile().CreateDirectory(*ProjectScriptsPath);
	}
	ScriptsPath.Add(ProjectScriptsPath);
	
}

void FUE5PythonModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FUE5PythonModule, UE5Python)