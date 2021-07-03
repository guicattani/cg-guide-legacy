#ifndef CLASS_HEADER_SCENE
#define CLASS_HEADER_SCENE
#include "scene.h"
#endif

GLuint Scene8::BuildTriangle()
{
  GLfloat triangle_vertices[] = {
    -0.5f, -0.5f, 0.0f, first_vertex_color.x,  first_vertex_color.y,  first_vertex_color.z,
     0.5f, -0.5f, 0.0f, second_vertex_color.x, second_vertex_color.y, second_vertex_color.z,
     0.0f,  0.5f, 0.0f, third_vertex_color.x,  third_vertex_color.y,  third_vertex_color.z
  };

  GLuint VBO_triangles_id;
  glGenBuffers(1, &VBO_triangles_id);

  glBindBuffer(GL_ARRAY_BUFFER, VBO_triangles_id);
  glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);

  glGenVertexArrays(1, &VAO_triangle_id);
  // position coefficients
  glBindVertexArray(VAO_triangle_id);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) 0);
  glEnableVertexAttribArray(0);

  // color coefficients
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  return VAO_triangle_id;
}


void Scene8::Render()
{
  this->shader.use();
  this->camera->UpdateShaderUniforms(this->shader);

  GLuint vertex_array_object_id = BuildTriangle();
  glBindVertexArray(vertex_array_object_id);

  int display_w, display_h;
  glfwGetFramebufferSize(g_Window, &display_w, &display_h);

  glViewport(0, 0, display_w/2, display_h);
  this->camera->Enable((float) (display_w/2)/display_h);
  glDrawArrays(GL_TRIANGLES, 0, 3);

  glViewport(display_w/2, 0, display_w/2, display_h);
  this->camera->Enable((float) (display_w/2)/display_h);
  glDrawArrays(GL_TRIANGLES, 0, 3);
}