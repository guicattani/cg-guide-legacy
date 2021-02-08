#ifndef CLASS_HEADER_SCENE
#define CLASS_HEADER_SCENE
#include "scene.h"
#endif

#ifndef CLASS_HEADER_BEZIER
#define CLASS_HEADER_BEZIER
#include "bezier.h"
#endif

const char *Scene4::shader_vertex_filepath = "../src/scene_4_shader_vertex.glsl";
const char *Scene4::shader_fragment_filepath = "../src/scene_4_shader_fragment.glsl";

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
  bezier_lines.name = "Linha Bezier";
  bezier_lines.first_index = (void *)0;
  bezier_lines.num_indices = 6;
  bezier_lines.rendering_mode = GL_LINES; // índices correspondem ao tipo de rasterização GL_LINES.
  bezier_lines.vertex_array_object_id = vertex_array_object_id;
  // Adicionamos o objeto criado acima na nossa cena virtual (Globals::g_VirtualScene).
  Globals::g_VirtualScene["bezier_lines"] = bezier_lines;

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

void Scene4::LoadShaderVariables(GLuint program_id)
{
  // Buscamos o endereço das variáveis definidas dentro do Vertex Shader.
  // Utilizaremos estas variáveis para enviar dados para a placa de vídeo
  // (GPU)! Veja arquivo "shader_vertex.glsl" e "shader_fragment.glsl".
  model_uniform = glGetUniformLocation(program_id, "model");           // Variável da matriz "model"
  view_uniform = glGetUniformLocation(program_id, "view");             // Variável da matriz "view" em shader_vertex.glsl
  projection_uniform = glGetUniformLocation(program_id, "projection"); // Variável da matriz "projection" em shader_vertex.glsl
  object_id_uniform = glGetUniformLocation(program_id, "object_id");   // Variável "object_id" em shader_fragment.glsl
}

void Scene4::BuildTrianglesAndAddToVirtualScene(ObjModel *model)
{
  GLuint vertex_array_object_id;
  glGenVertexArrays(1, &vertex_array_object_id);
  glBindVertexArray(vertex_array_object_id);

  std::vector<GLuint> indices;
  std::vector<float> model_coefficients;
  std::vector<float> normal_coefficients;
  std::vector<float> texture_coefficients;

  for (size_t shape = 0; shape < model->shapes.size(); ++shape)
  {
    size_t first_index = indices.size();
    size_t num_triangles = model->shapes[shape].mesh.num_face_vertices.size();

    for (size_t triangle = 0; triangle < num_triangles; ++triangle)
    {
      assert(model->shapes[shape].mesh.num_face_vertices[triangle] == 3);

      for (size_t vertex = 0; vertex < 3; ++vertex)
      {
        tinyobj::index_t idx = model->shapes[shape].mesh.indices[3 * triangle + vertex];

        indices.push_back(first_index + 3 * triangle + vertex);

        const float vx = model->attrib.vertices[3 * idx.vertex_index + 0];
        const float vy = model->attrib.vertices[3 * idx.vertex_index + 1];
        const float vz = model->attrib.vertices[3 * idx.vertex_index + 2];
        //printf("tri %d vert %d = (%.2f, %.2f, %.2f)\n", (int)triangle, (int)vertex, vx, vy, vz);
        model_coefficients.push_back(vx);   // X
        model_coefficients.push_back(vy);   // Y
        model_coefficients.push_back(vz);   // Z
        model_coefficients.push_back(1.0f); // W

        // Inspecionando o código da tinyobjloader, o aluno Bernardo
        // Sulzbach (2017/1) apontou que a maneira correta de testar se
        // existem normais e coordenadas de textura no ObjModel é
        // comparando se o índice retornado é -1. Fazemos isso abaixo.

        if (idx.normal_index != -1)
        {
          const float nx = model->attrib.normals[3 * idx.normal_index + 0];
          const float ny = model->attrib.normals[3 * idx.normal_index + 1];
          const float nz = model->attrib.normals[3 * idx.normal_index + 2];
          normal_coefficients.push_back(nx);   // X
          normal_coefficients.push_back(ny);   // Y
          normal_coefficients.push_back(nz);   // Z
          normal_coefficients.push_back(0.0f); // W
        }

        if (idx.texcoord_index != -1)
        {
          const float u = model->attrib.texcoords[2 * idx.texcoord_index + 0];
          const float v = model->attrib.texcoords[2 * idx.texcoord_index + 1];
          texture_coefficients.push_back(u);
          texture_coefficients.push_back(v);
        }
      }
    }

    size_t last_index = indices.size() - 1;

    SceneObject theobject;
    theobject.name = model->shapes[shape].name;
    theobject.first_index = (void *)first_index;          // Primeiro índice
    theobject.num_indices = last_index - first_index + 1; // Número de indices
    theobject.rendering_mode = GL_TRIANGLES;              // Índices correspondem ao tipo de rasterização GL_TRIANGLES.
    theobject.vertex_array_object_id = vertex_array_object_id;

    Globals::g_VirtualScene[model->shapes[shape].name] = theobject;
  }

  GLuint VBO_model_coefficients_id;
  glGenBuffers(1, &VBO_model_coefficients_id);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_model_coefficients_id);
  glBufferData(GL_ARRAY_BUFFER, model_coefficients.size() * sizeof(float), NULL, GL_STATIC_DRAW);
  glBufferSubData(GL_ARRAY_BUFFER, 0, model_coefficients.size() * sizeof(float), model_coefficients.data());
  GLuint location = 0;            // "(location = 0)" em "shader_vertex.glsl"
  GLint number_of_dimensions = 4; // vec4 em "shader_vertex.glsl"
  glVertexAttribPointer(location, number_of_dimensions, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(location);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  if (!normal_coefficients.empty())
  {
    GLuint VBO_normal_coefficients_id;
    glGenBuffers(1, &VBO_normal_coefficients_id);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_normal_coefficients_id);
    glBufferData(GL_ARRAY_BUFFER, normal_coefficients.size() * sizeof(float), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, normal_coefficients.size() * sizeof(float), normal_coefficients.data());
    location = 1;             // "(location = 1)" em "shader_vertex.glsl"
    number_of_dimensions = 4; // vec4 em "shader_vertex.glsl"
    glVertexAttribPointer(location, number_of_dimensions, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(location);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  if (!texture_coefficients.empty())
  {
    GLuint VBO_texture_coefficients_id;
    glGenBuffers(1, &VBO_texture_coefficients_id);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_texture_coefficients_id);
    glBufferData(GL_ARRAY_BUFFER, texture_coefficients.size() * sizeof(float), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, texture_coefficients.size() * sizeof(float), texture_coefficients.data());
    location = 2;             // "(location = 1)" em "shader_vertex.glsl"
    number_of_dimensions = 2; // vec2 em "shader_vertex.glsl"
    glVertexAttribPointer(location, number_of_dimensions, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(location);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  GLuint indices_id;
  glGenBuffers(1, &indices_id);

  // "Ligamos" o buffer. Note que o tipo agora é GL_ELEMENT_ARRAY_BUFFER.
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_id);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), NULL, GL_STATIC_DRAW);
  glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indices.size() * sizeof(GLuint), indices.data());
  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // XXX Errado!
  //

  // "Desligamos" o VAO, evitando assim que operações posteriores venham a
  // alterar o mesmo. Isso evita bugs.
  glBindVertexArray(0);
}

void Scene4::Render()
{
  glLineWidth(1.0f);

  glm::mat4 model = Matrix_Identity(); // Transformação identidade de modelagem

  // Enviamos as matrizes "view" e "projection" para a placa de vídeo
  // (GPU). Veja o arquivo "shader_vertex.glsl", onde estas são
  // efetivamente aplicadas em todos os pontos.
  glUniformMatrix4fv(view_uniform, 1, GL_FALSE, glm::value_ptr(g_MainCamera->view));
  glUniformMatrix4fv(projection_uniform, 1, GL_FALSE, glm::value_ptr(g_MainCamera->projection));

#define SPHERE 0
#define BUNNY 1
#define PLANE 2
#define BEZIER_LINE 3

  // Desenhamos o modelo da esfera
  // model = Matrix_Translate(-1.0f,0.0f,0.0f);
  // glUniformMatrix4fv(model_uniform, 1 , GL_FALSE , glm::value_ptr(model));
  // glUniform1i(object_id_uniform, SPHERE);
  // DrawVirtualObject("sphere");

  // Desenhamos o modelo do coelho
  t = glfwGetTime() / 2;
  bool flip = (int)t % 2 == 1;
  t = t - floor(t); // \in [0,1]
  t = flip ? 1.0 - t : t;
  t = 0.5f * sin(3.14f * (t - 0.5f)) + 0.5f;

  auto p = bezier3(t, a, b, c, d);

  x = p.x;
  y = p.y;
  z = p.z;

  model = Matrix_Translate(p.x, p.y, p.z) * Matrix_Rotate_Z(g_AngleZ) * Matrix_Rotate_Y(g_AngleY) * Matrix_Rotate_X(g_AngleX);
  glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(model));
  glUniform1i(object_id_uniform, BUNNY);
  DrawVirtualObject("bunny");
  glBindVertexArray(0);

  // Desenhamos o plano do chão
  model = Matrix_Translate(0.0f, -1.0f, 0.0f) * Matrix_Scale(2.0f, 1.0f, 2.0f);
  glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(model));
  glUniform1i(object_id_uniform, PLANE);
  DrawVirtualObject("plane");
  glBindVertexArray(0);

  // int samples = 8;
  // GLfloat *bezier_line_coefficients = new GLfloat[samples * 4];
  // sampledBezierPoints(bezier_line_coefficients, samples, a, b, c, d);
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

  glBindVertexArray(Globals::g_VirtualScene["bezier_lines"].vertex_array_object_id);
  // Mexe no buffer dinamicamente, atualizando a posição dos vértices da linha.
  glBindBuffer(GL_ARRAY_BUFFER, VBO_bezier_line);
  // Utilizamos BufferSubData para alterar os valores sem realocar memória (glBufferData faz realocação).
  // glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * samples * 4, bezier_line_coefficients);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(bezier_line_coefficients), bezier_line_coefficients);

  // delete[] bezier_line_coefficients;

  model = Matrix_Identity(); // Reseta matriz de modelagem
  glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(model));
  glUniform1i(object_id_uniform, BEZIER_LINE);
  DrawVirtualObject("bezier_lines");

  glPointSize(15.0f);
  for (int i = 0; i < 4; i++)
  {
    glDrawArrays(GL_POINTS, i, 1);
  }
  glBindVertexArray(0);
}