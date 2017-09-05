set VC_BIN=C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\bin
set PATH=%VC_BIN%;%PATH%

call "%VC_BIN%\vcvars32.bat"
cl /O1 /MD /D _STATIC_CPPLIB /c /I"%JAVA_HOME%\include" /I"%JAVA_HOME%\include\win32" src\main\c\agent.c
link /dll /opt:REF /out:src\main\resources\win32_x86_32\faketime.dll agent.obj
del agent.obj
del src\main\resources\win32_x86_32\faketime.exp
del src\main\resources\win32_x86_32\faketime.lib

call "%VC_BIN%\amd64\vcvars64.bat"
cl /O1 /MD /D _STATIC_CPPLIB /c /I"%JAVA_HOME%\include" /I"%JAVA_HOME%\include\win32" src\main\c\agent.c
link /dll /opt:REF /out:src\main\resources\win32_x86_64\faketime.dll agent.obj
del agent.obj
del src\main\resources\win32_x86_64\faketime.exp
del src\main\resources\win32_x86_64\faketime.lib
