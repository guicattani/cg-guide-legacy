#ifndef CLASS_HEADER_SCENE_GLOBALS
#define CLASS_HEADER_SCENE_GLOBALS
#include "globals_scenes.h"
#endif

#ifndef CLASS_HEADER_INTERFACE
#define CLASS_HEADER_INTERFACE
#include "interface.h"
#endif

void InterfaceScene6::ShowControls()
{
  ImGui::Text("Material");
  ImGui::Checkbox("Use texture", &g_Scene6->useTexture);
  if (ImGui::CollapsingHeader("Texture options", &g_Scene6->useTexture)) {
    ImGui::Checkbox("Use diffuse", &g_Scene6->useDiffuseTexture);
    ImGui::Checkbox("Use specular", &g_Scene6->useSpecularTexture);
  }
  if(!g_Scene6->useTexture) {
    ImGui::ColorEdit3("Material Ambient", (float *)&g_Scene6->material->ambient);
    ImGui::ColorEdit3("Material Specular", (float *)&g_Scene6->material->specular);
    ImGui::ColorEdit3("Material Diffuse", (float *)&g_Scene6->material->diffuse);
  }
  ImGui::SliderFloat("Material Shininess", (float *)&g_Scene6->material->shininess, -1.0f, 100.0f);
  ImGui::SliderFloat("Gourad Specular Strength", (float *)&g_Scene6->gouradSpecularStrength, 0.0f, 3.0f);


  ImGui::Separator();

  ImGui::Text("Light");
  ImGui::SliderFloat3("Light Position", (float *)&g_Scene6->light->position, -5.0f, 5.0f);
  ImGui::ColorEdit3("Light Ambient", (float *)&g_Scene6->light->ambient);
  ImGui::ColorEdit3("Light Diffuse", (float *)&g_Scene6->light->diffuse);
  ImGui::ColorEdit3("Light Specular", (float *)&g_Scene6->light->specular);

  ImGui::Separator();

  ImGui::Text("Camera");
  ImGui::Text("Position: %f %f %f %f", (float) g_Scene6->camera->position[0],
                                       (float) g_Scene6->camera->position[1],
                                       (float) g_Scene6->camera->position[2],
                                       (float) g_Scene6->camera->position[3]);
  ImGui::Text("Theta: %f", (float) g_Scene6->camera->theta);
  ImGui::Text("Phi: %f", (float) g_Scene6->camera->phi);
}

void InterfaceScene6::ShowText() {
  ImGui::TextWrapped("This text should automatically wrap on the edge of the window. The current implementation for text wrapping follows simple rules suitable for English and possibly other languages.");

}
