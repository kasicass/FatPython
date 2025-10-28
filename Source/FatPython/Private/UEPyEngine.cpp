#include "UEPyEngine.h"
#include "FatPythonHeaders.h"

// unreal_engine.log()
PyObject* pyue_log(PyObject* self, PyObject* args)
{
	PyObject* msg;
	if (!PyArg_ParseTuple(args, "O:log", &msg))
	{
		return NULL;
	}

	PyObject* s = PyObject_Str(msg);
	if (s == NULL)
		return PyErr_Format(PyExc_Exception, "argument can't be casted to string");

	const char *utf8 = PyUnicode_AsUTF8(s);
	UE_LOG(LogFatPython, Log, TEXT("%s"), UTF8_TO_TCHAR(utf8));
	
	Py_DECREF(s);
	Py_RETURN_NONE;
}

//
// unreal_engine module
//

static PyMethodDef unreal_engine_methods[] = {
	{"log", pyue_log, METH_VARARGS, "" },
	{NULL, NULL},	
};

PyDoc_STRVAR(unreal_engine_py_doc, "Unreal Engine FatPython module.");
static PyModuleDef unreal_engine_module = {
	PyModuleDef_HEAD_INIT,
	"unreal_engine",
	unreal_engine_py_doc,
	-1,
	unreal_engine_methods,
};
static PyObject* init_unreal_engine(void)
{
	PyObject* mod = PyModule_Create(&unreal_engine_module);
	UE_LOG(LogFatPython, Log, TEXT("UE Module: %p"), mod);
	return mod;
}


//
// Startup & Shutdown
//

void UEPyEngine::Startup()
{
	PyImport_AppendInittab("unreal_engine", &init_unreal_engine);
	
	Py_InitializeEx(0);
	int inited = Py_IsInitialized();
	UE_LOG(LogFatPython, Log, TEXT("Python VM startup: %d"), inited);
}

void UEPyEngine::Shutdown()
{
	UE_LOG(LogFatPython, Log, TEXT("Python VM shutdown"));
	Py_FinalizeEx();
}
