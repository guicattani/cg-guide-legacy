#include <iostream>
#ifndef CLASS_HEADER_SCENE
#define CLASS_HEADER_SCENE
#include "scene.h"
#endif

void Scene10::BuildTrianglesAndAddToVirtualScene()
{
   GLfloat model_color_coefficients[] = {
      0.0f,   0.0f,  0.0f,  1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
      1.0f,   0.0f,  0.0f,  1.0f,  1.0f, 0.0f, 0.0f, 1.0f,

      0.0f,   0.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, 1.0f,
      0.0f,   1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, 1.0f,

      0.0f,   0.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, 1.0f,
      0.0f,   0.0f,  1.0f,  1.0f,  0.0f, 0.0f, 1.0f, 1.0f
  };

  GLuint VBO_model_color_coefficients_id, vertex_array_object_id;
  glGenBuffers(1, &VBO_model_color_coefficients_id);
  glGenVertexArrays(1, &vertex_array_object_id);

  glBindBuffer(GL_ARRAY_BUFFER, VBO_model_color_coefficients_id);
  glBufferData(GL_ARRAY_BUFFER, sizeof(model_color_coefficients), model_color_coefficients, GL_STATIC_DRAW);

  glBindVertexArray(vertex_array_object_id);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(4 * sizeof(float)));
  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  GLuint indices[] = {
      0, 1,
      2, 3,
      4, 5
  };

  SceneObject axes;
  axes.name = "Eixos XYZ";
  axes.first_index = (void *)0;
  axes.num_indices = 6;
  axes.rendering_mode = GL_LINES;
  axes.vertex_array_object_id = vertex_array_object_id;
  this->virtualScene["axes"] = axes;

  GLuint indices_id;
  glGenBuffers(1, &indices_id);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_id);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), NULL, GL_STATIC_DRAW);
  glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(indices), indices);

  glBindVertexArray(0);

  //textures
  this->sceneTextures["uv_checker"] = LoadTextureImage("../data/uv_checker.jpg");
  this->sceneTextures["container"] = LoadTextureImage("../data/container2.png");
  this->sceneTextures["world"] = LoadTextureImage("../data/tc-earth_daymap_surface.jpg");
  shaders["scene"].setInt("diffuseTexture", 0);
}

void Scene10::Render()
{
  this->camera->Enable();
  this->camera->UpdateShaderUniforms(this->shaders["scene"]);
  this->camera->UpdateShaderUniforms(this->shaders["axes"]);

  glLineWidth(1.0f);

  this->shaders["axes"].use();
  glm::mat4 model = Matrix_Identity();
  model = model * Matrix_Translate(5.0f, 0.0f, 0.0f);
  shaders["axes"].setMat4("model", model);
  DrawVirtualObject(this->virtualScene["axes"]);

  this->shaders["scene"].use();
  model = Matrix_Identity();
  // bind diffuse map
  glActiveTexture(GL_TEXTURE0);
  switch(chosen_texture) {
  case 0:
    glBindTexture(GL_TEXTURE_2D, this->sceneTextures["uv_checker"]);
    break;
  case 1:
    glBindTexture(GL_TEXTURE_2D, this->sceneTextures["container"]);
    break;
  case 2:
    glBindTexture(GL_TEXTURE_2D, this->sceneTextures["world"]);
    break;
  }

  string chosen_model_name;
  // TODO we can use enum for this, can"t we
  switch(chosen_model) {
    case 0:
      chosen_model_name = "cylinder";
      break;
    case 1:
      chosen_model_name = "bunny";
      break;
    case 2:
      chosen_model_name = "teapot";
      model = scale(model, glm::vec3(0.5f));
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

  model = model * Matrix_Translate(model_position.x, model_position.y, model_position.z);

  shaders["scene"].setMat4("model", model);
  shaders["scene"].setInt("object_id", 0);
  shaders["scene"].setVec4("bbox_min", vec4(this->virtualScene[chosen_model_name.c_str()].bbox_min, 1.0f));
  shaders["scene"].setVec4("bbox_max", vec4(this->virtualScene[chosen_model_name.c_str()].bbox_max, 1.0f));
  shaders["scene"].setInt("texture_projection", this->texture_projection);
  shaders["scene"].setFloat("cylinder_height", this->cylinder_height);
  shaders["scene"].setBool("use_world_coordinates", this->use_world_coordinates);

  DrawVirtualObject(this->virtualScene[chosen_model_name.c_str()]);
}
