#ifndef CLASS_HEADER_SCENE_GLOBALS
#define CLASS_HEADER_SCENE_GLOBALS
#include "globals_scenes.h"
#endif

#ifndef CLASS_HEADER_INTERFACE
#define CLASS_HEADER_INTERFACE
#include "interface.h"
#endif

void InterfaceScene8::ShowControls()
{

}

void InterfaceScene8::ShowText() {
  ImGui::TextColored(ImVec4(0.0f,1.0f,1.0f,1.0f), "Drawing your first triangle");
}
