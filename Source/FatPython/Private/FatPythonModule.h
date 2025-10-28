#pragma once

#include "CoreMinimal.h"
#include "IFatPythonModule.h"

class FFatPythonModule : public IFatPythonModule
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	virtual void RunString(const char *CodeString) override;
	virtual void RunFile(const char *FilePath) override;
	
	TArray<FString> ScriptsPaths;
};
