#ifndef CLASS_HEADER_SCENE_GLOBALS
#define CLASS_HEADER_SCENE_GLOBALS
#include "globals_scenes.h"
#endif

#ifndef CLASS_HEADER_INTERFACE
#define CLASS_HEADER_INTERFACE
#include "interface.h"
#endif

void InterfaceScene5::ShowControls()
{
  ImGui::SliderFloat3("Light Position", (float *)&g_Scene5->lightPos, -5.0f, 5.0f);
  ImGui::SliderFloat("Ambient Strength", (float *)&g_Scene5->ambientStrength, 0.0f, 1.0f);
  ImGui::SliderFloat("Diffuse Strength", (float *)&g_Scene5->diffuseStrength, 0.0f, 3.0f);
  ImGui::SliderFloat("Gourad (Vertex based) Specular Strength", (float *)&g_Scene5->gouradSpecularStrength, 0.0f, 3.0f);
  ImGui::SliderFloat("Phong (Fragment based) Specular Strength", (float *)&g_Scene5->phongSpecularStrength, 0.0f, 3.0f);

  ImGui::Text("Camera");
  ImGui::Text("Position: %f %f %f %f", (float) g_Scene5->camera->position[0],
                                       (float) g_Scene5->camera->position[1],
                                       (float) g_Scene5->camera->position[2],
                                       (float) g_Scene5->camera->position[3]);

  ImGui::Text("Theta: %f", (float) g_Scene5->camera->theta);
  ImGui::Text("Phi: %f", (float) g_Scene5->camera->phi);
}

void InterfaceScene5::ShowText() {
  ImGui::TextWrapped("This text should automatically wrap on the edge of the window. The current implementation for text wrapping follows simple rules suitable for English and possibly other languages.");

}
