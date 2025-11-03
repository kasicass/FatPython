#pragma once

#include "FatPythonHeaders.h"

typedef struct 
{
	PyObject_HEAD

	FColor color;
} pyue_FColor;

PyObject *pyue_new_fcolor(FColor color);
pyue_FColor *pyue_is_fcolor(PyObject *obj);

void pyue_init_fvector(PyObject *module);
