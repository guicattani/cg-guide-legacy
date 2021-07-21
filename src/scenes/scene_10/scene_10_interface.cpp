#ifndef CLASS_HEADER_SCENE_GLOBALS
#define CLASS_HEADER_SCENE_GLOBALS
#include "globals_scenes.h"
#endif

#ifndef CLASS_HEADER_INTERFACE
#define CLASS_HEADER_INTERFACE
#include "interface.h"
#endif

void InterfaceScene10::ShowControls()
{
  ImGui::Combo("Texture Projection", &g_Scene10->texture_projection, "Spherical\0 \
Cylindrical\0 \
Axis Aligned Bounding Box\0 \
Planar\0", 4);
}

void InterfaceScene10::ShowText()
{
  ImGui::TextWrapped("This text should automatically wrap on the edge of the window. The current implementation for text wrapping follows simple rules suitable for English and possibly other languages.");
}