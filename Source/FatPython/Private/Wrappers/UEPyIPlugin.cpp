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

static PyGetSetDef pyue_IPlugin_getsetters[] = {
	{NULL}
};

#endif
