#ifndef CLASS_HEADER_SCENE_GLOBALS
#define CLASS_HEADER_SCENE_GLOBALS
#include "globals_scenes.h"
#endif

#ifndef CLASS_HEADER_INTERFACE
#define CLASS_HEADER_INTERFACE
#include "interface.h"
#endif

void InterfaceScene3::ShowControls()
{
  ImGui::Text("Camera");
  ImGui::Text("Position: %f %f %f %f", (float) g_Scene3->camera->position[0],
                                       (float) g_Scene3->camera->position[1],
                                       (float) g_Scene3->camera->position[2],
                                       (float) g_Scene3->camera->position[3]);
}

void InterfaceScene3::ShowText() {
  ImGui::TextWrapped("This text should automatically wrap on the edge of the window. The current implementation for text wrapping follows simple rules suitable for English and possibly other languages.");

}
