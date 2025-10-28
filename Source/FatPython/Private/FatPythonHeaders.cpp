#include "FatPythonHeaders.h"

DEFINE_LOG_CATEGORY(LogFatPython);

void UEPy_LogPythonError(void)
{
	PyObject *type = NULL;
	PyObject *value = NULL;
	PyObject *traceback = NULL;

	PyErr_Fetch(&type, &value, &traceback);
	PyErr_NormalizeException(&type, &value, &traceback);
}
