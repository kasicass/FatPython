#include "UEPyEngine.h"
#include "FatPythonHeaders.h"
#include "TimerManager.h"

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

TArray<FString> UEPyEngine::ScriptsPaths;

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

void UEPyEngine::RunString(const char *CodeString)
{
	int ret = PyRun_SimpleString(CodeString);
	if (ret != 0)
	{
		if (PyErr_ExceptionMatches(PyExc_SystemExit))
		{
			PyErr_Clear();
		}
		else
		{
			// TODO
			// FatPy_LogError();
			UE_LOG(LogFatPython, Log, TEXT("RunString() Fail!"));
			PyErr_Clear();
		}
	}
}

void UEPyEngine::RunFile(const char *FilePath)
{
	FScopePythonGIL gil;

	// find .py file
	FString OriginalFilePath = UTF8_TO_TCHAR(FilePath);
	FString FullPath = OriginalFilePath;
	bool FoundFile = false;
	if (!FPaths::FileExists(OriginalFilePath))
	{
		for (FString Prefix : ScriptsPaths)
		{
			FullPath = FPaths::Combine(Prefix, OriginalFilePath);
			if (FPaths::FileExists(FullPath))
			{
				FoundFile = true;
				break;
			}
		}
	}
	else
	{
		FoundFile = true;
	}

	if (!FoundFile)
	{
		UE_LOG(LogFatPython, Error, TEXT("RunFile(): Unable to find file: %s"), *OriginalFilePath);
		return;
	}

	// read file content
	FString FileContent;
	if (!FFileHelper::LoadFileToString(FileContent, *FullPath))
	{
		UE_LOG(LogFatPython, Error, TEXT("RunFile(): Can't read file: %s"), *OriginalFilePath);
		return;
	}
	
	RunString(TCHAR_TO_ANSI(*FileContent));
}
