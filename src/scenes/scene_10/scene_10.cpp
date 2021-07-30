#include <iostream>
#ifndef CLASS_HEADER_SCENE
#define CLASS_HEADER_SCENE
#include "scene.h"
#endif

void Scene10::BuildTrianglesAndAddToVirtualScene()
{
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
  shaders["texture"].setInt("cubemapBackTexture", 0);
  // Not entirely sure, but I think since GL_TEXTURE0 won't be used anymore, OGL does a roundrobin?
}

void Scene10::DrawArrow()
{
  if(this->texture_projection == 1) {
    arrow->position.x = 2.0f * cos(arrow->phi) * sin(arrow->theta);
    arrow->position.y = arrow->lookAtHeightCylinder;
    arrow->position.z = 2.0f * cos(arrow->phi) * cos(arrow->theta);
    arrow->lookAt.y = arrow->lookAtHeightCylinder;
  }
  else if(this->texture_projection != 2) {
    arrow->position.x = 2.0f * cos(arrow->phi) * sin(arrow->theta);
    arrow->position.y = 2.0f * sin(arrow->phi);
    arrow->position.z = 2.0f * cos(arrow->phi) * cos(arrow->theta);
  } else {
    arrow->phi = 0.0f;
    arrow->theta = 0.0f;
    arrow->position.x = arrow->axisAlignedCenter.x + arrow->axisAlignedPosition.x;
    arrow->position.y = arrow->axisAlignedCenter.y + arrow->axisAlignedPosition.y;
    arrow->position.z = 2.0f * arrow->distance;
    arrow->lookAt = arrow->position - vec4(0.0f, 0.0f, 1.0f, 0.0f);
  }

  vec4 forward_vector = vec4(0.0f, 0.0f, 1.0f, 0.0f);
  vec4 look_at_vector =  arrow->lookAt - arrow->position;
  arrow->position -= normalize(look_at_vector) * arrow->distance;

  vec4 arrow_look_at_vec = normalize(look_at_vector);
  float arrow_point_in_plane_distance = (1 - arrow->position.z) / arrow_look_at_vec.z;
  vec4 arrow_point_in_plane = arrow->position + arrow_look_at_vec * arrow_point_in_plane_distance;

  shaders["texture"].use();
  shaders["texture"].setVec4("arrow_point_in_plane", arrow_point_in_plane);

  shaders["scene"].use();
  shaders["scene"].setVec4("arrow_position", arrow->position);
  shaders["scene"].setVec4("arrow_look_at", arrow->lookAt);
  shaders["scene"].setVec4("arrow_point_in_plane", arrow_point_in_plane);

  float dot_product = dotproduct(look_at_vector, forward_vector);
  float y_angle = atan2(look_at_vector.x, dot_product);

  vec4 up_vector = vec4(0.0f, 1.0f, 0.0f, 0.0f);
  look_at_vector = look_at_vector * Matrix_Rotate_Y(y_angle);
  dot_product = dotproduct(look_at_vector, up_vector);
  float x_angle = atan2(look_at_vector.z, dot_product) - 3.14f / 2;

  mat4 model = Matrix_Translate(arrow->position.x, arrow->position.y, arrow->position.z)
               * Matrix_Rotate_Y(y_angle)
               * Matrix_Rotate_X(x_angle);

  if(!this->use_world_coordinates)
    model = model * Matrix_Translate(-model_position.x, model_position.y, -model_position.z);

  shaders["arrow"].use();
  shaders["arrow"].setMat4("model", model);
  DrawVirtualObject(this->virtualScene["arrow"]);
}

void Scene10::Render()
{
  int display_w, display_h;
  glfwGetFramebufferSize(g_Window, &display_w, &display_h);

  glViewport(0, 0, display_w/2, display_h);
  bool mouse_over_camera = false;
  if(Globals::g_CurrentCursorPosX < display_w/2)
    mouse_over_camera = true;

  this->camera->Enable((float) (display_w/2)/display_h, mouse_over_camera);
  this->camera->UpdateShaderUniforms(this->shaders["scene"]);
  this->camera->UpdateShaderUniforms(this->shaders["arrow"]);

  glLineWidth(1.0f);

  this->shaders["scene"].use();
  glm::mat4 model = Matrix_Identity();

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
  } else {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->sceneTextures["cubemap_back"]);
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
  arrow->axisAlignedCenter = this->virtualScene[chosen_model_name.c_str()].bbox_center;
  arrow->lookAtMaxHeightCylinder = this->virtualScene[chosen_model_name.c_str()].bbox_max.y;
  if(this->texture_projection != 2) {
    arrow->lookAt = vec4(this->virtualScene[chosen_model_name.c_str()].bbox_center, 1.0);
  }
  shaders["scene"].use();
  shaders["scene"].setMat4("model", model);
  shaders["scene"].setVec4("bbox_min", vec4(this->virtualScene[chosen_model_name.c_str()].bbox_min, 1.0f));
  shaders["scene"].setVec4("bbox_max", vec4(this->virtualScene[chosen_model_name.c_str()].bbox_max, 1.0f));

  if(this->texture_projection == 1) {
    shaders["scene"].setVec4("bbox_center", vec4(
      this->virtualScene[chosen_model_name.c_str()].bbox_center.x,
      arrow->lookAtHeightCylinder,
      this->virtualScene[chosen_model_name.c_str()].bbox_center.z,
      1.0f));
  }
  else {
    shaders["scene"].setVec4("bbox_center", vec4(this->virtualScene[chosen_model_name.c_str()].bbox_center,1.0f));
  }


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

  if(!this->use_world_coordinates)
    model = Matrix_Identity();

  shaders["texture"].setMat4("model", model);
  shaders["texture"].setVec4("bbox_min", vec4(this->virtualScene[chosen_model_name.c_str()].bbox_min, 1.0f));

  if(this->texture_projection == 1) {
    shaders["texture"].setVec4("bbox_center", vec4(
      this->virtualScene[chosen_model_name.c_str()].bbox_center.x,
      arrow->lookAtHeightCylinder,
      this->virtualScene[chosen_model_name.c_str()].bbox_center.z,
      1.0f));
  }
  else {
    shaders["texture"].setVec4("bbox_center", vec4(this->virtualScene[chosen_model_name.c_str()].bbox_center,1.0f));
  }

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
  string chosen_projection_name;

  if(this->texture_projection == 0)
  {
    float radius = 1.7f;
    model = scale(model, vec3(radius));
    model = model * Matrix_Translate(0.0f, -0.5f, 0.0f);
    chosen_projection_name = "sphere";
  } else if(this->texture_projection == 1)
  {
    model = scale(model, vec3(1.05f));
    chosen_projection_name = "cylinder";
  } else if(this->texture_projection == 2)
  {
    SceneObject virtual_model = this->virtualScene[chosen_model_name.c_str()];
    model = scale(model, vec3(
                          abs(virtual_model.bbox_max.x - virtual_model.bbox_min.x) / 2,
                          abs(virtual_model.bbox_max.y - virtual_model.bbox_min.y) / 2,
                          abs(virtual_model.bbox_max.z - virtual_model.bbox_min.z) / 2
                          ));
    model = scale(model, vec3(1.15f));
    chosen_projection_name = "cube";
  }
  else if(this->texture_projection == 3)
  {
    SceneObject virtual_model = this->virtualScene[chosen_model_name.c_str()];
    model = scale(model, vec3(
                          abs(virtual_model.bbox_max.x - virtual_model.bbox_min.x) / 2,
                          abs(virtual_model.bbox_max.y - virtual_model.bbox_min.y) / 2,
                          abs(virtual_model.bbox_max.z - virtual_model.bbox_min.z) / 2
                          ));
    model = scale(model, vec3(1.02f));
    chosen_projection_name = "cube";
  }

  if(texture_projection == 1) {
    switch(chosen_model) {
      case 1:
        model = scale(model, vec3(1.2f));
        break;
      case 2:
        model = scale(model, vec3(1.6f, 1.0f, 1.6f));
        break;
      case 3:
        model = scale(model, vec3(1.6f, 1.0f, 1.6f));
        break;
    }
  }

  shaders["texture"].setMat4("model", model);
  DrawVirtualObject(this->virtualScene[chosen_projection_name.c_str()]);
  glDisable(GL_BLEND);
}
