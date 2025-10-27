#pragma once

#include "CoreMinimal.h"
#include "IFatPythonModule.h"

class FFatPythonModule : public IFatPythonModule
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

public:
	TArray<FString> ScriptsPath;

private:
	bool IsPythonVMStarted = false;
};