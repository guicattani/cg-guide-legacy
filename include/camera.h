#ifndef CLASS_HEADER_MATRICES
#define CLASS_HEADER_MATRICES
#include "matrices.h"
#endif

#ifndef CLASS_HEADER_INITIALIZE_GLOBALS
#define CLASS_HEADER_INITIALIZE_GLOBALS
#include "globals.h"
#endif

#ifndef CLASS_HEADER_SHADER
#define CLASS_HEADER_SHADER
#include "shader.h"
#endif

#ifndef CLASS_CAMERA_CLASS_HEADER
#define CLASS_CAMERA_CLASS_HEADER

using namespace std;

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
  Camera() {};
  void Enable();
};

class FreeCamera : public Camera
{
private:
  Quaternion quaternion;
public:
  glm::vec4 position = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
  glm::mat4 projection;
  glm::mat4 view;

  FreeCamera() : Camera() {};
  void Enable(map<string, Shader> shaders);
};

class Camera2D : public Camera
{
public:
  Camera2D() : Camera() {};
  void Enable();
};


#endif