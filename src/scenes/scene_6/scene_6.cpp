#include <iostream>
#ifndef CLASS_HEADER_SCENE
#define CLASS_HEADER_SCENE
#include "scene.h"
#endif


void Scene6::BuildTrianglesAndAddToVirtualScene()
{
  // This is not using EBO
  GLfloat vertices[] = {
      // positions        // normals          //texture coords
      -1.0f,-1.0f,-1.0f,	-1.0f, 0.0f, 0.0f,  0.0f, 0.0f, // Left Side // -X
      -1.0f,-1.0f, 1.0f,	-1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
      -1.0f, 1.0f, 1.0f,	-1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
      -1.0f,-1.0f,-1.0f,	-1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
      -1.0f, 1.0f, 1.0f,	-1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
      -1.0f, 1.0f,-1.0f,	-1.0f, 0.0f, 0.0f,  0.0f, 1.0f, // Left Side

       1.0f, 1.0f,-1.0f,   0.0f, 0.0f,-1.0f,  0.0f, 1.0f, // Back Side // -Z
      -1.0f,-1.0f,-1.0f,   0.0f, 0.0f,-1.0f,  1.0f, 0.0f,
      -1.0f, 1.0f,-1.0f,   0.0f, 0.0f,-1.0f,  1.0f, 1.0f,
       1.0f, 1.0f,-1.0f,   0.0f, 0.0f,-1.0f,  0.0f, 1.0f,
       1.0f,-1.0f,-1.0f,   0.0f, 0.0f,-1.0f,  0.0f, 0.0f,
      -1.0f,-1.0f,-1.0f,   0.0f, 0.0f,-1.0f,  1.0f, 0.0f, // Back Side

       1.0f,-1.0f, 1.0f,   0.0f,-1.0f, 0.0f,  0.0f, 0.0f, // Bottom Side // -Y
      -1.0f,-1.0f,-1.0f,   0.0f,-1.0f, 0.0f,  1.0f, 1.0f,
       1.0f,-1.0f,-1.0f,   0.0f,-1.0f, 0.0f,  1.0f, 0.0f,
       1.0f,-1.0f, 1.0f,   0.0f,-1.0f, 0.0f,  0.0f, 0.0f,
      -1.0f,-1.0f, 1.0f,   0.0f,-1.0f, 0.0f,  0.0f, 1.0f,
      -1.0f,-1.0f,-1.0f,   0.0f,-1.0f, 0.0f,  1.0f, 1.0f, // Bottom Side

      -1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 1.0f,  0.0f, 1.0f, // Front Side // +Z
      -1.0f,-1.0f, 1.0f,   0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
       1.0f,-1.0f, 1.0f,   0.0f, 0.0f, 1.0f,  1.0f, 0.0f,
       1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
      -1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 1.0f,  0.0f, 1.0f,
       1.0f,-1.0f, 1.0f,   0.0f, 0.0f, 1.0f,  1.0f, 0.0f, // Front Side

       1.0f, 1.0f, 1.0f,   1.0f, 0.0f, 0.0f,  0.0f, 1.0f, // Right Side // +X
       1.0f,-1.0f,-1.0f,   1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
       1.0f, 1.0f,-1.0f,   1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
       1.0f,-1.0f,-1.0f,   1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
       1.0f, 1.0f, 1.0f,   1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
       1.0f,-1.0f, 1.0f,   1.0f, 0.0f, 0.0f,  0.0f, 0.0f, // Right Side

       1.0f, 1.0f, 1.0f,   0.0f, 1.0f, 0.0f,  1.0f, 1.0f, // Top Side // +Y
       1.0f, 1.0f,-1.0f,   0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
      -1.0f, 1.0f,-1.0f,   0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
       1.0f, 1.0f, 1.0f,   0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
      -1.0f, 1.0f,-1.0f,   0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
      -1.0f, 1.0f, 1.0f,   0.0f, 1.0f, 0.0f,  1.0f, 0.0f // Top Side
    };

  GLuint VBO_vertices_id, VAO_cube_id, VAO_light_cube_id;
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

  // light VAO
  glGenVertexArrays(1, &VAO_light_cube_id);
  glBindVertexArray(VAO_light_cube_id);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_vertices_id);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);

  SceneObject light_cube;
  light_cube.name = "Light Cube";
  light_cube.first_index = (void *)0;
  light_cube.num_indices = 36;
  light_cube.rendering_mode = GL_TRIANGLES;
  light_cube.vertex_array_object_id = VAO_light_cube_id;
  this->virtualScene["light_cube"] = light_cube;
  glEnableVertexAttribArray(0);

  this->material->diffuseTextureId = LoadTextureImage("../data/container2.png");
  this->material->specularTextureId = LoadTextureImage("../data/container2_specular.png");

  this->shaders["color_shader"].use();
  this->shaders["color_shader"].setInt("material.diffuseTexture", 0);
  this->shaders["color_shader"].setInt("material.specularTexture", 1);
}

void Scene6::Render()
{
  this->camera->Enable();

  this->shaders["color_shader"].use();
  this->camera->UpdateShaderUniforms(this->shaders["color_shader"]);

  this->shaders["color_shader"].setVec3("light.position", this->light->position);
  this->shaders["color_shader"].setVec3("light.ambient", this->light->ambient);
  this->shaders["color_shader"].setVec3("light.diffuse", this->light->diffuse);
  this->shaders["color_shader"].setVec3("light.specular", this->light->specular);

  // material properties
  this->shaders["color_shader"].setVec3("material.ambient", this->material->ambient);
  this->shaders["color_shader"].setVec3("material.diffuse", this->material->diffuse);
  this->shaders["color_shader"].setVec3("material.specular", this->material->specular); // specular lighting doesn't have full effect on this object's material
  this->shaders["color_shader"].setFloat("material.shininess", this->material->shininess);
  this->shaders["color_shader"].setFloat("gouradSpecularStrength", this->gouradSpecularStrength);

  glm::mat4 model = glm::mat4(1.0f);
  this->shaders["color_shader"].setMat4("model", model);

  //textures
  this->shaders["color_shader"].setBool("useTexture", this->useTexture);
  if(this->useTexture) {
    this->shaders["color_shader"].setBool("useDiffuseTexture", this->useDiffuseTexture);
    this->shaders["color_shader"].setBool("useSpecularTexture", this->useSpecularTexture);
  }
  // bind diffuse map
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, this->material->diffuseTextureId);

  // bind specular map
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, this->material->specularTextureId);

  glBindVertexArray(this->virtualScene["cube"].vertex_array_object_id);
  glDrawArrays(this->virtualScene["cube"].rendering_mode, 0, this->virtualScene["cube"].num_indices);

  this->shaders["light_shader"].use();
  this->camera->UpdateShaderUniforms(this->shaders["light_shader"]);
  model = glm::mat4(1.0f);
  model = glm::translate(model, this->light->position);
  model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
  this->shaders["light_shader"].setVec3("color", this->light->ambient + this->light->diffuse);
  this->shaders["light_shader"].setMat4("model", model);

  glBindVertexArray(this->virtualScene["light_cube"].vertex_array_object_id);
  glDrawArrays(this->virtualScene["light_cube"].rendering_mode, 0, this->virtualScene["light_cube"].num_indices);
}
