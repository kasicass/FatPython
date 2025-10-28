#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"

class IFatPythonModule : public IModuleInterface
{
public:
	static IFatPythonModule& Get()
	{
		return FModuleManager::LoadModuleChecked<IFatPythonModule>("FatPythonModule");
	}
	
public:
	virtual void RunString(const char *CodeString) = 0;
	virtual void RunFile(const char *FilePath) = 0;
};