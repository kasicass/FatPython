// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE5Python.h"
#include "HAL/PlatformFileManager.h"
#include "GenericPlatform/GenericPlatformFile.h"
#include "Misc/Paths.h"

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

	// start Python VM
	Py_InitializeEx(0);
}

void FUE5PythonModule::ShutdownModule()
{
	Py_FinalizeEx();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FUE5PythonModule, UE5Python)