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
  ImGui::Checkbox("Free Camera Toggle", &g_Scene8->camera->isFreeCamera);
  ImGui::Text("Camera Pos: %f %f %f", g_Scene8->camera->position.x,
                                      g_Scene8->camera->position.y,
                                      g_Scene8->camera->position.z);
  ImGui::SliderFloat("Camera Near Plane", &g_Scene8->camera->nearPlane, -100.0f, 100.0f);
  ImGui::SliderFloat("Camera Far Plane", &g_Scene8->camera->farPlane, -100.0f, 100.0f);

  ImGui::SliderFloat3("Look At", (float *)&g_Scene8->camera->lookAt, -3.0f, 3.0f);
  ImGui::SliderFloat3("Camera Position", (float *)&g_Scene8->camera->position, -10.0f, 10.0f);

  ImGui::Separator();
  ImGui::Text("Second Camera Pos: %f %f %f", g_Scene8->second_camera->position.x,
                                             g_Scene8->second_camera->position.y,
                                             g_Scene8->second_camera->position.z);
  ImGui::SliderFloat("Second Camera Near Plane", &g_Scene8->second_camera->nearPlane, -100.0f, 100.0f);
  ImGui::SliderFloat("Second Camera Far Plane", &g_Scene8->second_camera->farPlane, -100.0f, 100.0f);
}

void InterfaceScene8::ShowText() {
  ImGui::TextColored(ImVec4(0.0f,1.0f,1.0f,1.0f), "Drawing your first triangle");
}
