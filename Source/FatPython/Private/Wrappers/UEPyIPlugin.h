#pragma once

#if WITH_EDITOR

#include "FatPythonHeaders.h"
#include "Interfaces/IPluginManager.h"

typedef struct
{
	PyObject_HEAD
	IPlugin *plugin;
} pyue_IPlugin;

PyObject *pyue_new_iplugin(IPlugin *plugin);

void pyue_init_iplugin(PyObject *module);

#endif
