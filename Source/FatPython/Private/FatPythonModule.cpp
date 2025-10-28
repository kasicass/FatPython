// Copyright Epic Games, Inc. All Rights Reserved.

#include "FatPythonModule.h"
#include "UEPyEngine.h"
#include "HAL/PlatformFileManager.h"
#include "GenericPlatform/GenericPlatformFile.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

#include "PythonScript.h"

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
	UEPyEngine::ScriptsPaths.Add(ProjectScriptsPath);

	// start Python VM
	UEPyEngine::Startup();

	// just for test
	// RunString("import unreal_engine\nunreal_engine.log(\"Hello!\")");
	// RunFile("PrintTest.py");
#if 0
	UPythonScript *script = NewObject<UPythonScript>();
	script->ScriptPath = "PrintTest.py";
	script->FunctionToCall = "print_test";
	script->Run();
#endif
}

void FFatPythonModule::ShutdownModule()
{
	UEPyEngine::Shutdown();
}

void FFatPythonModule::RunString(const char *CodeString)
{
	UEPyEngine::RunString(CodeString);
}

void FFatPythonModule::RunFile(const char *FilePath)
{
	UEPyEngine::RunFile(FilePath);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FFatPythonModule, FatPython)
