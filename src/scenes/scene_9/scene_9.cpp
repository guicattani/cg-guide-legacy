#ifndef CLASS_HEADER_SCENE
#define CLASS_HEADER_SCENE
#include "scene.h"
#endif

void Scene9::BuildTrianglesAndAddToVirtualScene()
{
  // This is not using EBO
  GLfloat vertices[] = {
      // positions        // normals          //texture coords
      -0.3f,-0.3f,-0.3f,	-1.0f, 0.0f, 0.0f,  0.0f, 0.0f, // Left Side // -X
      -0.3f,-0.3f, 0.3f,	-1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
      -0.3f, 0.3f, 0.3f,	-1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
      -0.3f,-0.3f,-0.3f,	-1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
      -0.3f, 0.3f, 0.3f,	-1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
      -0.3f, 0.3f,-0.3f,	-1.0f, 0.0f, 0.0f,  0.0f, 1.0f, // Left Side

       0.3f, 0.3f,-0.3f,   0.0f, 0.0f,-1.0f,  0.0f, 1.0f, // Back Side // -Z
      -0.3f,-0.3f,-0.3f,   0.0f, 0.0f,-1.0f,  1.0f, 0.0f,
      -0.3f, 0.3f,-0.3f,   0.0f, 0.0f,-1.0f,  1.0f, 1.0f,
       0.3f, 0.3f,-0.3f,   0.0f, 0.0f,-1.0f,  0.0f, 1.0f,
       0.3f,-0.3f,-0.3f,   0.0f, 0.0f,-1.0f,  0.0f, 0.0f,
      -0.3f,-0.3f,-0.3f,   0.0f, 0.0f,-1.0f,  1.0f, 0.0f, // Back Side

       0.3f,-0.3f, 0.3f,   0.0f,-1.0f, 0.0f,  0.0f, 0.0f, // Bottom Side // -Y
      -0.3f,-0.3f,-0.3f,   0.0f,-1.0f, 0.0f,  1.0f, 1.0f,
       0.3f,-0.3f,-0.3f,   0.0f,-1.0f, 0.0f,  1.0f, 0.0f,
       0.3f,-0.3f, 0.3f,   0.0f,-1.0f, 0.0f,  0.0f, 0.0f,
      -0.3f,-0.3f, 0.3f,   0.0f,-1.0f, 0.0f,  0.0f, 1.0f,
      -0.3f,-0.3f,-0.3f,   0.0f,-1.0f, 0.0f,  1.0f, 1.0f, // Bottom Side

      -0.3f, 0.3f, 0.3f,   0.0f, 0.0f, 1.0f,  0.0f, 1.0f, // Front Side // +Z
      -0.3f,-0.3f, 0.3f,   0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
       0.3f,-0.3f, 0.3f,   0.0f, 0.0f, 1.0f,  1.0f, 0.0f,
       0.3f, 0.3f, 0.3f,   0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
      -0.3f, 0.3f, 0.3f,   0.0f, 0.0f, 1.0f,  0.0f, 1.0f,
       0.3f,-0.3f, 0.3f,   0.0f, 0.0f, 1.0f,  1.0f, 0.0f, // Front Side

       0.3f, 0.3f, 0.3f,   1.0f, 0.0f, 0.0f,  0.0f, 1.0f, // Right Side // +X
       0.3f,-0.3f,-0.3f,   1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
       0.3f, 0.3f,-0.3f,   1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
       0.3f,-0.3f,-0.3f,   1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
       0.3f, 0.3f, 0.3f,   1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
       0.3f,-0.3f, 0.3f,   1.0f, 0.0f, 0.0f,  0.0f, 0.0f, // Right Side

       0.3f, 0.3f, 0.3f,   0.0f, 1.0f, 0.0f,  1.0f, 1.0f, // Top Side // +Y
       0.3f, 0.3f,-0.3f,   0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
      -0.3f, 0.3f,-0.3f,   0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
       0.3f, 0.3f, 0.3f,   0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
      -0.3f, 0.3f,-0.3f,   0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
      -0.3f, 0.3f, 0.3f,   0.0f, 1.0f, 0.0f,  1.0f, 0.0f // Top Side
    };

  GLuint VBO_vertices_id, VAO_cube_id;
  glGenVertexArrays(1, &VAO_cube_id);
  glGenBuffers(1, &VBO_vertices_id);

  glBindBuffer(GL_ARRAY_BUFFER, VBO_vertices_id);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindVertexArray(VAO_cube_id);
  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  // normal attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  // texture coordinates attribute
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);

  SceneObject cube;
  cube.name = "Cube";
  cube.first_index = (void *)0;
  cube.num_indices = 36;
  cube.rendering_mode = GL_TRIANGLES;
  cube.vertex_array_object_id = VAO_cube_id;
  this->virtualScene["cube"] = cube;
  glEnableVertexAttribArray(0);

  GLfloat frustum_line_coefficients[36];
  GLuint VAO_frustum_id;
  glGenBuffers(1, &VBO_frustum_lines);
  glGenVertexArrays(1, &VAO_frustum_id);

  glBindVertexArray(VAO_frustum_id);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_frustum_lines);
  glBufferData(GL_ARRAY_BUFFER, sizeof(frustum_line_coefficients), frustum_line_coefficients, GL_DYNAMIC_DRAW);

  GLuint location = 0;
  GLint number_of_dimensions = 4;
  glVertexAttribPointer(location, number_of_dimensions, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(location);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  GLuint indices[] = {
      0,1,
      0,2,
      0,3,
      0,4,

      1,5,
      2,6,
      3,7,
      4,8,

      1,2,
      2,3,
      3,4,
      4,1,

      5,6,
      6,7,
      7,8,
      8,5
  };

  SceneObject frustum_lines;
  frustum_lines.name = "Frustum Lines";
  frustum_lines.first_index = (void *)0;
  frustum_lines.num_indices = 32;
  frustum_lines.rendering_mode = GL_LINES;
  frustum_lines.vertex_array_object_id = VAO_frustum_id;
  this->virtualScene["frustum_lines"] = frustum_lines;

  GLuint indices_id;
  glGenBuffers(1, &indices_id);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_id);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(indices), indices);

  glBindVertexArray(0);
}

void Scene9::DrawCommonModels(bool perspective_transform) {
  glm::mat4 model;
  for(int i = -1; i < 2; i++) {
    for(int j = -1; j < 2; j++) {
      model = Matrix_Translate( (float) i, 0.0f, (float) j);
      shaders["scene"].setMat4("model", model);
      shaders["scene"].setInt("object_id", 0);

      glBindVertexArray(this->virtualScene["cube"].vertex_array_object_id);
      glDrawArrays(this->virtualScene["cube"].rendering_mode, 0, this->virtualScene["cube"].num_indices);
      glBindVertexArray(0);
    }
  }
}


void Scene9::Render()
{
  if(this->follow_camera) {
    second_camera->position = camera->position;
    second_camera->theta = camera->theta;
    second_camera->phi = camera->phi;
  }

  if(this->freeze_camera_in_origin) {
    this->follow_camera = false;
    second_camera->position = vec4(0.0f, 0.0f, -3.7f, 1.0f);
    second_camera->theta = 0.0f;
    second_camera->phi = 0.0f;
  }

  int display_w, display_h;
  glfwGetFramebufferSize(g_Window, &display_w, &display_h);

  //first camera
  glViewport(0, 0, display_w/2, display_h);
  bool mouse_over_camera = false;
  if(Globals::g_CurrentCursorPosX < display_w/2)
    mouse_over_camera = true;

  this->camera->Enable((float) (display_w/2)/display_h, mouse_over_camera);
  this->camera->UpdateShaderUniforms(this->shaders["scene"]);
  DrawCommonModels();

  this->shaders["scene"].use();
  shaders["scene"].setFloat("simulate_perspective_slider", this->simulate_perspective_slider);
  shaders["scene"].setMat4("first_camera_projection", camera->projection);
  shaders["scene"].setMat4("first_camera_view", camera->view);

  //second camera
  shaders["scene"].setBool("second_camera", true);
  glViewport(display_w/2, 0, display_w/2, display_h);
  bool mouse_over_second_camera = false;
  if(Globals::g_CurrentCursorPosX > display_w/2)
    mouse_over_second_camera = true;

  this->second_camera->Enable((float) (display_w/2)/display_h, mouse_over_second_camera);
  this->second_camera->UpdateShaderUniforms(this->shaders["scene"]);
  DrawCommonModels(this->simulate_perspective);

  float y_angle = this->camera->theta;
  float x_angle = this->camera->phi;

  glm::mat4 model = Matrix_Translate(this->camera->position.x, this->camera->position.y, this->camera->position.z)
                    * Matrix_Rotate_Y(y_angle)
                    * Matrix_Rotate_X(x_angle);
  model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
  shaders["scene"].setMat4("model", model);
  shaders["scene"].setInt("object_id", 1);

  glBindVertexArray(this->virtualScene["cube"].vertex_array_object_id);
  glDrawArrays(this->virtualScene["cube"].rendering_mode, 0, this->virtualScene["cube"].num_indices);
  glBindVertexArray(0);

  float frustumHeightNear = camera->nearPlane * glm::tan(camera->fieldOfView * 0.5f);
  float frustumHeightNearR = frustumHeightNear * ((display_w/2) / (float) display_h);
  float frustumHeightNearB = -frustumHeightNear;
  float frustumHeightNearL = -frustumHeightNearR;

  float frustumHeightFar = camera->farPlane * glm::tan(camera->fieldOfView * 0.5f);
  float frustumHeightFarR = frustumHeightFar * ((display_w/2) / (float) display_h);
  float frustumHeightFarB = -frustumHeightFar;
  float frustumHeightFarL = -frustumHeightFarR;

  GLfloat frustum_line_coefficients[] = {
    0.0f, 0.0f, 0.0f, 1.0f,

    frustumHeightNearR, frustumHeightNear,  -camera->nearPlane, 1.0f,
    frustumHeightNearL, frustumHeightNear,  -camera->nearPlane, 1.0f,
    frustumHeightNearL, frustumHeightNearB, -camera->nearPlane, 1.0f,
    frustumHeightNearR, frustumHeightNearB, -camera->nearPlane, 1.0f,

    frustumHeightFarR, frustumHeightFar,  -camera->farPlane, 1.0f,
    frustumHeightFarL, frustumHeightFar,  -camera->farPlane, 1.0f,
    frustumHeightFarL, frustumHeightFarB, -camera->farPlane, 1.0f,
    frustumHeightFarR, frustumHeightFarB, -camera->farPlane, 1.0f
  };

  glLineWidth(4.0f);

  glBindVertexArray(this->virtualScene["frustum_lines"].vertex_array_object_id);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_frustum_lines);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(frustum_line_coefficients), frustum_line_coefficients);

  model = Matrix_Translate(this->camera->position.x, this->camera->position.y, this->camera->position.z)
        * Matrix_Rotate_Y(y_angle)
        * Matrix_Rotate_X(x_angle);
  shaders["scene"].setMat4("model", model);
  shaders["scene"].setInt("object_id", 2);
  DrawVirtualObject(this->virtualScene["frustum_lines"]);

  shaders["scene"].setBool("second_camera", false);
}