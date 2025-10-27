#pragma once

#include "CoreMinimal.h"
#include "IFatPythonConsoleModule.h"

class SWindow;

class FFatPythonConsoleModule : public IFatPythonConsoleModule
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

private:
    void CreatePluginWindow();
    void OnWindowClosed(const TSharedRef<SWindow>& Window);
	
    TSharedPtr<SWindow> PluginWindow;
};
