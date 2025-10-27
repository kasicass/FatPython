#pragma once

#if PLATFORM_WINDOWS
#include <include/pyconfig.h>
#include <include/Python.h>
#else
#warning "Unsupported platform"
#endif


class FScopePythonGIL
{
public:
	FScopePythonGIL()
	{
		state = PyGILState_Ensure();
	}

	~FScopePythonGIL()
	{
		PyGILState_Release(state);
	}

private:
	PyGILState_STATE state;
};
