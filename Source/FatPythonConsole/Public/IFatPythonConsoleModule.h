#pragma once

#include "Modules/ModuleInterface.h"

class IFatPythonConsoleModule : public IModuleInterface
{
public:
    static IFatPythonConsoleModule& Get()
    {
        return FModuleManager::LoadModuleChecked<IFatPythonConsoleModule>("FatPythonConsoleModule");
    }
};
