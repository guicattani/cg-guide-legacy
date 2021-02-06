#ifndef CLASS_HEADER_SCENE
#define CLASS_HEADER_SCENE
#include "scene.h"
#endif

const char *Scene2::shader_vertex_filepath = "../src/scene_2_shader_vertex.glsl";
const char *Scene2::shader_fragment_filepath = "../src/scene_2_shader_fragment.glsl";

void Scene2::BuildTrianglesAndAddToVirtualScene()
{
  // create VAO and VBO
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  GLfloat vertices[] =
      {
          -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,  // top left
          0.5f, 0.5f, 0.0f, 1.0f, 0.0f,   // top right
          -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // bottom left

          0.5f, 0.5f, 0.0f, 1.0f, 0.0f,   // top right
          0.5f, -0.5f, 0.0f, 1.0f, 1.0f,  // bottom right
          -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // bottom left
      };
  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), NULL, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(2 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  SceneObject simple_plane;
  simple_plane.name = "Simple plane";
  simple_plane.first_index = (void *)0;       // Primeiro índice está em indices[0]
  simple_plane.num_indices = 30;              // último índice está em indices[35]; total de 36 índices.
  simple_plane.rendering_mode = GL_TRIANGLES; // índices correspondem ao tipo de rasterização GL_TRIANGLES.

  simple_plane.vertex_array_object_id = vao;
  Globals::g_VirtualScene["simple_plane"] = simple_plane;
}

void Scene2::Render()
{
  glBindVertexArray(Globals::g_VirtualScene["simple_plane"].vertex_array_object_id);
  glDrawArrays(Globals::g_VirtualScene["simple_plane"].rendering_mode, 0, 6);
  glBindVertexArray(0);
}