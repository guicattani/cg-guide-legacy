#ifndef CLASS_ADD_HEADERS
#define CLASS_ADD_HEADERS
#include "headers.h"
#endif

#ifndef CLASS_HEADER_INITIALIZE_GLOBALS
#define CLASS_HEADER_INITIALIZE_GLOBALS
#include "globals.h"
#endif

#ifndef CLASS_DEMO_CLASS_HEADER
#define CLASS_DEMO_CLASS_HEADER
class Demo {
  public:
    virtual GLuint BuildTriangles() = 0;
};

class Demo_3 : Demo {
  public:
    GLuint BuildTriangles();
};
#endif