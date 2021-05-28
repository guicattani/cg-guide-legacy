#include <iostream>
#ifndef CLASS_HEADER_SCENE
#define CLASS_HEADER_SCENE
#include "scene.h"
#endif

void Scene5::BuildTrianglesAndAddToVirtualScene()
{
  // For more information on how to initialize this structure, refer to Scene3
  // This is not using EBO
  GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
    };

  GLuint VBO_vertices_id;
  glGenBuffers(1, &VBO_vertices_id);

  GLuint cube_VAO_id;
  glGenVertexArrays(1, &cube_VAO_id);

  glBindBuffer(GL_ARRAY_BUFFER, VBO_vertices_id);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindVertexArray(cube_VAO_id);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  SceneObject cube;
  cube.name = "Cube";
  cube.first_index = (void *)0;
  cube.num_indices = 36;
  cube.rendering_mode = GL_TRIANGLES;
  cube.vertex_array_object_id = cube_VAO_id;
  this->virtualScene["cube"] = cube;

  // light VAO
  GLuint light_cube_VAO_id;
  glGenVertexArrays(1, &light_cube_VAO_id);
  glBindVertexArray(light_cube_VAO_id);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  SceneObject light_cube;
  light_cube.name = "Light Cube";
  light_cube.first_index = (void *)0;
  light_cube.num_indices = 36;
  light_cube.rendering_mode = GL_TRIANGLES;
  light_cube.vertex_array_object_id = light_cube_VAO_id;
  this->virtualScene["light_cube"] = light_cube;
}

void Scene5::Render()
{
  this->camera->Enable(this->shaders);

  this->shaders["light_shader"].use();
  this->shaders["light_shader"].setVec3("objectColor", 1.0f, 0.5f, 0.31f);
  this->shaders["light_shader"].setVec3("lightColor",  1.0f, 1.0f, 1.0f);

  glm::mat4 model = glm::mat4(1.0f);
  this->shaders["light_shader"].setMat4("model", model);

  glDrawElements(
      this->virtualScene["cube"].rendering_mode,
      this->virtualScene["cube"].num_indices,
      GL_UNSIGNED_INT,
      (void *)this->virtualScene["cube"].first_index);

  this->shaders["color_shader"].use();
  model = glm::mat4(1.0f);
  model = glm::translate(model, lightPos);
  model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
  this->shaders["color_shader"].setMat4("model", model);

  glDrawElements(
      this->virtualScene["light_cube"].rendering_mode,
      this->virtualScene["light_cube"].num_indices,
      GL_UNSIGNED_INT,
      (void *)this->virtualScene["light_cube"].first_index);
}
