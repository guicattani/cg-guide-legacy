#ifndef CLASS_HEADER_SCENE_GLOBALS
#define CLASS_HEADER_SCENE_GLOBALS
#include "globals_scenes.h"
#endif

#ifndef CLASS_HEADER_INTERFACE
#define CLASS_HEADER_INTERFACE
#include "interface.h"
#endif

void InterfaceScene7::ShowControls()
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


  ImGui::Checkbox("Directional Light On", &g_Scene7->directionalLightOn);
  if (ImGui::CollapsingHeader("Directional Light options", &g_Scene7->directionalLightOn)) {
    ImGui::SliderFloat3("Directional Light Direction", (float *)&g_Scene7->directional_light->direction, -5.0f, 5.0f);
    ImGui::ColorEdit3("Directional Light Ambient", (float *)&g_Scene7->directional_light->ambient);
    ImGui::ColorEdit3("Directional Light Diffuse", (float *)&g_Scene7->directional_light->diffuse);
    ImGui::ColorEdit3("Directional Light Specular", (float *)&g_Scene7->directional_light->specular);
  }

  ImGui::Checkbox("Point Light On", &g_Scene7->pointLightOn);
  if (ImGui::CollapsingHeader("Point Light options", &g_Scene7->pointLightOn)) {
    ImGui::SliderFloat3("Point Light Position", (float *)&g_Scene7->point_light->position, -5.0f, 5.0f);
    ImGui::ColorEdit3("Point Light Ambient",     (float *)&g_Scene7->point_light->ambient);
    ImGui::ColorEdit3("Point Light Diffuse",     (float *)&g_Scene7->point_light->diffuse);
    ImGui::ColorEdit3("Point Light Specular",    (float *)&g_Scene7->point_light->specular);

    ImGui::Text("Point Light Attenuation");
    ImGui::SliderFloat("Point Light Constant", (float *)&g_Scene7->point_light->constant, 0.0f, 3.0f);
    ImGui::SliderFloat("Point Light Linear",   (float *)&g_Scene7->point_light->linear, 0.0f, 1.0f);
    ImGui::SliderFloat("Point Light Quadratic",(float *)&g_Scene7->point_light->quadratic, 0.0f, 1.0f);
  }

  ImGui::Checkbox("Spot Light On", &g_Scene7->spotLightOn);
  if (ImGui::CollapsingHeader("Spot Light options", &g_Scene7->spotLightOn)) {
    ImGui::SliderFloat3("Spot Light Position", (float *)&g_Scene7->spot_light->position, -5.0f, 5.0f);
    ImGui::SliderFloat3("Spot Light Direction", (float *)&g_Scene7->spot_light->direction, -5.0f, 5.0f);
    ImGui::ColorEdit3("Spot Light Ambient",     (float *)&g_Scene7->spot_light->ambient);
    ImGui::ColorEdit3("Spot Light Diffuse",     (float *)&g_Scene7->spot_light->diffuse);
    ImGui::ColorEdit3("Spot Light Specular",    (float *)&g_Scene7->spot_light->specular);

    ImGui::Text("Spot Light Attenuation");
    ImGui::SliderFloat("Spot Light Constant", (float *)&g_Scene7->spot_light->constant, 0.0f, 3.0f);
    ImGui::SliderFloat("Spot Light Linear",   (float *)&g_Scene7->spot_light->linear, 0.0f, 1.0f);
    ImGui::SliderFloat("Spot Light Quadratic",(float *)&g_Scene7->spot_light->quadratic, 0.0f, 1.0f);

    ImGui::Text("Spot Light Cutoff");
    ImGui::SliderFloat("Spot Light Cutoff (Radians)", (float *)&g_Scene7->spot_light->cutOff, 0.0f, 180.0f);
    ImGui::SliderFloat("Spot Light Outer CutOff (Radians)", (float *)&g_Scene7->spot_light->outerCutOff, 0.0f, 180.0f);

  }

  ImGui::Separator();

  ImGui::Text("Camera");
  ImGui::Text("Position: %f %f %f %f", (float) g_Scene7->camera->position[0],
                                       (float) g_Scene7->camera->position[1],
                                       (float) g_Scene7->camera->position[2],
                                       (float) g_Scene7->camera->position[3]);
  ImGui::Text("Theta: %f", (float) g_Scene7->camera->theta);
  ImGui::Text("Phi: %f", (float) g_Scene7->camera->phi);
}

void InterfaceScene7::ShowText() {
  ImGui::TextWrapped("This text should automatically wrap on the edge of the window. The current implementation for text wrapping follows simple rules suitable for English and possibly other languages.");

}
