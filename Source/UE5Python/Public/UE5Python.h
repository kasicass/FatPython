// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

#if PLATFORM_WINDOWS
#include <include/pyconfig.h>
#include <include/Python.h>
#else
#warning "Unsupported platform"
#endif

DECLARE_LOG_CATEGORY_EXTERN(LogUE5Python, Log, All);

class FUE5PythonModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

public:
	TArray<FString> ScriptsPath;

private:
	bool IsPythonVMStarted = false;
};
