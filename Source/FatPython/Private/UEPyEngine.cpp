#include "UEPyEngine.h"
#include "FatPythonHeaders.h"
#include "TimerManager.h"

//
// methods of unreal_engine module
//

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

// unreal_engine.log_warning()
PyObject* pyue_log_warning(PyObject* self, PyObject* args)
{
	PyObject* msg;
	if (!PyArg_ParseTuple(args, "O:log_warning", &msg))
	{
		return NULL;
	}

	PyObject* s = PyObject_Str(msg);
	if (s == NULL)
		return PyErr_Format(PyExc_Exception, "argument can't be casted to string");

	const char *utf8 = PyUnicode_AsUTF8(s);
	UE_LOG(LogFatPython, Warning, TEXT("%s"), UTF8_TO_TCHAR(utf8));
	
	Py_DECREF(s);
	Py_RETURN_NONE;
}

// unreal_engine.log_error()
PyObject* pyue_log_error(PyObject* self, PyObject* args)
{
	PyObject* msg;
	if (!PyArg_ParseTuple(args, "O:log_error", &msg))
	{
		return NULL;
	}

	PyObject* s = PyObject_Str(msg);
	if (s == NULL)
		return PyErr_Format(PyExc_Exception, "argument can't be casted to string");

	const char *utf8 = PyUnicode_AsUTF8(s);
	UE_LOG(LogFatPython, Error, TEXT("%s"), UTF8_TO_TCHAR(utf8));
	
	Py_DECREF(s);
	Py_RETURN_NONE;
}

// unreal_engine.shutdown()
PyObject* pyue_shutdown(PyObject* self, PyObject* args)
{
	RequestEngineExit(TEXT("Shutdown from FatPython"));
	Py_RETURN_NONE;
}

// unreal_engine.get_content_dir()
PyObject* pyue_get_content_dir(PyObject* self, PyObject* args)
{
	return PyUnicode_FromString(TCHAR_TO_UTF8(*FPaths::ProjectContentDir()));
}


//
// unreal_engine module
//

static PyMethodDef unreal_engine_methods[] = {
	{"log", pyue_log, METH_VARARGS, "" },
	{"log_warning", pyue_log_warning, METH_VARARGS, "" },
	{"log_error", pyue_log_error, METH_VARARGS, "" },
	{"shutdown", pyue_shutdown, METH_VARARGS, "" },
	{"get_content_dir", pyue_get_content_dir, METH_VARARGS, "" },
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
// Startup Utils
//

static void UEPy_SetupStdoutStderr(void)
{
	// Redirecting stdout
	char const* code = "import sys\n"
		"import unreal_engine\n"
		"class UnrealEngineOutput:\n"
		"    def __init__(self, logger):\n"
		"        self.logger = logger\n"
		"    def write(self, buf):\n"
		"        self.logger(buf)\n"
		"    def flush(self):\n"
		"        return\n"
		"    def isatty(self):\n"
		"        return False\n"
		"sys.stdout = UnrealEngineOutput(unreal_engine.log)\n"
		"sys.stderr = UnrealEngineOutput(unreal_engine.log_error)\n"
		"\n"
		"class event:\n"
		"    def __init__(self, event_signature):\n"
		"        self.event_signature = event_signature\n"
		"    def __call__(self, f):\n"
		"        f.ue_event = self.event_signature\n"
		"        return f\n"
		"\n"
		"unreal_engine.event = event";
	PyRun_SimpleString(code);
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

	UEPy_SetupStdoutStderr();
}

void UEPyEngine::Shutdown()
{
	UE_LOG(LogFatPython, Log, TEXT("Python VM shutdown"));
	Py_FinalizeEx();
}

void UEPyEngine::RunString(const char *CodeString)
{
	PyRun_SimpleString(CodeString); // auto-call PyErr_Print() when fail
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
