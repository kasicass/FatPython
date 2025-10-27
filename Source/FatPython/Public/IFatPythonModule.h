#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"

#if PLATFORM_WINDOWS
#include <include/pyconfig.h>
#include <include/Python.h>
#else
#warning "Unsupported platform"
#endif

DECLARE_LOG_CATEGORY_EXTERN(LogFatPython, Log, All);

class IFatPythonModule : public IModuleInterface
{
public:
	static IFatPythonModule& Get()
	{
		return FModuleManager::LoadModuleChecked<IFatPythonModule>("FatPythonModule");
	}
};