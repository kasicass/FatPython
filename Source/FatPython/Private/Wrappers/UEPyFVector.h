#pragma once

#include "FatPythonHeaders.h"

typedef struct 
{
	PyObject_HEAD

	FVector vec;
} pyue_FVector;

PyObject *pyue_new_fvector(FVector vec);
pyue_FVector *pyue_is_fvector(pyue_FVector *vec);

void pyue_init_fvector(PyObject *);