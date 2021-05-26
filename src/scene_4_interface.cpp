#ifndef CLASS_HEADER_SCENE_GLOBALS
#define CLASS_HEADER_SCENE_GLOBALS
#include "globals_scenes.h"
#endif

#ifndef CLASS_HEADER_INTERFACE
#define CLASS_HEADER_INTERFACE
#include "interface.h"
#endif

void InterfaceScene4::Show()
{
  ImGui::SliderFloat3("A", (float *)&g_Scene4->a, -3.0f, 3.0f);
  ImGui::SliderFloat3("B", (float *)&g_Scene4->b, -3.0f, 3.0f);
  ImGui::SliderFloat3("C", (float *)&g_Scene4->c, -3.0f, 3.0f);
  ImGui::SliderFloat3("D", (float *)&g_Scene4->d, -3.0f, 3.0f);

  ImGui::Separator();

  ImGui::Checkbox("Hold time", &g_HoldTime);

  ImGui::SliderFloat("Min Range of Graph", (float *)&g_InterfaceScene4->minRange, -3.0f, 3.0f);
  ImGui::SliderFloat("Max Range of Graph", (float *)&g_InterfaceScene4->maxRange, -3.0f, 3.0f);

  ImGui::PlotVar("Current T", g_Scene4->t, g_HoldTime, g_InterfaceScene4->maxRange, g_InterfaceScene4->minRange);
  ImGui::PlotVar("Current X", g_Scene4->x, g_HoldTime, g_InterfaceScene4->maxRange, g_InterfaceScene4->minRange);
  ImGui::PlotVar("Current Y", g_Scene4->y, g_HoldTime, g_InterfaceScene4->maxRange, g_InterfaceScene4->minRange);
  ImGui::PlotVar("Current Z", g_Scene4->z, g_HoldTime, g_InterfaceScene4->maxRange, g_InterfaceScene4->minRange);

  ImGui::Separator();

  // ImGui::Text("Camera");
  // ImGui::Text("Position: %f %f %f %f", (float) g_Scene4->camera->position[0], (float) g_Scene4->camera->position[1], (float) g_Scene4->camera->position[2], (float) g_Scene4->camera->position[3]);

}