### TODO

* 实现 PythonConsole
* 实现 SPythonLog
* 实现 UPythonScript Asset

### 2025.10.28

* unreal_engine.log()/log_warning()/log_error() done!
* re-direct stdout/stderr to log()/log_error()
* 使用 PyErr_Print() 打印 trackback information
* 如果 PyRun_SimpleString() 失败
  * 其自动调用 PyErr_Print()
  * PyErr_Print() 会调用 PyErr_Clear()
* 给 unreal_engine module 增加 method
  * 修改 UEPyEngine.cpp 中的代码即可

### 2025.10.27

* 把项目更名为 FatPython
* 理解 Python VM 的初始化流程
