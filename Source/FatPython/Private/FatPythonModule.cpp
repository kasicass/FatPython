// Copyright Epic Games, Inc. All Rights Reserved.

#include "FatPythonModule.h"
#include "PythonHeaders.h"
#include "HAL/PlatformFileManager.h"
#include "GenericPlatform/GenericPlatformFile.h"
#include "Misc/Paths.h"


DEFINE_LOG_CATEGORY(LogFatPython);

#define LOCTEXT_NAMESPACE "FFatPythonModule"


PyObject* unreal_engine_log(PyObject* self, PyObject* args)
{
	PyObject* msg;
	if (!PyArg_ParseTuple(args, "O", &msg))
	{
		return NULL;
	}

	PyObject* s = PyObject_Str(msg);
	if (!s)
		return PyErr_Format(PyExc_Exception, "argument can't be casted to string");

	UE_LOG(LogFatPython, Log, TEXT("unreal_engine_log"));
	
	Py_RETURN_NONE;
}

static PyMethodDef unreal_engine_methods[] = {
	{"log", unreal_engine_log, METH_VARARGS, "" },
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

void FFatPythonModule::StartupModule()
{
	//GConfig->GetString()

	// init ScriptsPaths
	FPaths::ProjectContentDir();

	FString ProjectScriptsPath = FPaths::Combine(FPaths::ProjectContentDir(), UTF8_TO_TCHAR("Scripts"));
	if (!FPaths::DirectoryExists(ProjectScriptsPath))
	{
		FPlatformFileManager::Get().GetPlatformFile().CreateDirectory(*ProjectScriptsPath);
	}
	ScriptsPaths.Add(ProjectScriptsPath);

	// start Python VM
	PyImport_AppendInittab("unreal_engine", &init_unreal_engine);
	
	Py_InitializeEx(0);
	IsPythonVMStarted = (bool)Py_IsInitialized();
	UE_LOG(LogFatPython, Log, TEXT("Python VM startup: %d"), IsPythonVMStarted);
	
	if (!IsPythonVMStarted)
		return;

	RunString("import unreal_engine\nunreal_engine.log(\"Hello!\")");
}

void FFatPythonModule::ShutdownModule()
{
	if (IsPythonVMStarted)
	{
		UE_LOG(LogFatPython, Log, TEXT("Python VM shutdown"));
		Py_FinalizeEx();
	}
}

void FFatPythonModule::RunString(const char *CodeString)
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

void FFatPythonModule::RunFile(const char *FilePath)
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
		UE_LOG(LogFatPython, Error, TEXT("Unable to find file: %s"), *OriginalFilePath);
		return;
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FFatPythonModule, FatPython)
