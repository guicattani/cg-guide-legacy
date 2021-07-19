#ifndef CLASS_ADD_HEADERS
#define CLASS_ADD_HEADERS
#include "headers.h"
#endif

#ifndef CLASS_HEADER_INITIALIZE_GLOBALS
#define CLASS_HEADER_INITIALIZE_GLOBALS
#include "globals.h"
#endif

namespace ImGuiMarkdown {
  void LinkCallback( ImGui::MarkdownLinkCallbackData data_ );
  inline ImGui::MarkdownImageData ImageCallback( ImGui::MarkdownLinkCallbackData data_ );
  void Markdown( const std::string& markdown_ );
}

class Interface
{
private:
  bool m_show_demo_window;
  void Start();
  void SceneLoader();
  void CameraSettings();
  void ModelSettings();
  void DebugSettings();
  void LoadFonts();
  void Load3DFonts();
  void LoadImages();

public:

  bool show_app_metrics = false;
  bool show_app_style_editor = false;
  bool show_app_about = false;

  glm::vec2 detail_window_constraints = glm::vec2(200.0f, 200.0f);

  Interface(bool show_demo_window);
  void Init(GLFWwindow *window, const char *glsl_version);
  void Show(GLFWwindow *window);
  void CleanUp();
};

class InterfaceScene1
{
public:
  class Part1 {
  public:
    static const glm::vec2 window_constraints;
    static void ShowControls();
    static void ShowText();
  };

  static const glm::vec2 window_constraints;
  static void ShowControls();
  static void ShowText();
};


class InterfaceScene2
{
public:
  static void ShowControls();
  static void ShowText();
};
class InterfaceScene3
{
public:
  static void ShowControls();
  static void ShowText();
};

class InterfaceScene4
{
  float maxRange = 1.0f;
  float minRange = -1.0f;

public:
  class GraphMaxMin {
    float min;
    float max;
  };

  GraphMaxMin x;
  GraphMaxMin y;
  GraphMaxMin z;

  static void ShowControls();
  static void ShowText();
};

class InterfaceScene5
{
public:
  static void ShowControls();
  static void ShowText();
};

class InterfaceScene6
{
public:
  static void ShowControls();
  static void ShowText();
};

class InterfaceScene7
{
public:
  static void ShowControls();
  static void ShowText();
};

class InterfaceScene8
{
public:
  static void ShowControls();
  static void ShowText();
};

class InterfaceScene9
{
public:
  static void ShowControls();
  static void ShowText();
};

class InterfaceScene10
{
public:
  static void ShowControls();
  static void ShowText();
};
