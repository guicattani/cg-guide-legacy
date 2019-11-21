#ifndef CLASS_ADD_HEADERS
#define CLASS_ADD_HEADERS
#include "headers.h"
#endif

#ifndef CLASS_HEADER_INITIALIZE_GLOBALS
#define CLASS_HEADER_INITIALIZE_GLOBALS
#include "globals.h"
#endif

#ifndef CLASS_INTERFACE_CLASS_HEADER
#define CLASS_INTERFACE_CLASS_HEADER
class Interface {
  private:
    bool m_show_demo_window;
    void Start();
    void SetInterface(bool show_demo_window);
  public:
    Interface(bool show_demo_window);
    void Init(GLFWwindow *window, const char* glsl_version);
    void Show(GLFWwindow *window);
    void LoadFonts();
    void CleanUp();
};
#endif