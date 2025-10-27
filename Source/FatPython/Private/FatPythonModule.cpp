// Copyright Epic Games, Inc. All Rights Reserved.

#include "FatPythonModule.h"
#include "HAL/PlatformFileManager.h"
#include "GenericPlatform/GenericPlatformFile.h"
#include "Misc/Paths.h"


DEFINE_LOG_CATEGORY(LogFatPython);

#define LOCTEXT_NAMESPACE "FFatPythonModule"

void FFatPythonModule::StartupModule()
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
	IsPythonVMStarted = (bool)Py_IsInitialized();
	UE_LOG(LogFatPython, Log, TEXT("Python VM startup: %d"), IsPythonVMStarted);
	
	if (!IsPythonVMStarted)
		return;
}

void FFatPythonModule::ShutdownModule()
{
	if (IsPythonVMStarted)
	{
		UE_LOG(LogFatPython, Log, TEXT("Python VM shutdown"));
		Py_FinalizeEx();
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FFatPythonModule, UE5Python)
