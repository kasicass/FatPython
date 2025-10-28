#pragma once

#include "CoreMinimal.h"

class UEPyEngine
{
public:
	static void Startup(void);
	static void Shutdown(void);

	static void RunString(const char *CodeString);
	static void RunFile(const char *FilePath);
	
	static TArray<FString> ScriptsPaths;
};
