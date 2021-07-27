#include <stdio.h>
#include "imgui.h"
#include "imgui_markdown.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <ft2build.h>
#include FT_FREETYPE_H

// About Desktop OpenGL function loaders:
//  Modern desktop OpenGL doesn't have a standard portable header file to load OpenGL function pointers.
//  Helper libraries are often used for this purpose! Here we are supporting a few common ones (gl3w, glew, glad).
//  You may use another loader/header of your choice (glext, glLoadGen, etc.), or chose to manually implement your own.
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h> // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h> // Initialize with glewInit()
#endif

#include <GLFW/glfw3.h>
#include <cmath>
#include <cstdio>
#include <cstdlib>

// Headers abaixo são específicos de C++
#include <map>
#include <string>
#include <fstream>
#include <sstream>

// Headers da biblioteca GLM: criação de matrizes e vetores.
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>

// Headers da biblioteca para carregar modelos obj
#include <tiny_obj_loader.h>

#ifndef CLASS_STRUCTS
#define CLASS_STRUCTS
// Definimos uma estrutura que armazenará dados necessários para renderizar
// cada objeto da cena virtual.
struct SceneObject
{
  std::string name;              // Nome do objeto
  void *first_index;             // índice do primeiro vértice dentro do vetor indices[] definido em BuildTriangles()
  int num_indices;               // Número de índices do objeto dentro do vetor indices[] definido em BuildTriangles()
  GLenum rendering_mode;         // Modo de rasterização (GL_TRIANGLES, GL_TRIANGLE_STRIP, etc.)
  GLuint vertex_array_object_id; // ID do VAO onde estão armazenados os atributos do modelo
  glm::vec3 bbox_min;            // Axis-Aligned Bounding Box do objeto
  glm::vec3 bbox_center;
  glm::vec3 bbox_max;
};

// Hold image attributes
class Image {
public:
  glm::vec2 size;
  GLuint texture_id;
};

struct Character {
    unsigned int TextureID;  // ID handle of the glyph texture
    glm::ivec2   Size;       // Size of glyph
    glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
    unsigned int Advance;    // Offset to advance to next glyph
};

struct MinMax {
public:
  float min;
  float max;
};

class GraphMinMax {
public:
  MinMax x;
  MinMax y;
  MinMax z;

  GraphMinMax() {
    x = MinMax{100.0f, -100.0f};
    y = MinMax{100.0f, -100.0f};
    z = MinMax{100.0f, -100.0f};
  }
};

// Estrutura que representa um modelo geométrico carregado a partir de um
// arquivo ".obj". Veja https://en.wikipedia.org/wiki/Wavefront_.obj_file .
struct ObjModel
{
  tinyobj::attrib_t attrib;
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;

  ObjModel() {};
  // Este construtor lê o modelo de um arquivo utilizando a biblioteca tinyobjloader.
  // Veja: https://github.com/syoyo/tinyobjloader
  ObjModel(const char *filename, const char *basepath = NULL, bool triangulate = true)
  {
    printf("Carregando modelo \"%s\"... ", filename);

    std::string err;
    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, filename, basepath, triangulate);

    if (!err.empty())
      fprintf(stderr, "\n%s\n", err.c_str());

    if (!ret)
      throw std::runtime_error("Erro ao carregar modelo.");
    printf("OK.\n");
  }
};

static ImGui::MarkdownConfig mdConfig;

#ifdef _WIN32
  #include <Windows.h>
  #include "Shellapi.h"
#endif

#endif
