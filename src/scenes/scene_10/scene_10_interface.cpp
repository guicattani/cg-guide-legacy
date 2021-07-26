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
Cube\0 \
Sphere\0 \
Octahedron\0 \
Dodecahedron\0 \
Icosahedron\0", 4);
  ImGui::Separator();
  ImGui::Combo("Texture", &g_Scene10->chosen_texture, "UV Checker\0 \
Container\0 \
World\0", 2);
  ImGui::Separator();
  ImGui::Combo("Texture Projection", &g_Scene10->texture_projection, "Spherical\0 \
Cylindrical\0 \
Axis Aligned Bounding Box\0 \
Cubemap\0 \
Texture Coordinates (.obj must have texcoords)\0", 4);

  ImGui::Separator();
  ImGui::Text("Left Camera Pos: %f %f %f", g_Scene10->camera->position.x,
                                           g_Scene10->camera->position.y,
                                           g_Scene10->camera->position.z);
  ImGui::Text("Left Camera Theta: %f", g_Scene10->camera->theta);
  ImGui::Text("Left Camera Phi: %f", g_Scene10->camera->phi);

  ImGui::Checkbox("Use World Coordinates", &g_Scene10->use_world_coordinates);
  ImGui::SliderFloat3("Model Position", (float*) &g_Scene10->model_position, -1.0f, 1.0f);
  ImGui::SliderFloat("Cylinder Height", &g_Scene10->cylinder_height, 0.0f, 5.0f);
  ImGui::SliderFloat("Texture Projection Transparency", &g_Scene10->texture_projection_transparency, 0.0f, 1.0f);

  ImGui::Separator();
  ImGui::Text("Right Camera Pos: %f %f %f", g_Scene10->second_camera->position.x,
                                           g_Scene10->second_camera->position.y,
                                           g_Scene10->second_camera->position.z);
  ImGui::Text("Right Camera Theta: %f", g_Scene10->second_camera->theta);
  ImGui::Text("Right Camera Phi: %f", g_Scene10->second_camera->phi);
}

void InterfaceScene10::ShowText()
{
  ImGui::TextWrapped("This text should automatically wrap on the edge of the window. The current implementation for text wrapping follows simple rules suitable for English and possibly other languages.");
}