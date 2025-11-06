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

static PyObject *pyue_fcolor_get_g(pyue_FColor *self, void *closure)
{
	return PyLong_FromLong(self->color.G);
}

static int pyue_fcolor_set_g(pyue_FColor *self, PyObject *value, void *closure)
{
	if (!value || !PyNumber_Check(value))
	{
		PyErr_SetString(PyExc_TypeError, "value is not numeric");
		return -1;
	}

	PyObject *l_value = PyNumber_Long(value);
	self->color.G = PyLong_AsLong(l_value);
	Py_DECREF(l_value);
	return 0;
}

static PyObject *pyue_fcolor_get_b(pyue_FColor *self, void *closure)
{
	return PyLong_FromLong(self->color.B);
}

static int pyue_fcolor_set_b(pyue_FColor *self, PyObject *value, void *closure)
{
	if (!value || !PyNumber_Check(value))
	{
		PyErr_SetString(PyExc_TypeError, "value is not numeric");
		return -1;
	}

	PyObject *l_value = PyNumber_Long(value);
	self->color.B = PyLong_AsLong(l_value);
	Py_DECREF(l_value);
	return 0;
}

static PyObject *pyue_fcolor_get_a(pyue_FColor *self, void *closure)
{
	return PyLong_FromLong(self->color.A);
}

static int pyue_fcolor_set_a(pyue_FColor *self, PyObject *value, void *closure)
{
	if (!value || !PyNumber_Check(value))
	{
		PyErr_SetString(PyExc_TypeError, "value is not numeric");
		return -1;
	}

	PyObject *l_value = PyNumber_Long(value);
	self->color.A = PyLong_AsLong(l_value);
	Py_DECREF(l_value);
	return 0;
}

static PyGetSetDef pyue_FColor_getsetters[] = {
	{"r", (getter)pyue_fcolor_get_r, (setter)pyue_fcolor_set_r, "", NULL},
	{"g", (getter)pyue_fcolor_get_g, (setter)pyue_fcolor_set_g, "", NULL},
	{"b", (getter)pyue_fcolor_get_b, (setter)pyue_fcolor_set_b, "", NULL},
	{"a", (getter)pyue_fcolor_get_a, (setter)pyue_fcolor_set_a, "", NULL},
	{ NULL }
};

//
// pyue_FColor number methods
//

static PyObject *pyue_fcolor_nb_add(pyue_FColor *self, PyObject *value)
{
	FColor color = self->color;
	pyue_FColor *right_color = pyue_is_fcolor(value);
	if (right_color)
	{
		color += right_color->color;
	}
	else if (PyNumber_Check(value))
	{
		PyObject *long_value = PyNumber_Long(value);
		long l = PyLong_AsLong(long_value);
		color.R += l;
		color.G += l;
		color.B += l;
		color.A += l;
		Py_DECREF(long_value);
	}

	return pyue_new_fcolor(color);
}

static PyNumberMethods pyue_FColor_number_methods = {
	(binaryfunc)pyue_fcolor_nb_add,
};

//
// pyue_FColor sequence methods
//

static Py_ssize_t pyue_FColor_sq_length(pyue_FColor *self)
{
	return 4;
}

static PyObject *pyue_FColor_sq_item(pyue_FColor *self, Py_ssize_t i)
{
	switch (i)
	{
	case 0: return PyLong_FromLong(self->color.R);
	case 1: return PyLong_FromLong(self->color.G);
	case 2: return PyLong_FromLong(self->color.B);
	case 3: return PyLong_FromLong(self->color.A);
	}

	return PyErr_Format(PyExc_IndexError, "FColor has only 4 items");
}

static PySequenceMethods pyue_FColor_sequence_methods = {
	(lenfunc)pyue_FColor_sq_length,
	0,
	0,
	(ssizeargfunc)pyue_FColor_sq_item,
};

//
// pyue_FColor type
//

static PyObject *pyue_FColor_str(pyue_FColor *self)
{
	return PyUnicode_FromFormat("<unreal_engine.FColor {'r': %d, 'g': %d, 'b': %d, 'a': %d}>",
		self->color.R, self->color.G, self->color.B, self->color.A);
}

static int pyue_FColor_init(pyue_FColor *self, PyObject *args, PyObject *kwargs)
{
	int r = 0;
	int g = 0;
	int b = 0;
	int a = 255;
	if (!PyArg_ParseTuple(args, "|iiii", &r, &g, &b, &a))
		return -1;

	self->color.R = r;
	self->color.G = g;
	self->color.B = b;
	self->color.A = a;
	return 0;
}


PyTypeObject pyue_FColorType = {
	PyVarObject_HEAD_INIT(NULL, 0)
	"unreal_engine.FColor",
	sizeof(pyue_FColor),
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	&pyue_FColor_number_methods,
	&pyue_FColor_sequence_methods,
	0,
	0,
	0,
	(reprfunc) pyue_FColor_str,
	0,
	0,
	0,
	Py_TPFLAGS_DEFAULT,
	"Unreal Engine FColor",
	0,
	0,
	0,
	0,
	0,
	0,
	pyue_FColor_methods,
	0,
	pyue_FColor_getsetters,
	0,
	0,
	0,
	0,
	0,
	(initproc)pyue_FColor_init,
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

static void add_default_color(const char *name, FColor color)
{
	PyObject *obj = pyue_new_fcolor(color);
	PyDict_SetItemString(pyue_FColorType.tp_dict, name, obj);
}

void pyue_init_fcolor(PyObject *module)
{
	if (PyType_Ready(&pyue_FColorType) < 0)
		return;

	Py_INCREF(&pyue_FColorType);
	PyModule_AddObject(module, "FColor", (PyObject *)&pyue_FColorType);

	add_default_color("White", FColor::White);
	add_default_color("Black", FColor::Black);
	add_default_color("Transparent", FColor::Transparent);
	add_default_color("Red", FColor::Red);
	add_default_color("Green", FColor::Green);
	add_default_color("Blue", FColor::Blue);
	add_default_color("Yellow", FColor::Yellow);
	add_default_color("Cyan", FColor::Cyan);
	add_default_color("Green", FColor::Green);
	add_default_color("Magenta", FColor::Magenta);
	add_default_color("Orange", FColor::Orange);
	add_default_color("Purple", FColor::Purple);
	add_default_color("Turquoise", FColor::Turquoise);
	add_default_color("Silver", FColor::Silver);
	add_default_color("Emerald", FColor::Emerald);
}

PyObject *pyue_new_fcolor(FColor color)
{
	pyue_FColor *ret = (pyue_FColor *)PyObject_New(pyue_FColor, &pyue_FColorType);
	ret->color = color;
	return (PyObject *)ret;
}

pyue_FColor *pyue_is_fcolor(PyObject *obj)
{
	if (!PyObject_IsInstance(obj, (PyObject*)&pyue_FColorType))
		return nullptr;

	return (pyue_FColor *)obj;
}
