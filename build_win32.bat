@REM Build for Visual Studio compiler. Run your copy of vcvars32.bat or vcvarsall.bat to setup command-line compiler.
@REM EXAMPLE: D:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat

mkdir Debug
cl /nologo /Zi /MD /I .\src\ /I .\src\imgui\ /I .\libs\glfw\include /I .\libs\gl3w *.cpp .\src\imgui\imgui_impl_glfw.cpp .\src\imgui\imgui_impl_opengl3.cpp .\src\imgui\imgui*.cpp .\libs\gl3w\GL\gl3w.c /FeDebug/example_glfw_opengl3.exe /FoDebug/ /link /LIBPATH:.\libs\glfw\lib-vc2010-32 glfw3.lib opengl32.lib gdi32.lib shell32.lib


