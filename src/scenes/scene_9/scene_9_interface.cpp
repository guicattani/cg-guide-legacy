#ifndef CLASS_HEADER_SCENE_GLOBALS
#define CLASS_HEADER_SCENE_GLOBALS
#include "globals_scenes.h"
#endif

#ifndef CLASS_HEADER_INTERFACE
#define CLASS_HEADER_INTERFACE
#include "interface.h"
#endif

void InterfaceScene9::ShowControls()
{
  ImGui::Checkbox("Free Camera Toggle", &g_Scene9->camera->isFreeCamera);

  ImGui::SliderFloat("Camera Near Plane", &g_Scene9->camera->nearPlane, -10.0f, 10.0f);
  ImGui::SliderFloat("Camera Far Plane", &g_Scene9->camera->farPlane, -10.0f, 10.0f);

  ImGui::SliderFloat("Camera Field Of View", &g_Scene9->camera->fieldOfView, 0.0f, 3.14f);

  ImGui::Text("Camera Pos: %f %f %f", g_Scene9->camera->position.x,
                                      g_Scene9->camera->position.y,
                                      g_Scene9->camera->position.z);

  ImGui::Separator();
  ImGui::Checkbox("Simulate Perspective", &g_Scene9->simulate_perspective);
  ImGui::Checkbox("Follow perspective camera", &g_Scene9->follow_camera);

  ImGui::Text("Second Camera Pos: %f %f %f", g_Scene9->second_camera->position.x,
                                             g_Scene9->second_camera->position.y,
                                             g_Scene9->second_camera->position.z);

  ImGui::SliderFloat("Second Camera Near Plane", &g_Scene9->second_camera->nearPlane, -10.0f, 10.0f);
  ImGui::SliderFloat("Second Camera Far Plane", &g_Scene9->second_camera->farPlane, -10.0f, 10.0f);
  ImGui::SliderFloat("Second Camera Field Of View", &g_Scene9->second_camera->fieldOfView, 0.0f, 3.14f);
}

void InterfaceScene9::ShowText() {
  ImGui::TextColored(ImVec4(0.0f,1.0f,1.0f,1.0f), "Drawing your first triangle");
}
