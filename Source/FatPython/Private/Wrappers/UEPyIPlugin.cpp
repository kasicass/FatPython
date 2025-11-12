#include "UEPyIPlugin.h"

#if WITH_EDITOR

//
// pyue_IPlugin methods
//

static PyObject *pyue_iplugin_get_name(pyue_IPlugin *self, PyObject *args)
{
	return PyUnicode_FromString(TCHAR_TO_UTF8(*(self->plugin->GetName())));
}

static PyObject *pyue_iplugin_get_base_dir(pyue_IPlugin *self, PyObject *args)
{
	return PyUnicode_FromString(TCHAR_TO_UTF8(*(self->plugin->GetBaseDir())));
}

static PyObject *pyue_iplugin_get_content_dir(pyue_IPlugin *self, PyObject *args)
{
	return PyUnicode_FromString(TCHAR_TO_UTF8(*(self->plugin->GetContentDir())));
}

static PyObject *pyue_iplugin_get_descriptor_file_name(pyue_IPlugin *self, PyObject *args)
{
	return PyUnicode_FromString(TCHAR_TO_UTF8(*(self->plugin->GetDescriptorFileName())));
}

static PyObject *pyue_iplugin_get_mounted_asset_path(pyue_IPlugin *self, PyObject *args)
{
	return PyUnicode_FromString(TCHAR_TO_UTF8(*(self->plugin->GetMountedAssetPath())));
}

static PyObject *pyue_iplugin_can_contain_content(pyue_IPlugin *self, PyObject *args)
{
	if (self->plugin->CanContainContent())
	{
		Py_RETURN_TRUE;
	}
	else
	{
		Py_RETURN_FALSE;
	}
}

static PyObject *pyue_iplugin_is_enabled(pyue_IPlugin *self, PyObject *args)
{
	if (self->plugin->IsEnabled())
	{
		Py_RETURN_TRUE;
	}
	else
	{
		Py_RETURN_FALSE;
	}
}

static PyObject *pyue_iplugin_to_json(pyue_IPlugin *self, PyObject *args)
{
	Py_RETURN_NONE;
}

static PyObject *pyue_iplugin_from_json(pyue_IPlugin *self, PyObject *args)
{
	Py_RETURN_NONE;
}

static PyMethodDef pyue_IPlugin_methods[] = {
	{"get_name", (PyCFunction)pyue_iplugin_get_name, METH_VARARGS, ""},
	{"get_base_dir", (PyCFunction)pyue_iplugin_get_base_dir, METH_VARARGS, ""},
	{"get_content_dir", (PyCFunction)pyue_iplugin_get_content_dir, METH_VARARGS, ""},
	{"get_descriptor_file_name", (PyCFunction)pyue_iplugin_get_descriptor_file_name, METH_VARARGS, ""},
	{"get_mounted_asset_path", (PyCFunction)pyue_iplugin_get_mounted_asset_path, METH_VARARGS, ""},
	{"can_contain_content", (PyCFunction)pyue_iplugin_can_contain_content, METH_VARARGS, ""},
	{"is_enabled", (PyCFunction)pyue_iplugin_is_enabled, METH_VARARGS, ""},
	{"to_json", (PyCFunction)pyue_iplugin_to_json, METH_VARARGS, ""},
	{"from_json", (PyCFunction)pyue_iplugin_from_json, METH_VARARGS, ""},
	{NULL}
};

//
// pyue_IPlugin get/setters
//

static PyObject *pyue_iplugin_get_category(pyue_IPlugin *self, void *closure)
{
	return PyUnicode_FromString(TCHAR_TO_UTF8(*(self->plugin->GetDescriptor().Category)));
}

static PyObject *pyue_iplugin_get_can_contain_content(pyue_IPlugin *self, void *closure)
{
	if (self->plugin->GetDescriptor().bCanContainContent)
	{
		Py_RETURN_TRUE;
	}
	else
	{
		Py_RETURN_FALSE;
	}
}

static PyObject *pyue_iplugin_get_enabled_by_default(pyue_IPlugin *self, void *closure)
{
	if (self->plugin->GetDescriptor().EnabledByDefault == EPluginEnabledByDefault::Enabled)
	{
		Py_RETURN_TRUE;
	}
	else
	{
		Py_RETURN_FALSE;
	}
}

static PyObject *pyue_iplugin_get_installed(pyue_IPlugin *self, void *closure)
{
	if (self->plugin->GetDescriptor().bInstalled)
	{
		Py_RETURN_TRUE;
	}
	else
	{
		Py_RETURN_FALSE;
	}
}

static PyObject *pyue_iplugin_get_is_beta_version(pyue_IPlugin *self, void *closure)
{
	if (self->plugin->GetDescriptor().bIsBetaVersion)
	{
		Py_RETURN_TRUE;
	}
	else
	{
		Py_RETURN_FALSE;
	}
}

static PyObject *pyue_iplugin_get_created_by(pyue_IPlugin *self, void *closure)
{
	return PyUnicode_FromString(TCHAR_TO_UTF8(*(self->plugin->GetDescriptor().CreatedBy)));
}

static PyGetSetDef pyue_IPlugin_getsetters[] = {
	{"category", (getter)pyue_iplugin_get_category, NULL, "", NULL},
	{"can_contain_content", (getter)pyue_iplugin_get_can_contain_content, NULL, "", NULL},
	{"enabled_by_default", (getter)pyue_iplugin_get_enabled_by_default, NULL, "", NULL},
	{"installed", (getter)pyue_iplugin_get_installed, NULL, "", NULL},
	{"is_beta_version", (getter)pyue_iplugin_get_is_beta_version, NULL, "", NULL},
	{"created_by", (getter)pyue_iplugin_get_created_by, NULL, "", NULL},
	{NULL}
};

//
// pyue_IPlugin type
//

static PyObject *pyue_IPlugin_str(pyue_IPlugin *self)
{
	return PyUnicode_FromFormat("<unreal_engine.IPlugin {'name': '%s'}>",
		TCHAR_TO_UTF8(*self->plugin->GetName()));
}

PyTypeObject pyue_IPluginType = {
	PyVarObject_HEAD_INIT(NULL, 0)
	"unreal_engine.IPlugin",
	sizeof(pyue_IPlugin),
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	(reprfunc) pyue_IPlugin_str,
	0,
	0,
	0,
	Py_TPFLAGS_DEFAULT,
	"Unreal Engine Editor IPlugin",
	0,
	0,
	0,
	0,
	0,
	0,
	pyue_IPlugin_methods,
	0,
	pyue_IPlugin_getsetters,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	PyType_GenericNew,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
};

void pyue_init_iplugin(PyObject *module)
{
	if (PyType_Ready(&pyue_IPluginType) < 0)
		return;

	Py_INCREF(&pyue_IPluginType);
	PyModule_AddObject(module, "IPlugin", (PyObject *)&pyue_IPluginType);
}

PyObject *pyue_new_iplugin(IPlugin *plugin)
{
	pyue_IPlugin *ret = (pyue_IPlugin *)PyObject_New(pyue_IPlugin, &pyue_IPluginType);
	ret->plugin = plugin;
	return (PyObject *)ret;
}

#endif
