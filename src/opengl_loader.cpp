#include "opengl_loader.h"

/*
Initialize OpenGL loader
*/
bool InitializeOpenGLLoader()
{
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
  return gl3wInit() != 0;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
  return glewInit() != GLEW_OK;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
  return gladLoadGL() == 0;
#else
  return false; // If you use IMGUI_IMPL_OPENGL_LOADER_CUSTOM, your loader is likely to requires some form of initialization.
#endif
}

/*
Pedimos para utilizar OpenGL versão 3.3 (ou superior)
Pedimos para utilizar o perfil "core", isto é, utilizaremos somente as
funções modernas de OpenGL.
*/
void InitializeOpenGL3()
{
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

/*
Imprimimos no terminal informações sobre a GPU do sistema
*/
void PrintGPUInformation()
{
  const GLubyte *vendor = glGetString(GL_VENDOR);
  const GLubyte *renderer = glGetString(GL_RENDERER);
  const GLubyte *glversion = glGetString(GL_VERSION);
  const GLubyte *glslversion = glGetString(GL_SHADING_LANGUAGE_VERSION);

  printf("GPU: %s, %s, OpenGL %s, GLSL %s\n", vendor, renderer, glversion, glslversion);
}