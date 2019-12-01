#ifndef CLASS_ADD_HEADERS
#define CLASS_ADD_HEADERS
#include "headers.h"
#endif

#ifndef CLASS_HEADER_INITIALIZE_GLOBALS
#define CLASS_HEADER_INITIALIZE_GLOBALS
#include "globals.h"
#endif

#ifndef CLASS_HEADER_MODEL_LOADER
#define CLASS_HEADER_MODEL_LOADER
#include "model_loader.h"
#endif

#ifndef CLASS_HEADER_MATRICES
#define CLASS_HEADER_MATRICES
#include "matrices.h"
#endif

#ifndef CLASS_SCENE_CLASS_HEADER
#define CLASS_SCENE_CLASS_HEADER
class Scene_3 {
  private:
    GLint model_uniform;
    GLint render_as_black_uniform;

  public:
    static const char* shader_vertex_filepath;
    static const char* shader_fragment_filepath;

    void LoadShaderVariables(GLuint program_id);
    void BuildTrianglesAndAddToVirtualScene();
    void Render();
};

class Scene_4 {
  public:
    std::string shader_vertex_filepath = "../src/scene_4_shader_vertex.glsl";
    std::string shader_fragment_file_filepath = "../sr c/scene_4_shader_fragment.glsl";

    GLint model_uniform;
    GLint view_uniform;
    GLint projection_uniform;
    GLint object_id_uniform;

    void LoadShaderVariables(GLuint program_id);
    void BuildTrianglesAndAddToVirtualScene(ObjModel*);
    void Render();
};
#endif