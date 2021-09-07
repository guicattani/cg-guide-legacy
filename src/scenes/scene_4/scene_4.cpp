#include <iostream>
#ifndef CLASS_HEADER_SCENE
#define CLASS_HEADER_SCENE
#include "scene.h"
#endif

#ifndef CLASS_HEADER_BEZIER
#define CLASS_HEADER_BEZIER
#include "bezier.h"
#endif

// TODO make this call in Render()
void Scene4::CreateBezierLine()
{
  GLfloat bezier_line_coefficients[] = {
      // Posições em coordenadas homogêneas - vec4 - com último componente w=1 pois são pontos
      -1.0f, 1.0f, 1.0f, 1.0f, // posição do vértice 0
      -0.5f, 1.0f, 0.0f, 1.0f, // posição do vértice 1
      0.5f, 1.0f, 1.0f, 1.0f,  // posição do vértice 2
      1.0f, 1.0f, 0.0f, 1.0f   // posição do vértice 3
  };

  glGenBuffers(1, &VBO_bezier_line);

  GLuint vertex_array_object_id;
  glGenVertexArrays(1, &vertex_array_object_id);

  glBindVertexArray(vertex_array_object_id);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_bezier_line);
  glBufferData(GL_ARRAY_BUFFER, sizeof(bezier_line_coefficients), NULL, GL_DYNAMIC_DRAW);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(bezier_line_coefficients), bezier_line_coefficients);

  GLuint location = 0;            // "(location = 0)" em "shader_vertex.glsl"
  GLint number_of_dimensions = 4; // vec4 em "shader_vertex.glsl"
  glVertexAttribPointer(location, number_of_dimensions, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(location);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  GLuint indices[] = {
      0, 1,
      1, 2,
      2, 3};

  SceneObject bezier_lines;
  bezier_lines.name = "Bezier Lines";
  bezier_lines.first_index = (void *)0;
  bezier_lines.num_indices = 6;
  bezier_lines.rendering_mode = GL_LINES; // índices correspondem ao tipo de rasterização GL_LINES.
  bezier_lines.vertex_array_object_id = vertex_array_object_id;
  // Adicionamos o objeto criado acima na nossa cena virtual (this->virtualScene).
  this->virtualScene["bezier_lines"] = bezier_lines;

  // Criamos um buffer OpenGL para armazenar os índices acima
  GLuint indices_id;
  glGenBuffers(1, &indices_id);

  // "Ligamos" o buffer. Note que o tipo agora é GL_ELEMENT_ARRAY_BUFFER.
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_id);

  // Alocamos memória para o buffer.
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), NULL, GL_STATIC_DRAW);

  // Copiamos os valores do array indices[] para dentro do buffer.
  glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(indices), indices);

  glBindVertexArray(0);
}

void Scene4::Render()
{
  this->shaders["scene"].use();
  this->camera->Enable();
  this->camera->UpdateShaderUniforms(this->shaders["scene"]);

  glLineWidth(1.0f);

  glm::mat4 model = Matrix_Identity(); // Transformação identidade de modelagem

#define SPHERE 0
#define BUNNY 1
#define PLANE 2
#define BEZIER_LINE 3

  if(!g_HoldTime) {
    t = (double) last_frame / 100;
    bool flip = (int)t % 2 == 1;
    t = t - floor(t); // \in [0,1]
    t = flip ? 1.0 - t : t;
    t = 0.5f * sin(3.14f * (t - 0.5f)) + 0.5f;
    last_frame++;
  }

  vec3 p = bezier3(this->t, this->a, this->b, this->c, this->d);

  x = p.x;
  y = p.y;
  z = p.z;

  // Desenhamos o modelo do coelho
  model = Matrix_Translate(p.x, p.y, p.z) * Matrix_Rotate_Z(g_AngleZ) * Matrix_Rotate_Y(g_AngleY) * Matrix_Rotate_X(g_AngleX);
  shaders["scene"].setMat4("model", model);
  shaders["scene"].setInt("object_id", BUNNY);
  DrawVirtualObject(this->virtualScene["bunny"]);
  glBindVertexArray(0);

  // Desenhamos o plano do chão
  model = Matrix_Translate(0.0f, -1.0f, 0.0f) * Matrix_Scale(2.0f, 1.0f, 2.0f);
  shaders["scene"].setMat4("model", model);
  shaders["scene"].setInt("object_id", PLANE);
  DrawVirtualObject(this->virtualScene["plane"]);
  glBindVertexArray(0);

  // Desenha polígono de controle da curva de Bézier
  // clang-format off
  GLfloat bezier_line_coefficients[] = {
      // Posições em coordenadas homogêneas - vec4 - com último componente w=1 pois são pontos
      a.x, a.y, a.z, 1.0f,
      b.x, b.y, b.z, 1.0f,
      c.x, c.y, c.z, 1.0f,
      d.x, d.y, d.z, 1.0f,
  };
  // clang-format on

  glBindVertexArray(this->virtualScene["bezier_lines"].vertex_array_object_id);
  // Mexe no buffer dinamicamente, atualizando a posição dos vértices da linha.
  glBindBuffer(GL_ARRAY_BUFFER, VBO_bezier_line);
  // Utilizamos BufferSubData para alterar os valores sem realocar memória (glBufferData faz realocação).
  // glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * samples * 4, bezier_line_coefficients);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(bezier_line_coefficients), bezier_line_coefficients);

  model = Matrix_Identity(); // Reseta matriz de modelagem
  shaders["scene"].setMat4("model", model);
  shaders["scene"].setInt("object_id", BEZIER_LINE);
  glDrawElements(
      this->virtualScene["bezier_lines"].rendering_mode,
      this->virtualScene["bezier_lines"].num_indices,
      GL_UNSIGNED_INT,
      (void *)this->virtualScene["bezier_lines"].first_index);

  glPointSize(15.0f);
  for (int i = 0; i < 4; i++)
  {
    glDrawArrays(GL_POINTS, i, 1);
  }
  glBindVertexArray(0);
}
