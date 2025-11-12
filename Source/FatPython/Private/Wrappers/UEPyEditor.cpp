#include "UEPyEditor.h"

#include "UEPyIPlugin.h"
#include "Interfaces/IPluginManager.h"

#if WITH_EDITOR

PyObject *pyue_find_plugin(PyObject *self, PyObject *args)
{
	char *name;
	if (!PyArg_ParseTuple(args, "s:find_plugin", &name))
		return NULL;

	TSharedPtr<IPlugin> plugin = IPluginManager::Get().FindPlugin(UTF8_TO_TCHAR(name));
	if (!plugin.IsValid())
	{
		Py_RETURN_NONE;
	}

	PyObject *ret = pyue_new_iplugin(plugin.Get());
	if (!ret)
		return PyErr_Format(PyExc_Exception, "PyUObject is in invalid state");

	Py_INCREF(ret);
	return ret;
}

#endif
