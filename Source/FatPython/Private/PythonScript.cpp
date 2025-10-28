#include "PythonScript.h"
#include "UEPyEngine.h"
#include "FatPythonHeaders.h"

void UPythonScript::Run()
{
	// IFatPythonModule::Get().RunFile(TCHAR_TO_UTF8(*fileName));
}

void UPythonScript::CallSpecificFunctionWithArgs()
{
	PyObject *fn = PyDict_GetItemString(PyEval_GetGlobals(), TCHAR_TO_UTF8(*FunctionToCall));
	if (!fn)
	{
		UE_LOG(LogFatPython, Error, TEXT("Can't find function: %s"), *FunctionToCall);
		return;
	}

	int n = FunctionArgs.Num();
	PyObject *args = n > 0 ? PyTuple_New(n) : nullptr;

	for (int i = 0; i < n; i++)
	{
		PyTuple_SetItem(args, i, PyUnicode_FromString(TCHAR_TO_UTF8(*FunctionArgs[i])));
	}

	PyObject *ret = PyObject_Call(fn, args, nullptr);
	if (!ret)
	{
		PyErr_Print();
	}
	else
	{
		Py_DECREF(ret);
	}

	Py_XDECREF(args);
}
