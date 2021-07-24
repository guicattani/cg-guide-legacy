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
  ImGui::Combo("Model", &g_Scene10->chosen_model, "Cylinder\0 \
Bunny\0 \
Teapot\0 \
Sphere\0 \
Octahedron\0 \
Dodecahedron\0 \
Icosahedron\0", 4);
  ImGui::Combo("Texture", &g_Scene10->chosen_texture, "Container\0 \
World\0", 2);
  ImGui::Combo("Texture Projection", &g_Scene10->texture_projection, "Spherical\0 \
Cylindrical\0 \
Axis Aligned Bounding Box\0 \
Texture Coordinates (.obj must have texcoords)\0", 4);

  ImGui::Separator();
  ImGui::Text("Left Camera Pos: %f %f %f", g_Scene10->camera->position.x,
                                           g_Scene10->camera->position.y,
                                           g_Scene10->camera->position.z);
  ImGui::Text("Left Camera Theta: %f", g_Scene10->camera->theta);
  ImGui::Text("Left Camera Phi: %f", g_Scene10->camera->phi);


  ImGui::Text("cylinder # of texcoords : %d\n", (int)(g_Scene10->sceneModels["cylinder"].attrib.texcoords.size() / 2));
  ImGui::Text("bunny # of texcoords : %d\n", (int)(g_Scene10->sceneModels["bunny"].attrib.texcoords.size() / 2));
  ImGui::Text("teapot # of texcoords : %d\n", (int)(g_Scene10->sceneModels["teapot"].attrib.texcoords.size() / 2));
  ImGui::Text("sphere # of texcoords : %d\n", (int)(g_Scene10->sceneModels["sphere"].attrib.texcoords.size() / 2));
  ImGui::Text("octahedron # of texcoords : %d\n", (int)(g_Scene10->sceneModels["octahedron"].attrib.texcoords.size() / 2));
}

void InterfaceScene10::ShowText()
{
  ImGui::TextWrapped("This text should automatically wrap on the edge of the window. The current implementation for text wrapping follows simple rules suitable for English and possibly other languages.");
}