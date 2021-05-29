#include <iostream>
#ifndef CLASS_HEADER_SCENE
#define CLASS_HEADER_SCENE
#include "scene.h"
#endif

void Scene5::BuildTrianglesAndAddToVirtualScene()
{
  // This is not using EBO
  GLfloat vertices[] = {
	    -0.5f,	-0.5f,	-0.5f,
	    -0.5f,	-0.5f,	 0.5f,
	    -0.5f,	 0.5f,	 0.5f,
	     0.5f,	 0.5f,	-0.5f,
	    -0.5f,	-0.5f,	-0.5f,
	    -0.5f,	 0.5f,	-0.5f,
	     0.5f,	-0.5f,	 0.5f,
	    -0.5f,	-0.5f,	-0.5f,
	     0.5f,	-0.5f,	-0.5f,
	     0.5f,	 0.5f,	-0.5f,
	     0.5f,	-0.5f,	-0.5f,
	    -0.5f,	-0.5f,	-0.5f,
	    -0.5f,	-0.5f,	-0.5f,
	    -0.5f,	 0.5f,	 0.5f,
	    -0.5f,	 0.5f,	-0.5f,
	     0.5f,	-0.5f,	 0.5f,
	    -0.5f,	-0.5f,	 0.5f,
	    -0.5f,	-0.5f,	-0.5f,
	    -0.5f,	 0.5f,	 0.5f,
	    -0.5f,	-0.5f,	 0.5f,
	     0.5f,	-0.5f,	 0.5f,
	     0.5f,	 0.5f,	 0.5f,
	     0.5f,	-0.5f,	-0.5f,
	     0.5f,	 0.5f,	-0.5f,
	     0.5f,	-0.5f,	-0.5f,
	     0.5f,	 0.5f,	 0.5f,
	     0.5f,	-0.5f,	 0.5f,
	     0.5f,	 0.5f,	 0.5f,
	     0.5f,	 0.5f,	-0.5f,
	    -0.5f,	 0.5f,	-0.5f,
	     0.5f,	 0.5f,	 0.5f,
	    -0.5f,	 0.5f,	-0.5f,
	    -0.5f,	 0.5f,	 0.5f,
	     0.5f,	 0.5f,	 0.5f,
	    -0.5f,	 0.5f,	 0.5f,
	     0.5f,	-0.5f,	 0.5f
    };

  GLuint VBO_vertices_id, VAO_cube_id, VAO_light_cube_id;
  glGenVertexArrays(1, &VAO_cube_id);
  glGenBuffers(1, &VBO_vertices_id);

  glBindBuffer(GL_ARRAY_BUFFER, VBO_vertices_id);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindVertexArray(VAO_cube_id);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

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
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

  SceneObject light_cube;
  light_cube.name = "Light Cube";
  light_cube.first_index = (void *)0;
  light_cube.num_indices = 36;
  light_cube.rendering_mode = GL_TRIANGLES;
  light_cube.vertex_array_object_id = VAO_light_cube_id;
  this->virtualScene["light_cube"] = light_cube;
  glEnableVertexAttribArray(0);
}

void Scene5::Render()
{
  this->camera->Enable();

  this->shaders["color_shader"].use();
  this->camera->UpdateShaderUniforms(this->shaders["color_shader"]);
  this->shaders["color_shader"].setVec3("objectColor", 1.0f, 0.5f, 0.31f);
  this->shaders["color_shader"].setVec3("lightColor",  1.0f, 1.0f, 1.0f);

  glm::mat4 model = glm::mat4(1.0f);
  this->shaders["color_shader"].setMat4("model", model);

  this->shaders["color_shader"].setMat4("view", this->camera->view);
  this->shaders["color_shader"].setMat4("projection", this->camera->projection);

  glBindVertexArray(this->virtualScene["cube"].vertex_array_object_id);
  glDrawArrays(this->virtualScene["cube"].rendering_mode, 0, this->virtualScene["cube"].num_indices);

  this->shaders["light_shader"].use();
  this->camera->UpdateShaderUniforms(this->shaders["light_shader"]);
  model = glm::mat4(1.0f);
  model = glm::translate(model, this->lightPos);
  model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
  this->shaders["light_shader"].setMat4("model", model);

  glBindVertexArray(this->virtualScene["light_cube"].vertex_array_object_id);
  glDrawArrays(this->virtualScene["light_cube"].rendering_mode, 0, this->virtualScene["light_cube"].num_indices);
}
