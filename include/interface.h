#ifndef CLASS_ADD_HEADERS
#define CLASS_ADD_HEADERS
#include "headers.h"
#endif

#ifndef CLASS_HEADER_INITIALIZE_GLOBALS
#define CLASS_HEADER_INITIALIZE_GLOBALS
#include "globals.h"
#endif

class Interface
{
private:
  bool m_show_demo_window;
  void Start();
  void SceneLoader();
  void CameraSettings();
  void ModelSettings();
  void DebugSettings();

public:
  Interface(bool show_demo_window);
  void Init(GLFWwindow *window, const char *glsl_version);
  void Show(GLFWwindow *window);
  void LoadFonts();
  void CleanUp();
};

class InterfaceScene2
{
public:
  static void Show();
};
class InterfaceScene3
{
public:
  static void Show();
};

class InterfaceScene4
{
  float maxRange = 1.0f;
  float minRange = -1.0f;

public:
  static void Show();
};

class InterfaceScene5
{
public:
  static void Show();
};