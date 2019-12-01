#ifndef CLASS_HEADER_SCENE
#define CLASS_HEADER_SCENE
#include "scene.h"
#endif

#ifndef CLASS_HEADER_INITIALIZE_GLOBALS
#define CLASS_HEADER_INITIALIZE_GLOBALS
#include "globals.h"
#endif

#ifndef CLASS_HEADER_SHADERS
#define CLASS_HEADER_SHADERS
#include "shaders.h"
#endif

void CreateProgramForScene(int scene);
GLuint LoadScene(int scene);