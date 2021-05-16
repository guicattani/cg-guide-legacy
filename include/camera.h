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
public:
  Camera(GLuint program_id) {};
  void Enable();
};

class FreeCamera : public Camera
{
private:
  Quaternion quaternion;
  GLint view_uniform;       // Variável da matriz "view" em shader_vertex.glsl
  GLint projection_uniform; // Variável da matriz "projection" em shader_vertex.glsl
public:
  glm::vec4 position;
  glm::mat4 projection;
  glm::mat4 view;

  FreeCamera(GLuint program_id) : Camera(program_id) {
    position = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

    view_uniform = glGetUniformLocation(program_id, "camera_view");
    projection_uniform = glGetUniformLocation(program_id, "camera_projection");
  };
  void Enable();
};

class Camera2D : public Camera
{
public:
  Camera2D(GLuint program_id) : Camera(program_id) {};
  void Enable();
};


#endif