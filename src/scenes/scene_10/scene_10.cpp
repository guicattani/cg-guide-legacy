#include <iostream>
#ifndef CLASS_HEADER_SCENE
#define CLASS_HEADER_SCENE
#include "scene.h"
#endif

void Scene10::BuildTrianglesAndAddToVirtualScene()
{
  this->diffuseTextureId = LoadTextureImage("../data/container2.png");

  this->shaders["scene"].use();
  this->shaders["scene"].setInt("diffuseTexture", 0);
}

void Scene10::Render()
{
  this->shaders["scene"].use();
  this->camera->Enable();
  this->camera->UpdateShaderUniforms(this->shaders["scene"]);

  glLineWidth(1.0f);

  glm::mat4 model = Matrix_Identity();
  shaders["scene"].setMat4("model", model);
  shaders["scene"].setInt("object_id", 0);

  // bind diffuse map
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, this->diffuseTextureId);

  shaders["scene"].setVec4("bbox_min", vec4(this->virtualScene["cylinder"].bbox_min, 1.0f));
  shaders["scene"].setVec4("bbox_max", vec4(this->virtualScene["cylinder"].bbox_max, 1.0f));
  shaders["scene"].setInt("texture_projection", this->texture_projection);

  DrawVirtualObject(this->virtualScene["cylinder"]);
}
