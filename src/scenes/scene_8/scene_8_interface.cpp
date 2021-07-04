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
  ImGui::Text("Camera Pos: %f %f %f", g_Scene8->camera->position.x,
                                      g_Scene8->camera->position.y,
                                      g_Scene8->camera->position.z);
  ImGui::Separator();
  ImGui::Text("Second Camera Pos: %f %f %f", g_Scene8->second_camera->position.x,
                                             g_Scene8->second_camera->position.y,
                                             g_Scene8->second_camera->position.z);
}

void InterfaceScene8::ShowText() {
  ImGui::TextColored(ImVec4(0.0f,1.0f,1.0f,1.0f), "Drawing your first triangle");
}
