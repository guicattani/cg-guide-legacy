#ifndef CLASS_HEADER_SCENE_GLOBALS
#define CLASS_HEADER_SCENE_GLOBALS
#include "globals_scenes.h"
#endif

#ifndef CLASS_HEADER_INTERFACE
#define CLASS_HEADER_INTERFACE
#include "interface.h"
#endif

void InterfaceScene7::Show()
{
  ImGui::Text("Material");
  ImGui::Checkbox("Use texture", &g_Scene7->useTexture);
  if (ImGui::CollapsingHeader("Texture options", &g_Scene7->useTexture)) {
    ImGui::Checkbox("Use diffuse", &g_Scene7->useDiffuseTexture);
    ImGui::Checkbox("Use specular", &g_Scene7->useSpecularTexture);
  }
  if(!g_Scene7->useTexture) {
    ImGui::ColorEdit3("Material Ambient", (float *)&g_Scene7->material->ambient);
    ImGui::ColorEdit3("Material Specular", (float *)&g_Scene7->material->specular);
    ImGui::ColorEdit3("Material Diffuse", (float *)&g_Scene7->material->diffuse);
  }
  ImGui::SliderFloat("Material Shininess", (float *)&g_Scene7->material->shininess, -1.0f, 100.0f);
  ImGui::SliderFloat("Gourad Specular Strength", (float *)&g_Scene7->gouradSpecularStrength, 0.0f, 3.0f);


  ImGui::Separator();

  ImGui::Text("Directional Light");
  ImGui::Checkbox("Directional Light On", &g_Scene7->directionalLightOn);
  ImGui::SliderFloat3("Directional Light Direction", (float *)&g_Scene7->directional_light->direction, -5.0f, 5.0f);
  ImGui::ColorEdit3("Directional Light Ambient", (float *)&g_Scene7->directional_light->ambient);
  ImGui::ColorEdit3("Directional Light Diffuse", (float *)&g_Scene7->directional_light->diffuse);
  ImGui::ColorEdit3("Directional Light Specular", (float *)&g_Scene7->directional_light->specular);

  ImGui::Separator();

  ImGui::Text("Point Light");
  ImGui::Checkbox("Point Light On", &g_Scene7->pointLightOn);
  ImGui::SliderFloat3("Point Light Direction", (float *)&g_Scene7->point_light->position, -5.0f, 5.0f);
  ImGui::ColorEdit3("Point Light Ambient",     (float *)&g_Scene7->point_light->ambient);
  ImGui::ColorEdit3("Point Light Diffuse",     (float *)&g_Scene7->point_light->diffuse);
  ImGui::ColorEdit3("Point Light Specular",    (float *)&g_Scene7->point_light->specular);

  ImGui::Text("Point Light Attenuation");
  ImGui::SliderFloat("Point Light Constant", (float *)&g_Scene7->point_light->constant, 0.0f, 3.0f);
  ImGui::SliderFloat("Point Light Linear",   (float *)&g_Scene7->point_light->linear, 0.0f, 1.0f);
  ImGui::SliderFloat("Point Light Quadratic",(float *)&g_Scene7->point_light->quadratic, 0.0f, 1.0f);


  ImGui::Separator();

  ImGui::Text("Camera");
  ImGui::Text("Position: %f %f %f %f", (float) g_Scene7->camera->position[0],
                                       (float) g_Scene7->camera->position[1],
                                       (float) g_Scene7->camera->position[2],
                                       (float) g_Scene7->camera->position[3]);
  ImGui::Text("Theta: %f", (float) g_Scene7->camera->theta);
  ImGui::Text("Phi: %f", (float) g_Scene7->camera->phi);
}