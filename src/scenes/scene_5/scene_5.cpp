#include <iostream>
#ifndef CLASS_HEADER_SCENE
#define CLASS_HEADER_SCENE
#include "scene.h"
#endif

void Scene5::BuildTrianglesAndAddToVirtualScene()
{
  // This is not using EBO
  GLfloat vertices[] = {
      -0.3f,-0.3f,-0.3f,	-1.0f, 0.0f, 0.0f,  // Left Side
      -0.3f,-0.3f, 0.3f,	-1.0f, 0.0f, 0.0f,
      -0.3f, 0.3f, 0.3f,	-1.0f, 0.0f, 0.0f,
      -0.3f,-0.3f,-0.3f,	-1.0f, 0.0f, 0.0f,
      -0.3f, 0.3f, 0.3f,	-1.0f, 0.0f, 0.0f,
      -0.3f, 0.3f,-0.3f,	-1.0f, 0.0f, 0.0f,  // Left Side

       0.3f, 0.3f,-0.3f,   0.0f, 0.0f,-1.0f,  // Back Side
      -0.3f,-0.3f,-0.3f,   0.0f, 0.0f,-1.0f,
      -0.3f, 0.3f,-0.3f,   0.0f, 0.0f,-1.0f,
       0.3f, 0.3f,-0.3f,   0.0f, 0.0f,-1.0f,
       0.3f,-0.3f,-0.3f,   0.0f, 0.0f,-1.0f,
      -0.3f,-0.3f,-0.3f,   0.0f, 0.0f,-1.0f,  // Back Side

       0.3f,-0.3f, 0.3f,   0.0f,-1.0f, 0.0f,  // Bottom Side
      -0.3f,-0.3f,-0.3f,   0.0f,-1.0f, 0.0f,
       0.3f,-0.3f,-0.3f,   0.0f,-1.0f, 0.0f,
       0.3f,-0.3f, 0.3f,   0.0f,-1.0f, 0.0f,
      -0.3f,-0.3f, 0.3f,   0.0f,-1.0f, 0.0f,
      -0.3f,-0.3f,-0.3f,   0.0f,-1.0f, 0.0f,  // Bottom Side

      -0.3f, 0.3f, 0.3f,   0.0f, 0.0f, 1.0f,  // Front Side
      -0.3f,-0.3f, 0.3f,   0.0f, 0.0f, 1.0f,
       0.3f,-0.3f, 0.3f,   0.0f, 0.0f, 1.0f,
       0.3f, 0.3f, 0.3f,   0.0f, 0.0f, 1.0f,
      -0.3f, 0.3f, 0.3f,   0.0f, 0.0f, 1.0f,
       0.3f,-0.3f, 0.3f,   0.0f, 0.0f, 1.0f,  // Front Side

       0.3f, 0.3f, 0.3f,   1.0f, 0.0f, 0.0f,  // Right Side
       0.3f,-0.3f,-0.3f,   1.0f, 0.0f, 0.0f,
       0.3f, 0.3f,-0.3f,   1.0f, 0.0f, 0.0f,
       0.3f,-0.3f,-0.3f,   1.0f, 0.0f, 0.0f,
       0.3f, 0.3f, 0.3f,   1.0f, 0.0f, 0.0f,
       0.3f,-0.3f, 0.3f,   1.0f, 0.0f, 0.0f,  // Right Side

       0.3f, 0.3f, 0.3f,   0.0f, 1.0f, 0.0f,  // Top Side
       0.3f, 0.3f,-0.3f,   0.0f, 1.0f, 0.0f,
      -0.3f, 0.3f,-0.3f,   0.0f, 1.0f, 0.0f,
       0.3f, 0.3f, 0.3f,   0.0f, 1.0f, 0.0f,
      -0.3f, 0.3f,-0.3f,   0.0f, 1.0f, 0.0f,
      -0.3f, 0.3f, 0.3f,   0.0f, 1.0f, 0.0f   // Top Side
    };

  GLuint VBO_vertices_id, VAO_cube_id, VAO_light_cube_id;
  glGenVertexArrays(1, &VAO_cube_id);
  glGenBuffers(1, &VBO_vertices_id);

  glBindBuffer(GL_ARRAY_BUFFER, VBO_vertices_id);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindVertexArray(VAO_cube_id);
  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  // normal attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

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
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

  SceneObject light_cube;
  light_cube.name = "Light Cube";
  light_cube.first_index = (void *)0;
  light_cube.num_indices = 36;
  light_cube.rendering_mode = GL_TRIANGLES;
  light_cube.vertex_array_object_id = VAO_light_cube_id;
  this->virtualScene["light_cube"] = light_cube;
  glEnableVertexAttribArray(0);

  // text
  glGenVertexArrays(1, &this->VAO_text);
  glGenBuffers(1, &this->VBO_text);
  glBindVertexArray(this->VAO_text);
  glBindBuffer(GL_ARRAY_BUFFER, this->VBO_text);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void Scene5::Render()
{
  //Necessary for Freetype 3D Text
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  this->camera->Enable();

  this->shaders["color_shader"].use();
  this->camera->UpdateShaderUniforms(this->shaders["color_shader"]);
  this->shaders["color_shader"].setVec3("objectColor", 1.0f, 0.4f, 0.31f);
  this->shaders["color_shader"].setVec3("lightColor",  1.0f, 1.0f, 1.0f);
  this->shaders["color_shader"].setVec3("lightPos",  this->lightPos);

  // Ambient cube
  this->shaders["color_shader"].setFloat("gouradSpecularStrength", 0.0f);
  this->shaders["color_shader"].setFloat("phongSpecularStrength", 0.0f);
  this->shaders["color_shader"].setFloat("diffuseStrength", 0.0f);
  this->shaders["color_shader"].setFloat("ambientStrength", this->ambientStrength);
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 2.5f));
  this->shaders["color_shader"].setMat4("model", model);
  glBindVertexArray(this->virtualScene["cube"].vertex_array_object_id);
  glDrawArrays(this->virtualScene["cube"].rendering_mode, 0, this->virtualScene["cube"].num_indices);


  // Diffuse cube
  this->shaders["color_shader"].setFloat("gouradSpecularStrength", 0.0f);
  this->shaders["color_shader"].setFloat("phongSpecularStrength", 0.0f);
  this->shaders["color_shader"].setFloat("diffuseStrength", this->diffuseStrength);
  this->shaders["color_shader"].setFloat("ambientStrength", 0.0f);
  model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(0.0f, 0.0f, 2.5f));
  this->shaders["color_shader"].setMat4("model", model);
  glBindVertexArray(this->virtualScene["cube"].vertex_array_object_id);
  glDrawArrays(this->virtualScene["cube"].rendering_mode, 0, this->virtualScene["cube"].num_indices);


  // Specular cube
  this->shaders["color_shader"].setFloat("gouradSpecularStrength", this->gouradSpecularStrength);
  this->shaders["color_shader"].setFloat("phongSpecularStrength", this->phongSpecularStrength);
  this->shaders["color_shader"].setFloat("diffuseStrength", 0.0f);
  this->shaders["color_shader"].setFloat("ambientStrength", 0.0f);
  model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(1.0f, 0.0f, 2.5f));
  this->shaders["color_shader"].setMat4("model", model);
  glBindVertexArray(this->virtualScene["cube"].vertex_array_object_id);
  glDrawArrays(this->virtualScene["cube"].rendering_mode, 0, this->virtualScene["cube"].num_indices);

  // Combined cube
  this->shaders["color_shader"].setFloat("gouradSpecularStrength", this->gouradSpecularStrength);
  this->shaders["color_shader"].setFloat("phongSpecularStrength", this->phongSpecularStrength);
  this->shaders["color_shader"].setFloat("diffuseStrength", this->diffuseStrength);
  this->shaders["color_shader"].setFloat("ambientStrength", this->ambientStrength);
  model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(2.0f, 0.0f, 2.5f));
  this->shaders["color_shader"].setMat4("model", model);

  glBindVertexArray(this->virtualScene["cube"].vertex_array_object_id);
  glDrawArrays(this->virtualScene["cube"].rendering_mode, 0, this->virtualScene["cube"].num_indices);

  //Light cube
  this->shaders["light_shader"].use();
  this->camera->UpdateShaderUniforms(this->shaders["light_shader"]);
  model = glm::mat4(1.0f);
  model = glm::translate(model, this->lightPos);
  model = glm::scale(model, glm::vec3(0.5f)); // a smaller cube
  this->shaders["light_shader"].setMat4("model", model);

  glBindVertexArray(this->virtualScene["light_cube"].vertex_array_object_id);
  glDrawArrays(this->virtualScene["light_cube"].rendering_mode, 0, this->virtualScene["light_cube"].num_indices);

  this->shaders["text_shader"].use();
  this->camera->UpdateShaderUniforms(this->shaders["text_shader"]);
  model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(-1.5f, 0.4f, 2.2f));
  this->shaders["text_shader"].setMat4("model", model);
  RenderText(this->shaders["text_shader"], this->VAO_text, this->VBO_text, "Ambient", 0.0f, 0.0f, 0.005f, glm::vec3(1.0f, 1.0f, 1.0f));

  model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(-0.4f, 0.4f, 2.2f));
  this->shaders["text_shader"].setMat4("model", model);
  RenderText(this->shaders["text_shader"], this->VAO_text, this->VBO_text, "Diffuse", 0.0f, 0.0f, 0.005f, glm::vec3(1.0f, 1.0f, 1.0f));

  model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(0.55f, 0.4f, 2.2f));
  this->shaders["text_shader"].setMat4("model", model);
  RenderText(this->shaders["text_shader"], this->VAO_text, this->VBO_text, "Specular", 0.0f, 0.0f, 0.005f, glm::vec3(1.0f, 1.0f, 1.0f));

  model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(1.6f, 0.4f, 2.2f));
  this->shaders["text_shader"].setMat4("model", model);
  RenderText(this->shaders["text_shader"], this->VAO_text, this->VBO_text, "All combined", 0.0f, 0.0f, 0.004f, glm::vec3(1.0f, 1.0f, 1.0f));
}
