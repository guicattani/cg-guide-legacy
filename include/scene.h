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

#ifndef CLASS_HEADER_CAMERA
#define CLASS_HEADER_CAMERA
#include "camera.h"
#endif

#ifndef CLASS_HEADER_SHADER
#define CLASS_HEADER_SHADER
#include "shader.h"
#endif

using namespace std;

class Scene2
{
private:
  static const float pi;
  static const int zero_vertices;
  static const int one_vertices;

  static const int num_of_digits;

  static const float zero_up_radius_small;
  static const float zero_up_radius_big;
  static const float zero_side_radius_small;
  static const float zero_side_radius_big;
public:
  Camera2D* camera;
  int seconds;
  Shader shader = Shader("../src/shaders/scene_2_shader_vertex.glsl",
                         "../src/shaders/scene_2_shader_fragment.glsl");

  GLuint BuildTriangles(int seconds, bool isAOne, int digitLocation);
  void Render();
};

class Scene3
{
public:
  map<string, SceneObject> virtualScene;
  map<string, Shader> shaders;
  FreeCamera* camera;

  void BuildTrianglesAndAddToVirtualScene();
  void Render();

  Scene3() {
    shaders["scene"] = Shader("../src/shaders/scene_3_shader_vertex.glsl",
                              "../src/shaders/scene_3_shader_fragment.glsl");
  }
};

class Scene4
{
private:
  GLuint VBO_bezier_line;
  GLfloat bezier_line_coefficients[12];

  int last_frame = -1;

public:
  map<string, ObjModel> sceneModels;
  map<string, SceneObject> virtualScene;
  map<string, Shader> shaders;
  FreeCamera* camera;
  static int bezier_samples;

  float t = 0;
  float x;
  float y;
  float z;

  glm::vec3 a = glm::vec3(1.0f, 0.0f, 1.0f);
  glm::vec3 b = glm::vec3(1.0f, 3.0f, 0.0f);
  glm::vec3 c = glm::vec3(-1.0f, -2.0f, 0.0f);
  glm::vec3 d = glm::vec3(-1.0f, 1.0f, -1.0f);

  void CreateBezierLine();
  void BuildTrianglesAndAddToVirtualScene(ObjModel *model);
  void Render();

  Scene4() {
    shaders["scene"] = Shader("../src/shaders/scene_4_shader_vertex.glsl",
                              "../src/shaders/scene_4_shader_fragment.glsl");
  }
};