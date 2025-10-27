// Copyright Epic Games, Inc. All Rights Reserved.

#include "FatPythonModule.h"
#include "PythonHeaders.h"
#include "HAL/PlatformFileManager.h"
#include "GenericPlatform/GenericPlatformFile.h"
#include "Misc/Paths.h"


DEFINE_LOG_CATEGORY(LogFatPython);

#define LOCTEXT_NAMESPACE "FFatPythonModule"

void FFatPythonModule::StartupModule()
{
	//GConfig->GetString()

	// init ScriptsPaths
	FPaths::ProjectContentDir();

	FString ProjectScriptsPath = FPaths::Combine(FPaths::ProjectContentDir(), UTF8_TO_TCHAR("Scripts"));
	if (!FPaths::DirectoryExists(ProjectScriptsPath))
	{
		FPlatformFileManager::Get().GetPlatformFile().CreateDirectory(*ProjectScriptsPath);
	}
	ScriptsPaths.Add(ProjectScriptsPath);

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

void FFatPythonModule::RunString(const char *CodeString)
{
	int ret = PyRun_SimpleString(CodeString);
	if (ret != 0)
	{
		if (PyErr_ExceptionMatches(PyExc_SystemExit))
		{
			PyErr_Clear();
		}
		else
		{
			// TODO
			// FatPy_LogError();
		}
	}
}

void FFatPythonModule::RunFile(const char *FilePath)
{
	FScopePythonGIL gil;

	// find .py file
	FString OriginalFilePath = UTF8_TO_TCHAR(FilePath);
	FString FullPath = OriginalFilePath;
	bool FoundFile = false;
	if (!FPaths::FileExists(OriginalFilePath))
	{
		for (FString Prefix : ScriptsPaths)
		{
			FullPath = FPaths::Combine(Prefix, OriginalFilePath);
			if (FPaths::FileExists(FullPath))
			{
				FoundFile = true;
				break;
			}
		}
	}
	else
	{
		FoundFile = true;
	}

	if (!FoundFile)
	{
		UE_LOG(LogFatPython, Error, TEXT("Unable to find file: %s"), *OriginalFilePath);
		return;
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FFatPythonModule, FatPython)
