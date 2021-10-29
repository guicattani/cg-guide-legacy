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
  ImGui::SliderFloat3("Translation", (float *)&g_Scene3->translation, -2.0f, 2.0f);
  ImGui::SliderFloat("Euler Z Angle", (float *)&g_Scene3->angleZ, -6.28f, 6.28f);
  ImGui::SliderFloat("Euler Y Angle", (float *)&g_Scene3->angleY, -6.28f, 6.28f);
  ImGui::SliderFloat("Euler X Angle", (float *)&g_Scene3->angleX, -6.28f, 6.28f);

  ImGui::Separator();
  ImGui::Text("Camera");
  ImGui::Text("Position: %f %f %f %f", (float)g_Scene3->camera->position[0],
              (float)g_Scene3->camera->position[1],
              (float)g_Scene3->camera->position[2],
              (float)g_Scene3->camera->position[3]);
  ImGui::Text("Theta: %f", (float)g_Scene3->camera->theta);
  ImGui::Text("Phi: %f", (float)g_Scene3->camera->phi);
  ImGui::Checkbox("Use perspective projection", &g_Scene3->camera->usePerspectiveProjection);
  ImGui::Separator();

  glm::vec4 p_model(0.5f, 0.5f, 0.5f, 1.0f);
  glm::vec4 p_world = g_Scene3->inspectable_model * p_model;
  glm::vec4 p_camera = g_Scene3->camera->view * p_world;
  glm::vec4 p_clip = g_Scene3->camera->projection * p_camera;
  glm::vec4 p_ndc = p_clip / p_clip.w;

  ImGuiInputTextFlags inputTextFlags = 0;
  inputTextFlags |= ImGuiInputTextFlags_ReadOnly;
  ImGui::Text("Matrix transformations");

  glm::mat4 inspectable_model = glm::transpose(g_Scene3->inspectable_model);
  glm::mat4 camera_view = glm::transpose(g_Scene3->camera->view);
  glm::mat4 projection = glm::transpose(g_Scene3->camera->projection);

  if (ImGui::CollapsingHeader("Model Matrix", ImGuiTreeNodeFlags_None))
  {
#pragma region Model Matrix
    ImGui::Text("Model Matrix                      ");
    ImGui::SameLine();
    ImGui::Text("Model point                       ");
    ImGui::SameLine();
    ImGui::Text("In World Coordinates");

    ImGui::InputFloat4("", (float *)&inspectable_model[0], 1, inputTextFlags);
    ImGui::SameLine();
    ImGui::Text("   ");
    ImGui::SameLine();
    ImGui::DragFloat("", (float *)&p_model[0]);
    ImGui::SameLine();
    ImGui::Text("   ");
    ImGui::SameLine();
    ImGui::DragFloat("", (float *)&p_world[0]);

    ImGui::InputFloat4("", (float *)&inspectable_model[1], 1, inputTextFlags);
    ImGui::SameLine();
    ImGui::Text("   ");
    ImGui::SameLine();
    ImGui::DragFloat("", (float *)&p_model[1]);
    ImGui::SameLine();
    ImGui::Text("   ");
    ImGui::SameLine();
    ImGui::DragFloat("", (float *)&p_world[1]);

    ImGui::InputFloat4("", (float *)&inspectable_model[2], 1, inputTextFlags);
    ImGui::SameLine();
    ImGui::Text(" * ");
    ImGui::SameLine();
    ImGui::DragFloat("", (float *)&p_model[2]);
    ImGui::SameLine();
    ImGui::Text(" = ");
    ImGui::SameLine();
    ImGui::DragFloat("", (float *)&p_world[2]);

    ImGui::InputFloat4("", (float *)&inspectable_model[3], 1, inputTextFlags);
    ImGui::SameLine();
    ImGui::Text("   ");
    ImGui::SameLine();
    ImGui::DragFloat("", (float *)&p_model[3]);
    ImGui::SameLine();
    ImGui::Text("   ");
    ImGui::SameLine();
    ImGui::DragFloat("", (float *)&p_world[3]);
#pragma endregion
    ImGui::Text("                                                                         |");
    ImGui::Text("                                              .--------------------------'");
    ImGui::Text("                                              V");
  }

  if (ImGui::CollapsingHeader("View Matrix", ImGuiTreeNodeFlags_None))
  {
#pragma region View Matrix
    ImGui::Text("View Matrix                        ");
    ImGui::SameLine();
    ImGui::Text("World                            ");
    ImGui::SameLine();
    ImGui::Text("In Camera Coordinates");
    ImGui::InputFloat4("", (float *)&camera_view[0], 2, inputTextFlags);
    ImGui::SameLine();
    ImGui::Text("   ");
    ImGui::SameLine();
    ImGui::DragFloat("", (float *)&p_world[0]);
    ImGui::SameLine();
    ImGui::Text("   ");
    ImGui::SameLine();
    ImGui::DragFloat("", (float *)&p_camera[0]);

    ImGui::InputFloat4("", (float *)&camera_view[1], 2, inputTextFlags);
    ImGui::SameLine();
    ImGui::Text("   ");
    ImGui::SameLine();
    ImGui::DragFloat("", (float *)&p_world[1]);
    ImGui::SameLine();
    ImGui::Text("   ");
    ImGui::SameLine();
    ImGui::DragFloat("", (float *)&p_camera[1]);

    ImGui::InputFloat4("", (float *)&camera_view[2], 2, inputTextFlags);
    ImGui::SameLine();
    ImGui::Text(" * ");
    ImGui::SameLine();
    ImGui::DragFloat("", (float *)&p_world[2]);
    ImGui::SameLine();
    ImGui::Text(" = ");
    ImGui::SameLine();
    ImGui::DragFloat("", (float *)&p_camera[2]);

    ImGui::InputFloat4("", (float *)&camera_view[3], 2, inputTextFlags);
    ImGui::SameLine();
    ImGui::Text("   ");
    ImGui::SameLine();
    ImGui::DragFloat("", (float *)&p_world[3]);
    ImGui::SameLine();
    ImGui::Text("   ");
    ImGui::SameLine();
    ImGui::DragFloat("", (float *)&p_camera[3]);
#pragma endregion
    ImGui::Text("                                                                         |");
    ImGui::Text("                                              .--------------------------'");
    ImGui::Text("                                              V");
  }

  if (ImGui::CollapsingHeader("Projection Matrix", ImGuiTreeNodeFlags_None))
  {
#pragma region Projection Matrix
    ImGui::Text("Projection Matrix                      ");
    ImGui::SameLine();
    ImGui::Text("Camera                                                             ");
    ImGui::SameLine();
    ImGui::Text("In NDC");
    ImGui::InputFloat4("", (float *)&projection[0], 2, inputTextFlags);
    ImGui::SameLine();
    ImGui::Text("   ");
    ImGui::SameLine();
    ImGui::DragFloat("", (float *)&p_camera[0]);
    ImGui::SameLine();
    ImGui::Text("   ");
    ImGui::SameLine();
    ImGui::DragFloat("", (float *)&p_clip[0]);
    ImGui::SameLine();
    ImGui::Text("      ");
    ImGui::SameLine();
    ImGui::DragFloat("", (float *)&p_ndc[0]);

    ImGui::InputFloat4("", (float *)&projection[1], 2, inputTextFlags);
    ImGui::SameLine();
    ImGui::Text("   ");
    ImGui::SameLine();
    ImGui::DragFloat("", (float *)&p_camera[1]);
    ImGui::SameLine();
    ImGui::Text("   ");
    ImGui::SameLine();
    ImGui::DragFloat("", (float *)&p_clip[1]);
    ImGui::SameLine();
    ImGui::Text("div. w");
    ImGui::SameLine();
    ImGui::DragFloat("", (float *)&p_ndc[1]);

    ImGui::InputFloat4("", (float *)&projection[2], 2, inputTextFlags);
    ImGui::SameLine();
    ImGui::Text(" * ");
    ImGui::SameLine();
    ImGui::DragFloat("", (float *)&p_camera[2]);
    ImGui::SameLine();
    ImGui::Text(" = ");
    ImGui::SameLine();
    ImGui::DragFloat("", (float *)&p_clip[2]);
    ImGui::SameLine();
    ImGui::Text("  ->  ");
    ImGui::SameLine();
    ImGui::DragFloat("", (float *)&p_ndc[2]);

    ImGui::InputFloat4("", (float *)&projection[3], 2, inputTextFlags);
    ImGui::SameLine();
    ImGui::Text("   ");
    ImGui::SameLine();
    ImGui::DragFloat("", (float *)&p_camera[3]);
    ImGui::SameLine();
    ImGui::Text("   ");
    ImGui::SameLine();
    ImGui::DragFloat("", (float *)&p_clip[3]);
    ImGui::SameLine();
    ImGui::Text("      ");
    ImGui::SameLine();
    ImGui::DragFloat("", (float *)&p_ndc[3]);
#pragma endregion
    ImGui::Text("                                                                                                             |");
    ImGui::Text("                                              .--------------------------------------------------------------'");
    ImGui::Text("                                              V");
  }

  if (ImGui::CollapsingHeader("Viewport Matrix", ImGuiTreeNodeFlags_None))
  {
#pragma region Viewport Matrix
    int width, height;
    glfwGetFramebufferSize(g_Window, &width, &height);
    glm::vec2 a = glm::vec2(-1, -1);
    glm::vec2 b = glm::vec2(+1, +1);
    glm::vec2 p = glm::vec2(0, 0);
    glm::vec2 q = glm::vec2(width, height);

    glm::mat4 viewport_mapping = Matrix(
        (q.x - p.x) / (b.x - a.x), 0.0f, 0.0f, (b.x * p.x - a.x * q.x) / (b.x - a.x),
        0.0f, (q.y - p.y) / (b.y - a.y), 0.0f, (b.y * p.y - a.y * q.y) / (b.y - a.y),
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f);

    glm::vec4 pixel_coords = viewport_mapping * p_ndc;
    ImGui::Text("Viewport Matrix                   ");
    ImGui::SameLine();
    ImGui::Text("NDC                                  ");
    ImGui::SameLine();
    ImGui::Text("In Pixel Coordinates");
    ImGui::InputFloat4("", (float *)&viewport_mapping[0], 2, inputTextFlags);
    ImGui::SameLine();
    ImGui::Text("   ");
    ImGui::SameLine();
    ImGui::DragFloat("", (float *)&p_ndc[0]);
    ImGui::SameLine();
    ImGui::Text("   ");
    ImGui::SameLine();
    ImGui::DragFloat("", (float *)&pixel_coords[0]);

    ImGui::InputFloat4("", (float *)&viewport_mapping[1], 2, inputTextFlags);
    ImGui::SameLine();
    ImGui::Text("   ");
    ImGui::SameLine();
    ImGui::DragFloat("", (float *)&p_ndc[1]);
    ImGui::SameLine();
    ImGui::Text("   ");
    ImGui::SameLine();
    ImGui::DragFloat("", (float *)&pixel_coords[1]);

    ImGui::InputFloat4("", (float *)&viewport_mapping[2], 2, inputTextFlags);
    ImGui::SameLine();
    ImGui::Text(" * ");
    ImGui::SameLine();
    ImGui::DragFloat("", (float *)&p_ndc[2]);
    ImGui::SameLine();
    ImGui::Text(" = ");
    ImGui::SameLine();
    ImGui::DragFloat("", (float *)&pixel_coords[2]);

    ImGui::InputFloat4("", (float *)&viewport_mapping[3], 2, inputTextFlags);
    ImGui::SameLine();
    ImGui::Text("   ");
    ImGui::SameLine();
    ImGui::DragFloat("", (float *)&p_ndc[3]);
    ImGui::SameLine();
    ImGui::Text("   ");
    ImGui::SameLine();
    ImGui::DragFloat("", (float *)&pixel_coords[3]);

#pragma endregion
  }
}

void InterfaceScene3::ShowText()
{
  ImGui::TextWrapped("This text should automatically wrap on the edge of the window. The current implementation for text wrapping follows simple rules suitable for English and possibly other languages.");
}
