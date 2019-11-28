#ifndef CLASS_ADD_HEADERS
#define CLASS_ADD_HEADERS
#include "headers.h"
#endif

#ifndef CLASS_HEADER_INITIALIZE_GLOBALS
#define CLASS_HEADER_INITIALIZE_GLOBALS
#include "globals.h"
#endif

#ifndef CLASS_SCENE_CLASS_HEADER
#define CLASS_SCENE_CLASS_HEADER
class Scene {
  public:
    virtual GLuint BuildTriangles() = 0;
};

class Scene_3 : public Scene {
  public:
    virtual GLuint BuildTriangles();
};
#endif