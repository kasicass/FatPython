#include "UEPyFVector.h"

//
// pyue_FVector methods
//

static PyObject* pyue_fvector_length(pyue_FVector *self, PyObject *args)
{
	return PyFloat_FromDouble(self->vec.Size());
}

static PyObject* pyue_fvector_length_squared(pyue_FVector *self, PyObject *args)
{
	return PyFloat_FromDouble(self->vec.SizeSquared());
}

static PyMethodDef pyue_FVector_methods[] = {
	{"length", (PyCFunction)pyue_fvector_length, METH_VARARGS, ""},
	{"length_squared", (PyCFunction)pyue_fvector_length_squared, METH_VARARGS, ""},
	{ NULL },
};


//
// pyue_FVector get/setters
//

static PyObject* pyue_fvector_get_x(pyue_FVector *self, void *closure)
{
	return PyFloat_FromDouble(self->vec.X);
}

static int pyue_fvector_set_x(pyue_FVector *self, PyObject *value,  void *closure)
{
	if (!value || !PyNumber_Check(value))
	{
		PyErr_SetString(PyExc_TypeError, "value is not numeric");
		return -1;
	}

	PyObject *f_value = PyNumber_Float(value);
	self->vec.X = PyFloat_AsDouble(f_value);
	Py_DECREF(f_value);
	return 0;
}

static PyGetSetDef pyue_FVector_getsetters[] = {
	{"x", (getter)pyue_fvector_get_x, (setter)pyue_fvector_set_x, "", NULL},
	{ NULL },
};


//
// pyue_FVector type
//

static PyObject *pyue_FVector_str(pyue_FVector *self)
{
	return PyUnicode_FromFormat("<unreal_engine.FVector {'x': %S, 'y': %S, 'z': %S}>",
		PyFloat_FromDouble(self->vec.X),
		PyFloat_FromDouble(self->vec.Y),
		PyFloat_FromDouble(self->vec.X));
}

PyTypeObject pyue_FVectorType = {
	PyVarObject_HEAD_INIT(NULL, 0)
	"unreal_engine.FVector",
	sizeof(pyue_FVector),
	0,
	0,
	0,
	0,
	0,					
};
