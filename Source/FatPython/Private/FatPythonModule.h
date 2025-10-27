#pragma once

#include "CoreMinimal.h"
#include "IFatPythonModule.h"

class FFatPythonModule : public IFatPythonModule
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

public:
	virtual void RunString(const char *CodeString) override;
	virtual void RunFile(const char *FilePath) override;
	
	TArray<FString> ScriptsPaths;

private:
	bool IsPythonVMStarted = false;
};