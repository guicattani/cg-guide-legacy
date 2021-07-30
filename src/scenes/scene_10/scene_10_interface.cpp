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
  ImGui::Combo("Texture Projection", &g_Scene10->texture_projection, "Spherical\0 \
Cylindrical\0 \
Axis Aligned Bounding Box\0 \
Cubemap\0", 4);

  ImGui::Separator();
  if(g_Scene10->texture_projection != 3) {
    ImGui::Combo("Texture", &g_Scene10->chosen_texture, "UV Checker\0 \
Container\0 \
World\0", 3);
  }

  ImGui::Separator();
  ImGui::SliderFloat("Arrow Distance", &g_Scene10->arrow->distance, -1.0f, 2.0f);

  if(g_Scene10->texture_projection == 1) {
    ImGui::SliderFloat("Arrow Theta", &g_Scene10->arrow->theta, 0.0f, 6.28f);
    ImGui::SliderFloat("Cylinder Look At Height", &g_Scene10->arrow->lookAtHeightCylinder, 0.0f, g_Scene10->arrow->lookAtMaxHeightCylinder + 1.0f);
    ImGui::SliderFloat("Cylinder Height", &g_Scene10->cylinder_height, 0.0f, 5.0f);
  }
  else if(g_Scene10->texture_projection == 2) {
    ImGui::SliderFloat("Arrow X", &g_Scene10->arrow->axisAlignedPosition.x, -3.0f, 3.0f);
    ImGui::SliderFloat("Arrow Y", &g_Scene10->arrow->axisAlignedPosition.y, -3.0f, 3.0f);
  }
  else {
    ImGui::SliderFloat("Arrow Theta", &g_Scene10->arrow->theta, 0.0f, 6.28f);
    ImGui::SliderFloat("Arrow Phi", &g_Scene10->arrow->phi, 0.0f, 6.28f);
  }

  ImGui::Text("Arrow Pos: %f %f %f", g_Scene10->arrow->position.x,
                                          g_Scene10->arrow->position.y,
                                          g_Scene10->arrow->position.z);
  ImGui::Text("Arrow LookAt: %f %f %f", g_Scene10->arrow->lookAt.x,
                                          g_Scene10->arrow->lookAt.y,
                                          g_Scene10->arrow->lookAt.z);


                                           string chosen_model_name;
  // TODO we can use enum for this, can"t we
  switch(g_Scene10->chosen_model) {
    case 0:
      chosen_model_name = "cylinder";
      break;
    case 1:
      chosen_model_name = "bunny";
      break;
    case 2:
      chosen_model_name = "teapot";
      break;
    case 3:
      chosen_model_name = "cube";
      break;
    case 4:
      chosen_model_name = "sphere";
      break;
    case 5:
      chosen_model_name = "octahedron";
      break;
    case 6:
      chosen_model_name = "dodecahedron";
      break;
    case 7:
      chosen_model_name = "icosahedron";
      break;
  }
  if(g_Scene10->texture_projection == 1) {
    ImGui::Text("BBox Center: %f %f %f", g_Scene10->virtualScene[chosen_model_name.c_str()].bbox_center.x,
                                        g_Scene10->arrow->lookAtHeightCylinder,
                                        g_Scene10->virtualScene[chosen_model_name.c_str()].bbox_center.z);
  }else{
    ImGui::Text("BBox Center: %f %f %f", g_Scene10->virtualScene[chosen_model_name.c_str()].bbox_center.x,
                                        g_Scene10->virtualScene[chosen_model_name.c_str()].bbox_center.y,
                                        g_Scene10->virtualScene[chosen_model_name.c_str()].bbox_center.z);
  }
  vec4 arrow_view = normalize(g_Scene10->arrow->lookAt - g_Scene10->arrow->position);
  ImGui::Text("Arrow View: %f %f %f", arrow_view.x,
                                      arrow_view.y,
                                      arrow_view.z);

  ImGui::Separator();
  ImGui::Text("Left Camera Pos: %f %f %f", g_Scene10->camera->position.x,
                                           g_Scene10->camera->position.y,
                                           g_Scene10->camera->position.z);
  ImGui::Text("Left Camera Theta: %f", g_Scene10->camera->theta);
  ImGui::Text("Left Camera Phi: %f", g_Scene10->camera->phi);

  ImGui::Checkbox("Use World Coordinates", &g_Scene10->use_world_coordinates);
  ImGui::SliderFloat3("Model Position", (float*) &g_Scene10->model_position, -1.0f, 1.0f);
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