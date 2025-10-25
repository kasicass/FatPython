// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

class SWindow;

class FUE5PythonConsoleModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	void CreatePluginWindow();
	void OnWindowClosed(const TSharedRef<SWindow>& Window);
	
	TSharedPtr<SWindow> PluginWindow;
};
