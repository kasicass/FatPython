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
	FString ContentDir = FPaths::ProjectContentDir();
	FString ProjectScriptsPath = FPaths::Combine(ContentDir, TEXT("Scripts"));
	if (!FPaths::DirectoryExists(ProjectScriptsPath))
	{
		FPlatformFileManager::Get().GetPlatformFile().CreateDirectory(*ProjectScriptsPath);
	}
	UEPyEngine::ScriptsPaths.Add(ProjectScriptsPath);

	FString FatPythonPath = FPaths::Combine(ContentDir, TEXT("../Plugins/FatPython"));
	UEPyEngine::ScriptsPaths.Add(FatPythonPath);

	// start Python VM
	UEPyEngine::Startup();

	// just for test
	// RunString("import unreal_engine\nunreal_engine.log(\"Hello!\")");
	// RunFile("PrintTest.py");
#if 1
	UPythonScript *script = NewObject<UPythonScript>();
	script->ScriptPath = "PrintTest.py";
	//script->FunctionToCall = "print_test";
	script->Run();
	
	script->ScriptPath = "run_tests.py";
	//script->FunctionToCall = "print_test";
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
