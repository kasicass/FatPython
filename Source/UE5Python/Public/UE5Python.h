// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

#if PLATFORM_WINDOWS
#include <include/pyconfig.h>
#else
#warning "Unsupported platform"
#endif

class FUE5PythonModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

public:
	TArray<FString> ScriptsPath;
};
