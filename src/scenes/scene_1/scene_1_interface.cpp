#ifndef CLASS_HEADER_SCENE_GLOBALS
#define CLASS_HEADER_SCENE_GLOBALS
#include "globals_scenes.h"
#endif

#ifndef CLASS_HEADER_INTERFACE
#define CLASS_HEADER_INTERFACE
#include "interface.h"
#endif

void InterfaceScene1::ShowControls()
{
  ImGui::ColorEdit3("First vertex Color",  (float *)&g_Scene1->first_vertex_color);
  ImGui::ColorEdit3("Second vertex Color", (float *)&g_Scene1->second_vertex_color);
  ImGui::ColorEdit3("Third vertex Color",  (float *)&g_Scene1->third_vertex_color);
}

void InterfaceScene1::ShowText() {
  ImGui::TextColored(ImVec4(0.0f,1.0f,1.0f,1.0f), "Drawing your first triangle");
  ImGui::SameLine(); ImGui::HelpMarker("The TextDisabled color is stored in ImGuiStyle.");
  ImGui::TextWrapped("This text should automatically wrap on the edge of the window.\
 The current implementation for text wrapping follows simple rules\
 suitable for English and possibly other languages.");
}
