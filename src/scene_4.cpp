#ifndef CLASS_HEADER_SCENE
#define CLASS_HEADER_SCENE
#include "scene.h"
#endif

#ifndef CLASS_HEADER_BEZIER
#define CLASS_HEADER_BEZIER
#include "bezier.h"
#endif

const char * Scene_4::shader_vertex_filepath = "../src/scene_4_shader_vertex.glsl";
const char * Scene_4::shader_fragment_filepath = "../src/scene_4_shader_fragment.glsl";

void Scene_4::LoadShaderVariables(GLuint program_id) {
  // Buscamos o endereço das variáveis definidas dentro do Vertex Shader.
  // Utilizaremos estas variáveis para enviar dados para a placa de vídeo
  // (GPU)! Veja arquivo "shader_vertex.glsl" e "shader_fragment.glsl".
  model_uniform           = glGetUniformLocation(program_id, "model"); // Variável da matriz "model"
  view_uniform            = glGetUniformLocation(program_id, "view"); // Variável da matriz "view" em shader_vertex.glsl
  projection_uniform      = glGetUniformLocation(program_id, "projection"); // Variável da matriz "projection" em shader_vertex.glsl
  object_id_uniform       = glGetUniformLocation(program_id, "object_id"); // Variável "object_id" em shader_fragment.glsl
}

void Scene_4::BuildTrianglesAndAddToVirtualScene(ObjModel* model) {
  GLuint vertex_array_object_id;
  glGenVertexArrays(1, &vertex_array_object_id);
  glBindVertexArray(vertex_array_object_id);

  std::vector<GLuint> indices;
  std::vector<float>  model_coefficients;
  std::vector<float>  normal_coefficients;
  std::vector<float>  texture_coefficients;

  for (size_t shape = 0; shape < model->shapes.size(); ++shape)
  {
    size_t first_index = indices.size();
    size_t num_triangles = model->shapes[shape].mesh.num_face_vertices.size();

    for (size_t triangle = 0; triangle < num_triangles; ++triangle)
    {
        assert(model->shapes[shape].mesh.num_face_vertices[triangle] == 3);

        for (size_t vertex = 0; vertex < 3; ++vertex)
        {
            tinyobj::index_t idx = model->shapes[shape].mesh.indices[3*triangle + vertex];

            indices.push_back(first_index + 3*triangle + vertex);

            const float vx = model->attrib.vertices[3*idx.vertex_index + 0];
            const float vy = model->attrib.vertices[3*idx.vertex_index + 1];
            const float vz = model->attrib.vertices[3*idx.vertex_index + 2];
            //printf("tri %d vert %d = (%.2f, %.2f, %.2f)\n", (int)triangle, (int)vertex, vx, vy, vz);
            model_coefficients.push_back( vx ); // X
            model_coefficients.push_back( vy ); // Y
            model_coefficients.push_back( vz ); // Z
            model_coefficients.push_back( 1.0f ); // W

            // Inspecionando o código da tinyobjloader, o aluno Bernardo
            // Sulzbach (2017/1) apontou que a maneira correta de testar se
            // existem normais e coordenadas de textura no ObjModel é
            // comparando se o índice retornado é -1. Fazemos isso abaixo.

            if ( idx.normal_index != -1 )
            {
                const float nx = model->attrib.normals[3*idx.normal_index + 0];
                const float ny = model->attrib.normals[3*idx.normal_index + 1];
                const float nz = model->attrib.normals[3*idx.normal_index + 2];
                normal_coefficients.push_back( nx ); // X
                normal_coefficients.push_back( ny ); // Y
                normal_coefficients.push_back( nz ); // Z
                normal_coefficients.push_back( 0.0f ); // W
            }

            if ( idx.texcoord_index != -1 )
            {
                const float u = model->attrib.texcoords[2*idx.texcoord_index + 0];
                const float v = model->attrib.texcoords[2*idx.texcoord_index + 1];
                texture_coefficients.push_back( u );
                texture_coefficients.push_back( v );
            }
        }
    }

    size_t last_index = indices.size() - 1;

    SceneObject theobject;
    theobject.name           = model->shapes[shape].name;
    theobject.first_index    = (void*)first_index; // Primeiro índice
    theobject.num_indices    = last_index - first_index + 1; // Número de indices
    theobject.rendering_mode = GL_TRIANGLES;       // Índices correspondem ao tipo de rasterização GL_TRIANGLES.
    theobject.vertex_array_object_id = vertex_array_object_id;

    Globals::g_VirtualScene[model->shapes[shape].name] = theobject;
  }

  GLuint VBO_model_coefficients_id;
  glGenBuffers(1, &VBO_model_coefficients_id);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_model_coefficients_id);
  glBufferData(GL_ARRAY_BUFFER, model_coefficients.size() * sizeof(float), NULL, GL_STATIC_DRAW);
  glBufferSubData(GL_ARRAY_BUFFER, 0, model_coefficients.size() * sizeof(float), model_coefficients.data());
  GLuint location = 0; // "(location = 0)" em "shader_vertex.glsl"
  GLint  number_of_dimensions = 4; // vec4 em "shader_vertex.glsl"
  glVertexAttribPointer(location, number_of_dimensions, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(location);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  if ( !normal_coefficients.empty() )
  {
    GLuint VBO_normal_coefficients_id;
    glGenBuffers(1, &VBO_normal_coefficients_id);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_normal_coefficients_id);
    glBufferData(GL_ARRAY_BUFFER, normal_coefficients.size() * sizeof(float), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, normal_coefficients.size() * sizeof(float), normal_coefficients.data());
    location = 1; // "(location = 1)" em "shader_vertex.glsl"
    number_of_dimensions = 4; // vec4 em "shader_vertex.glsl"
    glVertexAttribPointer(location, number_of_dimensions, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(location);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  if ( !texture_coefficients.empty() )
  {
    GLuint VBO_texture_coefficients_id;
    glGenBuffers(1, &VBO_texture_coefficients_id);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_texture_coefficients_id);
    glBufferData(GL_ARRAY_BUFFER, texture_coefficients.size() * sizeof(float), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, texture_coefficients.size() * sizeof(float), texture_coefficients.data());
    location = 2; // "(location = 1)" em "shader_vertex.glsl"
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
void Scene_4::Render() {
  glm::mat4 model = Matrix_Identity(); // Transformação identidade de modelagem

  // Enviamos as matrizes "view" e "projection" para a placa de vídeo
  // (GPU). Veja o arquivo "shader_vertex.glsl", onde estas são
  // efetivamente aplicadas em todos os pontos.
  glUniformMatrix4fv(view_uniform       , 1 , GL_FALSE , glm::value_ptr(g_MainCamera->view));
  glUniformMatrix4fv(projection_uniform , 1 , GL_FALSE , glm::value_ptr(g_MainCamera->projection));

  #define SPHERE 0
  #define BUNNY  1
  #define PLANE  2

  // Desenhamos o modelo da esfera
  // model = Matrix_Translate(-1.0f,0.0f,0.0f);
  // glUniformMatrix4fv(model_uniform, 1 , GL_FALSE , glm::value_ptr(model));
  // glUniform1i(object_id_uniform, SPHERE);
  // DrawVirtualObject("sphere");

  // Desenhamos o modelo do coelho
  float t = glfwGetTime();
  t = t / 2;
  bool flip = (int)t % 2 == 1;
  t = t - floor(t); // \in [0,1]
  t = flip ? 1.0-t : t;
  t = 0.5f*sin(M_PI * (t-0.5f)) + 0.5f;
  glm::vec3 a = glm::vec3(1.0f,0.0f,1.0f);
  glm::vec3 b = glm::vec3(1.0f,3.0f,0.0f);
  glm::vec3 c = glm::vec3(-1.0f,-2.0f,0.0f);
  glm::vec3 d = glm::vec3(-1.0f,1.0f,-1.0f);
  auto p = bezier3(t, a,b,c,d);
  model = Matrix_Translate(p.x,p.y,p.z)
        * Matrix_Rotate_Z(g_AngleZ)
        * Matrix_Rotate_Y(g_AngleY)
        * Matrix_Rotate_X(g_AngleX);
  glUniformMatrix4fv(model_uniform, 1 , GL_FALSE , glm::value_ptr(model));
  glUniform1i(object_id_uniform, BUNNY);
  DrawVirtualObject("bunny");

  // Desenhamos o plano do chão
  model = Matrix_Translate(0.0f,-1.0f,0.0f) * Matrix_Scale(2.0f,1.0f,2.0f);
  glUniformMatrix4fv(model_uniform, 1 , GL_FALSE , glm::value_ptr(model));
  glUniform1i(object_id_uniform, PLANE);
  DrawVirtualObject("plane");
}