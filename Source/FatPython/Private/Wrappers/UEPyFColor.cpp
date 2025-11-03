#include "UEPyFColor.h"

//
// pyue_FColor methods
//

static PyObject *pyue_fcolor_to_hex(pyue_FColor *self, PyObject *args)
{
	return PyUnicode_FromString(TCHAR_TO_UTF8(*self->color.ToString()));
}

static PyObject *pyue_fcolor_to_linear(pyue_FColor *self, PyObject *args)
{
	// TODO
	return nullptr;
}

static PyMethodDef pyue_FColor_methods[] = {
	{"to_hex", (PyCFunction)pyue_fcolor_to_hex, METH_VARARGS, ""},
	{"to_linear", (PyCFunction)pyue_fcolor_to_linear, METH_VARARGS, ""},
	{ NULL }
};


//
// pyue_FColor get/setters
//

static PyObject *pyue_fcolor_get_r(pyue_FColor *self, void *closure)
{
	return PyLong_FromLong(self->color.R);
}

static int pyue_fcolor_set_r(pyue_FColor *self, PyObject *value, void *closure)
{
	if (!value || !PyNumber_Check(value))
	{
		PyErr_SetString(PyExc_TypeError, "value is not numeric");
		return -1;
	}

	PyObject *l_value = PyNumber_Long(value);
	self->color.R = PyLong_AsLong(l_value);
	Py_DECREF(l_value);
	return 0;
}
