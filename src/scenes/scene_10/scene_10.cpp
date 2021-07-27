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

  this->shaders["scene"].use();
  //textures
  this->sceneTextures["uv_checker"] = LoadTextureImage("../data/uv_checker.jpg");
  this->sceneTextures["container"] = LoadTextureImage("../data/container2.png");
  this->sceneTextures["world"] = LoadTextureImage("../data/tc-earth_daymap_surface.jpg");
  shaders["scene"].setInt("diffuseTexture", 0);

  //cubemap
  this->sceneTextures["cubemap_top"]    = LoadTextureImage("../data/cubemap_top.jpg");
  this->sceneTextures["cubemap_bottom"] = LoadTextureImage("../data/cubemap_bottom.jpg");
  this->sceneTextures["cubemap_left"]   = LoadTextureImage("../data/cubemap_left.jpg");
  this->sceneTextures["cubemap_right"]  = LoadTextureImage("../data/cubemap_right.jpg");
  this->sceneTextures["cubemap_front"]  = LoadTextureImage("../data/cubemap_front.jpg");
  this->sceneTextures["cubemap_back"]   = LoadTextureImage("../data/cubemap_back.jpg");

  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, this->sceneTextures["cubemap_top"]);
  shaders["scene"].setInt("cubemapTopTexture", 1);

  glActiveTexture(GL_TEXTURE2);
  glBindTexture(GL_TEXTURE_2D, this->sceneTextures["cubemap_bottom"]);
  shaders["scene"].setInt("cubemapBottomTexture", 2);

  glActiveTexture(GL_TEXTURE3);
  glBindTexture(GL_TEXTURE_2D, this->sceneTextures["cubemap_left"]);
  shaders["scene"].setInt("cubemapLeftTexture", 3);

  glActiveTexture(GL_TEXTURE4);
  glBindTexture(GL_TEXTURE_2D, this->sceneTextures["cubemap_right"]);
  shaders["scene"].setInt("cubemapRightTexture", 4);

  glActiveTexture(GL_TEXTURE5);
  glBindTexture(GL_TEXTURE_2D, this->sceneTextures["cubemap_front"]);
  shaders["scene"].setInt("cubemapFrontTexture", 5);

  glActiveTexture(GL_TEXTURE6);
  glBindTexture(GL_TEXTURE_2D, this->sceneTextures["cubemap_back"]);
  // Not entirely sure, but I think since GL_TEXTURE0 won't be used anymore, OGL does a roundrobin?
  shaders["scene"].setInt("cubemapBackTexture", 0);

  //textures
  this->shaders["texture"].use();
  shaders["texture"].setInt("diffuseTexture", 0);
  //cubemap
  shaders["texture"].setInt("cubemapTopTexture", 1);
  shaders["texture"].setInt("cubemapBottomTexture", 2);
  shaders["texture"].setInt("cubemapLeftTexture", 3);
  shaders["texture"].setInt("cubemapRightTexture", 4);
  shaders["texture"].setInt("cubemapFrontTexture", 5);
  // Not entirely sure, but I think since GL_TEXTURE0 won't be used anymore, OGL does a roundrobin?
  shaders["texture"].setInt("cubemapBackTexture", 0);
}

void Scene10::DrawArrow()
{
  arrow->position.x = 2.0f * cos(arrow->phi) * sin(arrow->theta);
  arrow->position.y = 2.0f * sin(arrow->phi);
  arrow->position.z = 2.0f * cos(arrow->phi) * cos(arrow->theta);

  vec4 forward_vector = vec4(0.0f, 0.0f, 1.0f, 0.0f);
  vec4 look_at_vector =  arrow->lookAt - arrow->position;
  arrow->position -= normalize(look_at_vector) * arrow->distance;

  float dot_product = dotproduct(look_at_vector, forward_vector);
  float y_angle = atan2(look_at_vector.x, dot_product);

  vec4 up_vector = vec4(0.0f, 1.0f, 0.0f, 0.0f);
  look_at_vector = look_at_vector * Matrix_Rotate_Y(y_angle);
  dot_product = dotproduct(look_at_vector, up_vector);
  float x_angle = atan2(look_at_vector.z, dot_product) - 3.14f / 2;

  mat4 model = Matrix_Translate(arrow->position.x, arrow->position.y, arrow->position.z)
               * Matrix_Rotate_Y(y_angle)
               * Matrix_Rotate_X(x_angle);

  shaders["scene"].use();
  shaders["scene"].setMat4("model", model);
  shaders["scene"].setVec4("arrow_position", arrow->position);
  DrawVirtualObject(this->virtualScene["arrow"]);

  // model = Matrix_Translate(arrow->lookAt.x, arrow->lookAt.y, arrow->lookAt.z);
  // model = scale(model, vec3(0.3f));
  // shaders["scene"].setMat4("model", model);
  // DrawVirtualObject(this->virtualScene["cube"]);
}

void Scene10::Render()
{
  int display_w, display_h;
  glfwGetFramebufferSize(g_Window, &display_w, &display_h);

  shaders["scene"].use();
  glViewport(0, 0, display_w/2, display_h);
  bool mouse_over_camera = false;
  if(Globals::g_CurrentCursorPosX < display_w/2)
    mouse_over_camera = true;

  this->camera->Enable((float) (display_w/2)/display_h, mouse_over_camera);
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
  if(this->texture_projection != 3) {
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
  shaders["scene"].setVec4("bbox_min", vec4(this->virtualScene[chosen_model_name.c_str()].bbox_min, 1.0f));
  shaders["scene"].setVec4("bbox_max", vec4(this->virtualScene[chosen_model_name.c_str()].bbox_max, 1.0f));
  shaders["scene"].setInt("texture_projection", this->texture_projection);
  shaders["scene"].setFloat("cylinder_height", this->cylinder_height);
  shaders["scene"].setBool("use_world_coordinates", this->use_world_coordinates);

  DrawVirtualObject(this->virtualScene[chosen_model_name.c_str()]);

  DrawArrow();
  //second camera
  shaders["texture"].use();
  shaders["texture"].setVec4("arrow_position", arrow->position);
  glViewport(display_w/2, 0, display_w/2, display_h);
  bool mouse_over_second_camera = false;
  if(Globals::g_CurrentCursorPosX > display_w/2)
    mouse_over_second_camera = true;

  this->second_camera->Enable((float) (display_w/2)/display_h, mouse_over_second_camera);
  this->second_camera->UpdateShaderUniforms(this->shaders["texture"]);

  model = Matrix_Identity();
  model = model * Matrix_Translate(model_position.x, model_position.y, model_position.z);

  shaders["texture"].setMat4("model", model);
  shaders["texture"].setVec4("bbox_min", vec4(this->virtualScene[chosen_model_name.c_str()].bbox_min, 1.0f));
  shaders["texture"].setVec4("bbox_max", vec4(this->virtualScene[chosen_model_name.c_str()].bbox_max, 1.0f));
  shaders["texture"].setInt("texture_projection", this->texture_projection);
  shaders["texture"].setFloat("cylinder_height", this->cylinder_height);
  shaders["texture"].setBool("use_world_coordinates", this->use_world_coordinates);
  shaders["texture"].setBool("isObject", true);
  shaders["texture"].setFloat("texture_projection_transparency", this-> texture_projection_transparency);
  DrawVirtualObject(this->virtualScene[chosen_model_name.c_str()]);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  shaders["texture"].setBool("isObject", false);

  model = Matrix_Identity();
  model = scale(model, glm::vec3(1.2f));
  shaders["texture"].setMat4("model", model);

  if(this->texture_projection == 0) {
    DrawVirtualObject(this->virtualScene["sphere"]);
  } else if(this->texture_projection == 1) {
    DrawVirtualObject(this->virtualScene["cylinder"]);
  } else if(this->texture_projection == 2) {
    DrawVirtualObject(this->virtualScene["cube"]);
  } else if(this->texture_projection == 3) {
    DrawVirtualObject(this->virtualScene["cube"]);
  }

  glDisable(GL_BLEND);
}
