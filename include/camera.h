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
using namespace glm;

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
public:
  Quaternion quaternion;
  float theta;
  float phi;

  float nearPlane = -1.0f;
  float farPlane = -55.0f;

  vec4 position = vec4(0.0f, 0.0f, 0.0f, 1.0f);
  mat4 projection;
  mat4 view;

  FreeCamera(vec4 position = vec4(0.0f, 0.0f, 0.0f, 1.0f), float theta = 0.0f, float phi = 0.0f) : Camera() {
    this->position = position;
    this->theta = theta;
    this->phi = phi;
  };
  void Enable(float screenRatio = g_ScreenRatio, bool mouseOver = true);
  void UpdateShaderUniforms(Shader shader);
};

class HybridCamera : public Camera
{
public:
  bool isFreeCamera = true;
  bool usePerspectiveProjection = true;

  Quaternion quaternion;
  float theta;
  float phi;

  float nearPlane = -1.0f;
  float farPlane = -55.0f;
  float cameraDistanceFromOrigin = 2.0f;
  float screenRatio = 1.0f;

  float fieldOfView = 3.141592 / 3.0f;

  vec4 cameraViewVector;
  vec4 lookAt = vec4(0.0f, 0.0f, 1.0f, 1.0f);
  vec4 position = vec4(0.0f, 0.0f, 0.0f, 1.0f);
  mat4 projection;
  mat4 view;

  HybridCamera(vec4 position = vec4(0.0f, 0.0f, 0.0f, 1.0f), float theta = 0.0f, float phi = 0.0f) : Camera() {
    this->position = position;
    this->theta = theta;
    this->phi = phi;
  };
  void Enable(float screenRatio = g_ScreenRatio, bool mouseOver = true);
  void UpdateShaderUniforms(Shader shader);
};

class Camera2D : public Camera
{
public:
  vec4 position = vec4(0.0f, 0.0f, 0.0f, 1.0f);
  mat4 projection;
  mat4 view;

  Camera2D() : Camera() {};
  void Enable(float screenRatio = g_ScreenRatio);
  void UpdateShaderUniforms(Shader shader);
};

#endif