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
  ImGui::Text("Left Camera");
  ImGui::SliderFloat("Camera Near Plane", &g_Scene9->camera->nearPlane, -10.0f, 10.0f);
  ImGui::SliderFloat("Camera Far Plane", &g_Scene9->camera->farPlane, -10.0f, 10.0f);

  ImGui::SliderFloat("Camera Field Of View", &g_Scene9->camera->fieldOfView, 0.0f, 3.14f);

  ImGui::Text("Left Camera Pos: %f %f %f", g_Scene9->camera->position.x,
                                           g_Scene9->camera->position.y,
                                           g_Scene9->camera->position.z);
  ImGui::Text("Left Camera Theta: %f", g_Scene9->camera->theta);
  ImGui::Text("Left Camera Phi: %f", g_Scene9->camera->phi);

  ImGui::Separator();
  ImGui::Text("Right Camera");
  ImGui::SliderFloat("Simulate Perspective Slider", &g_Scene9->simulate_perspective_slider, 0.0f, 1.0f);
  ImGui::Checkbox("Follow perspective camera", &g_Scene9->follow_camera);
  ImGui::Checkbox("Freeze Camera in Origin", &g_Scene9->freeze_camera_in_origin);
  ImGui::SameLine();
  ImGui::HelpMarker("Useful to see how the first camera sees, use with ortographic projection, everything you'll see inside the square is what the first camera is rendering");
  ImGui::Checkbox("Use perspective projection", &g_Scene9->second_camera->usePerspectiveProjection);

  ImGui::Text("Right Camera Pos: %f %f %f", g_Scene9->second_camera->position.x,
                                             g_Scene9->second_camera->position.y,
                                             g_Scene9->second_camera->position.z);
  ImGui::Text("Right Camera Theta: %f", g_Scene9->second_camera->theta);
  ImGui::Text("Right Camera Phi: %f", g_Scene9->second_camera->phi);

  ImGui::SliderFloat("Right Camera Near Plane", &g_Scene9->second_camera->nearPlane, -15.0f, 15.0f);
  ImGui::SliderFloat("Right Camera Far Plane", &g_Scene9->second_camera->farPlane, -100.0f, 100.0f);
  ImGui::SliderFloat("Right Camera Field Of View", &g_Scene9->second_camera->fieldOfView, 0.0f, 3.14f);
}

void InterfaceScene9::ShowText() {
  ImGui::TextColored(ImVec4(0.0f,1.0f,1.0f,1.0f), "Drawing your first triangle");
}
