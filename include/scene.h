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
using namespace glm;

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
  Shader shader = Shader("../src/scenes/scene_2/shader_scene.vert",
                         "../src/scenes/scene_2/shader_scene.frag");

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
    shaders["scene"] = Shader("../src/scenes/scene_3/shader_scene.vert",
                              "../src/scenes/scene_3/shader_scene.frag");
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

  vec3 a = vec3(1.0f, 0.0f, 1.0f);
  vec3 b = vec3(1.0f, 3.0f, 0.0f);
  vec3 c = vec3(-1.0f, -2.0f, 0.0f);
  vec3 d = vec3(-1.0f, 1.0f, -1.0f);

  void CreateBezierLine();
  void BuildTrianglesAndAddToVirtualScene(ObjModel *model);
  void Render();

  Scene4() {
    shaders["scene"] = Shader("../src/scenes/scene_4/shader_scene.vert",
                              "../src/scenes/scene_4/shader_scene.frag");
  }
};

class Scene5
{
public:
  map<string, SceneObject> virtualScene;
  map<string, Shader> shaders;
  FreeCamera* camera;

  float ambientStrength = 0.1f;
  float gouradSpecularStrength = 0.0f;
  float phongSpecularStrength = 1.0f;
  float diffuseStrength = 1.0f;
  vec3 lightPos = vec3(0.5f, 0.0f, 1.6f);

  void LoadShaderVariables();
  void BuildTrianglesAndAddToVirtualScene();
  void Render();

  Scene5() {
    shaders["color_shader"] = Shader("../src/scenes/scene_5/shader_color.vert",
                                     "../src/scenes/scene_5/shader_color.frag");
    shaders["light_shader"] = Shader("../src/scenes/scene_5/shader_light.vert",
                                     "../src/scenes/scene_5/shader_light.frag");
  }
};

class Scene6
{
public:
  struct Material {
      GLuint diffuseTextureId;
      GLuint specularTextureId;
      vec3 ambient;
      vec3 diffuse;
      vec3 specular;
      float shininess;
  };

  struct Light {
      vec3 position;
      vec3 ambient;
      vec3 diffuse;
      vec3 specular;
  };

  bool useTexture = false;
  bool useDiffuseTexture = true;
  bool useSpecularTexture = true;
  float gouradSpecularStrength = 0.0f;
  map<string, SceneObject> virtualScene;
  map<string, Shader> shaders;
  FreeCamera* camera;
  Material* material;
  Light* light;

  void LoadShaderVariables();
  void BuildTrianglesAndAddToVirtualScene();
  void Render();

  Scene6() {
    material = new Material { 0,
                              0,
                              vec3(1.0f, 0.5f, 0.31f),
                              vec3(1.0f, 0.5f, 0.31f),
                              vec3(0.5f, 0.5f, 0.5f),
                              32.0f };

    light = new Light { vec3(1.2f, 1.0f, 2.0f),
                        vec3(1.0f, 1.0f, 1.0f),
                        vec3(1.0f, 1.0f, 1.0f),
                        vec3(1.0f, 1.0f, 1.0f) };

    shaders["color_shader"] = Shader("../src/scenes/scene_6/shader_color.vert",
                                     "../src/scenes/scene_6/shader_color.frag");
    shaders["light_shader"] = Shader("../src/scenes/scene_6/shader_light.vert",
                                     "../src/scenes/scene_6/shader_light.frag");
  }
};

class Scene7
{
public:
  struct Material {
      GLuint diffuseTextureId;
      GLuint specularTextureId;
      vec3 ambient;
      vec3 diffuse;
      vec3 specular;
      float shininess;
  };

  bool directionalLightOn = true;
  struct DirectionalLight {
      vec3 direction;
      vec3 ambient;
      vec3 diffuse;
      vec3 specular;
  };

  bool pointLightOn = true;
  struct PointLight {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
  };

  bool useTexture = false;
  bool useDiffuseTexture = true;
  bool useSpecularTexture = true;
  float gouradSpecularStrength = 0.0f;
  map<string, SceneObject> virtualScene;
  map<string, Shader> shaders;
  FreeCamera* camera;
  Material* material;
  DirectionalLight* directional_light;
  PointLight* point_light;

  void LoadShaderVariables();
  void BuildTrianglesAndAddToVirtualScene();
  void Render();

  Scene7() {
    material = new Material { 0,
                              0,
                              vec3(1.0f, 0.5f, 0.31f),
                              vec3(1.0f, 0.5f, 0.31f),
                              vec3(0.5f, 0.5f, 0.5f),
                              32.0f };

    directional_light = new DirectionalLight { vec3(-1.2f, -1.0f, -2.0f),
                                               vec3( 0.5f,  0.5f,  0.5f),
                                               vec3( 0.5f,  0.5f,  0.5f),
                                               vec3( 0.5f,  0.5f,  0.5f) };

    point_light = new PointLight { vec3(2.0f, 1.0f, 2.0f),
                                   vec3(0.5f, 0.5f, 0.5f),
                                   vec3(0.5f, 0.5f, 0.5f),
                                   vec3(0.5f, 0.5f, 0.5f),
                                   1.0f,
                                   0.09f,
                                   0.032f };

    shaders["color_shader"] = Shader("../src/scenes/scene_7/shader_color.vert",
                                     "../src/scenes/scene_7/shader_color.frag");
    shaders["light_shader"] = Shader("../src/scenes/scene_7/shader_light.vert",
                                     "../src/scenes/scene_7/shader_light.frag");
    shaders["plane_shader"] = Shader("../src/scenes/scene_7/shader_plane.vert",
                                     "../src/scenes/scene_7/shader_plane.frag");
  }
};