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

class Scene1
{
private:
  GLuint VAO_triangle_id;
public:
  class Part1 {
  private:
    GLuint VAO_triangle_id;
  public:
    Camera2D* camera;

    GLuint BuildTriangle();
    void Render();

    Part1() {
      camera = new Camera2D();
    }
  };

  vec3 first_vertex_color  = vec3(1.0f,0.0f,0.0f);
  vec3 second_vertex_color = vec3(0.0f,1.0f,0.0f);
  vec3 third_vertex_color  = vec3(0.0f,0.0f,1.0f);
  Camera2D* camera;
  Shader shader = Shader("../src/scenes/scene_1/shader_scene.vert",
                         "../src/scenes/scene_1/shader_scene.frag");

  unsigned int current_part = 2;
  GLuint BuildTriangle();
  void Render();

  Scene1() {
    camera = new Camera2D();
  }
};

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

  unsigned int current_part = 1;
  GLuint BuildTriangles(int seconds, bool isAOne, int digitLocation);
  void Render();

  Scene2() {
    camera = new Camera2D();
  }
};

class Scene3
{
public:
  map<string, SceneObject> virtualScene;
  map<string, Shader> shaders;
  HybridCamera* camera;

  mat4 inspectable_model;
  vec3 translation = vec3(-2.0f,0.0f,0.0f);
  float angleZ = 0.0f;
  float angleY = 0.0f;
  float angleX = 0.0f;

  unsigned int current_part = 1;
  void BuildTrianglesAndAddToVirtualScene();
  void Render();

  Scene3() {
    shaders["scene"] = Shader("../src/scenes/scene_3/shader_scene.vert",
                              "../src/scenes/scene_3/shader_scene.frag");
    camera = new HybridCamera(vec4(-3.0f,1.5f,3.0f,1.0f), 2.4f, 0.4f);
    BuildTrianglesAndAddToVirtualScene();
  }
};

class Scene4
{
private:
  GLuint VBO_bezier_line;
  int last_frame = -1;

public:
  map<string, ObjModel> sceneModels;
  map<string, SceneObject> virtualScene;
  map<string, Shader> shaders;
  FreeCamera* camera;
  static int bezier_samples;

  GraphMinMax graphMinMax = GraphMinMax();

  float t = 0;
  float x;
  float y;
  float z;

  vec3 a = vec3(0.0f, 0.0f, 0.0f);
  vec3 b = vec3(1.0f, 3.0f, 0.0f);
  vec3 c = vec3(2.0f, -2.0f, 0.0f);
  vec3 d = vec3(3.0f, 1.0f, 0.0f);
  vec3 aMonitor, bMonitor, cMonitor, dMonitor;

  unsigned int current_part = 1;
  void CreateBezierLine();
  void BuildTrianglesAndAddToVirtualScene(ObjModel *model);
  void Render();

  Scene4() {
    sceneModels["bunny_model"] = ObjModel("../data/bunny.obj");
    ComputeNormals(&sceneModels["bunny_model"]);
    AddModelToVirtualScene(&sceneModels["bunny_model"], virtualScene);

    sceneModels["plane"] = ObjModel("../data/plane.obj");
    ComputeNormals(&sceneModels["plane"]);
    AddModelToVirtualScene(&sceneModels["plane"], virtualScene);

    shaders["scene"] = Shader("../src/scenes/scene_4/shader_scene.vert",
                              "../src/scenes/scene_4/shader_scene.frag");

    camera = new FreeCamera(vec4(-1.5f,1.28f,4.0f,1.0f), -3.4f, 0.2f);
    CreateBezierLine();
  }
};

class Scene5
{
private:
  GLuint VBO_text, VAO_text;
public:
  map<string, SceneObject> virtualScene;
  map<string, Shader> shaders;
  FreeCamera* camera;

  float ambientStrength = 0.1f;
  float gouradSpecularStrength = 0.0f;
  float phongSpecularStrength = 1.0f;
  float diffuseStrength = 1.0f;
  vec3 lightPos = vec3(0.0f, 0.0f, 3.33f);

  unsigned int current_part = 1;
  void LoadShaderVariables();
  void BuildTrianglesAndAddToVirtualScene();
  void Render();

  Scene5() {
    shaders["color_shader"] = Shader("../src/scenes/scene_5/shader_color.vert",
                                     "../src/scenes/scene_5/shader_color.frag");
    shaders["light_shader"] = Shader("../src/scenes/scene_5/shader_light.vert",
                                     "../src/scenes/scene_5/shader_light.frag");
    shaders["text_shader"] =  Shader("../src/scenes/scene_5/shader_text.vert",
                                     "../src/scenes/scene_5/shader_text.frag");
    camera = new FreeCamera(vec4(-1.0f, 1.3f, 5.5f, 1.0f), 2.72f, 0.34f);
    BuildTrianglesAndAddToVirtualScene();
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

  unsigned int current_part = 1;
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

    camera = new FreeCamera(vec4(2.2f, 0.45f, -2.27f, 1.0f), -0.6f, 0.06f);
    BuildTrianglesAndAddToVirtualScene();
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

  bool spotLightOn = true;
  struct SpotLight {
    vec3 position;
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;

    float cutOff;
    float outerCutOff;
  };

  bool useTexture = false;
  bool useDiffuseTexture = true;
  bool useSpecularTexture = true;
  float gouradSpecularStrength = 0.0f;
  map<string, ObjModel> sceneModels;
  map<string, SceneObject> virtualScene;
  map<string, Shader> shaders;
  FreeCamera* camera;
  Material* material;
  DirectionalLight* directional_light;
  PointLight* point_light;
  SpotLight* spot_light;

  unsigned int current_part = 1;
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

    directional_light = new DirectionalLight { vec3(-3.2f, -3.0f, -5.0f),
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

    spot_light = new SpotLight { vec3(0.0f, 2.0f, 0.0f),
                                 vec3(0.0f,-1.0f, 0.0f),
                                 vec3(0.5f, 0.5f, 0.5f),
                                 vec3(0.5f, 0.5f, 0.5f),
                                 vec3(0.5f, 0.5f, 0.5f),
                                 1.0f,
                                 0.09f,
                                 0.032f,
                                 12.5f,
                                 15.0f};

    sceneModels["cylinder"] = ObjModel("../data/cylinder.obj");
    ComputeNormals(&sceneModels["cylinder"]);
    AddModelToVirtualScene(&sceneModels["cylinder"], virtualScene);

    shaders["color_shader"] = Shader("../src/scenes/scene_7/shader_color.vert",
                                     "../src/scenes/scene_7/shader_color.frag");
    shaders["light_shader"] = Shader("../src/scenes/scene_7/shader_light.vert",
                                     "../src/scenes/scene_7/shader_light.frag");
    shaders["plane_shader"] = Shader("../src/scenes/scene_7/shader_plane.vert",
                                     "../src/scenes/scene_7/shader_plane.frag");

    camera = new FreeCamera(vec4(-3.2f, 1.45f, -3.0f, 1.0f), 0.48f, 0.00f);
    BuildTrianglesAndAddToVirtualScene();
  }
};

class Scene8
{
private:
  GLuint VBO_frustum_lines;
  void DrawCommonModels();

public:
  map<string, ObjModel> sceneModels;
  map<string, SceneObject> virtualScene;
  map<string, Shader> shaders;
  HybridCamera* camera;
  FreeCamera* second_camera;
  bool simulate_perspective = false;

  unsigned int current_part = 1;
  void BuildTrianglesAndAddToVirtualScene();
  void Render();

  Scene8() {
    shaders["scene"] = Shader("../src/scenes/scene_8/shader_scene.vert",
                              "../src/scenes/scene_8/shader_scene.frag");

    camera = new HybridCamera(vec4(0.0f, 1.53f, -4.0f, 1.0f));
    camera->farPlane = -8.0f;
    second_camera = new FreeCamera(vec4(-3.7f, 2.5f, -7.4f, 1.0f), 0.42f);

    sceneModels["sphere"] = ObjModel("../data/sphere.obj");
    ComputeNormals(&sceneModels["sphere"]);
    AddModelToVirtualScene(&sceneModels["sphere"], virtualScene);

    sceneModels["plane"] = ObjModel("../data/plane.obj");
    ComputeNormals(&sceneModels["plane"]);
    AddModelToVirtualScene(&sceneModels["plane"], virtualScene);

    BuildTrianglesAndAddToVirtualScene();
  }
};

class Scene9
{
private:
  GLuint VBO_frustum_lines;
  void DrawCommonModels(bool perspective_transform = false);

public:
  map<string, ObjModel> sceneModels;
  map<string, SceneObject> virtualScene;
  map<string, Shader> shaders;
  HybridCamera* camera;
  HybridCamera* second_camera;
  bool simulate_perspective = false;
  bool follow_camera = false;
  bool freeze_camera_in_origin = false;
  float simulate_perspective_slider = 0.0f;

  unsigned int current_part = 1;
  void BuildTrianglesAndAddToVirtualScene();
  void Render();

  Scene9() {
    shaders["scene"] = Shader("../src/scenes/scene_9/shader_scene.vert",
                              "../src/scenes/scene_9/shader_scene.frag");

    // TODO: change this to free and make field of view settable?
    camera = new HybridCamera(vec4(0.0f, 0.0f, -3.7f, 1.0f));
    camera->farPlane = -8.0f;
    camera->nearPlane = -2.0f;
    second_camera = new HybridCamera(vec4(0.0f, 0.0f, -3.7f, 1.0f));
    second_camera->farPlane = -100.0f;
    second_camera->nearPlane = -2.0f;

    BuildTrianglesAndAddToVirtualScene();
  }
};

class Scene10
{
public:
  struct Arrow {
    vec4 position;
    vec4 lookAt;
    vec2 axisAlignedPosition;
    vec2 axisAlignedCenter;
    float lookAtHeightCylinder;
    float lookAtMaxHeightCylinder;
    float distance;
    float phi;
    float theta;

    Arrow() {
      position = vec4(0.0f,0.0f,0.0f,1.0f);
      lookAt = vec4(0.0f,1.0f,0.0f,1.0f);
      axisAlignedPosition = vec2(0.0f,0.0f);
      axisAlignedCenter = vec2(0.0f,0.0f);
      lookAtHeightCylinder = 0.5f;
      distance = 0.6f;
      phi = 2.0f;
      theta = 3.5f;
    }
  };

  bool useTexture = false;
  GLuint diffuseTextureId;

  map<string, GLuint> sceneTextures;
  map<string, ObjModel> sceneModels;
  map<string, SceneObject> virtualScene;
  map<string, Shader> shaders;
  HybridCamera* camera;
  FreeCamera* second_camera;
  Arrow* arrow;

  int texture_projection = 1;
  int chosen_model = 0;
  int chosen_texture = 0;
  bool use_world_coordinates = false;

  float cylinder_height = 1.0f;
  float texture_projection_transparency = 0.5f;

  vec3 model_position = vec3(0.0f, 0.0f, 0.0f);

  unsigned int current_part = 1;
  void DrawArrow();
  void BuildTrianglesAndAddToVirtualScene();
  void Render();

  Scene10() {
    sceneModels["cylinder"] = ObjModel("../data/cylinder.obj");
    ComputeNormals(&sceneModels["cylinder"]);
    AddModelToVirtualScene(&sceneModels["cylinder"], virtualScene);

    sceneModels["bunny"] = ObjModel("../data/bunny.obj");
    ComputeNormals(&sceneModels["bunny"]);
    AddModelToVirtualScene(&sceneModels["bunny"], virtualScene);

    sceneModels["teapot"] = ObjModel("../data/teapot.obj");
    ComputeNormals(&sceneModels["teapot"]);
    AddModelToVirtualScene(&sceneModels["teapot"], virtualScene);

    sceneModels["cube"] = ObjModel("../data/cube.obj");
    ComputeNormals(&sceneModels["cube"]);
    AddModelToVirtualScene(&sceneModels["cube"], virtualScene);

    sceneModels["sphere"] = ObjModel("../data/sphere.obj");
    ComputeNormals(&sceneModels["sphere"]);
    AddModelToVirtualScene(&sceneModels["sphere"], virtualScene);

    sceneModels["octahedron"] = ObjModel("../data/octahedron.obj");
    ComputeNormals(&sceneModels["octahedron"]);
    AddModelToVirtualScene(&sceneModels["octahedron"], virtualScene);

    sceneModels["dodecahedron"] = ObjModel("../data/dodecahedron.obj");
    ComputeNormals(&sceneModels["dodecahedron"]);
    AddModelToVirtualScene(&sceneModels["dodecahedron"], virtualScene);

    sceneModels["icosahedron"] = ObjModel("../data/icosahedron.obj");
    ComputeNormals(&sceneModels["icosahedron"]);
    AddModelToVirtualScene(&sceneModels["icosahedron"], virtualScene);

    sceneModels["arrow"] = ObjModel("../data/arrow.obj");
    ComputeNormals(&sceneModels["arrow"]);
    AddModelToVirtualScene(&sceneModels["arrow"], virtualScene);

    shaders["scene"] = Shader("../src/scenes/scene_10/shader_scene.vert",
                              "../src/scenes/scene_10/shader_scene.frag");

    shaders["arrow"] = Shader("../src/scenes/scene_10/shader_arrow.vert",
                              "../src/scenes/scene_10/shader_arrow.frag");

    shaders["texture"] = Shader("../src/scenes/scene_10/shader_texture.vert",
                                "../src/scenes/scene_10/shader_texture.frag");

    arrow = new Arrow();

    camera = new HybridCamera(vec4(-1.77f, 3.0f, 4.3f, 1.0f), -0.38f, 0.58f);
    camera->isFreeCamera = false;
    camera->lookAt = vec4(0.0f, 1.0f, 0.0f, 1.0f);
    second_camera = new FreeCamera(vec4(-1.68f, 2.58f, 4.0f, 1.0f), 2.7f, 0.31f);
    BuildTrianglesAndAddToVirtualScene();
  }
};