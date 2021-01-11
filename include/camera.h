#ifndef CLASS_HEADER_MATRICES
#define CLASS_HEADER_MATRICES
#include "matrices.h"
#endif

#ifndef CLASS_HEADER_INITIALIZE_GLOBALS
#define CLASS_HEADER_INITIALIZE_GLOBALS
#include "globals.h"
#endif

#ifndef CLASS_CAMERA_CLASS_HEADER
#define CLASS_CAMERA_CLASS_HEADER
class Quaternion
{
public:
  float x;
  float y;
  float z;
};

class Camera
{
private:
  Quaternion quaternion;
  glm::vec4 position;
  GLint view_uniform;       // Variável da matriz "view" em shader_vertex.glsl
  GLint projection_uniform; // Variável da matriz "projection" em shader_vertex.glsl
public:
  glm::mat4 projection;
  glm::mat4 view;

  Camera(GLuint program_id);
  void Enable();
};
#endif