#ifndef CLASS_HEADER_SCENE_LOADER
#define CLASS_HEADER_SCENE_LOADER
#include "scene_loader.h"
#endif

using namespace glm;

// TODO: Use constructor for this
void CreateScene(int scene)
{
  switch (scene)
  {
  case 1:
    g_Scene1->camera = new Camera2D();
    break;
  case 2:
    g_Scene2->camera = new Camera2D();
    break;
  case 3:
    g_Scene3->camera = new FreeCamera(vec4(-3.0f,1.5f,3.0f,1.0f), 2.4f, 0.4f);
    g_Scene3->BuildTrianglesAndAddToVirtualScene();
    break;
  case 4:
    g_Scene4->camera = new FreeCamera(vec4(-1.5f,1.28f,4.0f,1.0f), -3.4f, 0.2f);
    g_Scene4->CreateBezierLine();

    g_Scene4->sceneModels["bunny_model"] = ObjModel("../data/bunny.obj");
    ComputeNormals(&g_Scene4->sceneModels["bunny_model"]);
    g_Scene4->BuildTrianglesAndAddToVirtualScene(&g_Scene4->sceneModels["bunny_model"]);

    g_Scene4->sceneModels["plane"] = ObjModel("../data/plane.obj");
    ComputeNormals(&g_Scene4->sceneModels["plane"]);
    g_Scene4->BuildTrianglesAndAddToVirtualScene(&g_Scene4->sceneModels["plane"]);
    break;
  case 5:
    g_Scene5->camera = new FreeCamera(vec4(-1.0f, 1.3f, 5.5f, 1.0f), 2.72f, 0.34f);
    g_Scene5->BuildTrianglesAndAddToVirtualScene();
    break;
  case 6:
    g_Scene6->camera = new FreeCamera(vec4(2.2f, 0.45f, -2.27f, 1.0f), -0.6f, 0.06f);
    g_Scene6->BuildTrianglesAndAddToVirtualScene();
    break;
  case 7:
    g_Scene7->camera = new FreeCamera(vec4(-3.2f, 1.45f, -3.0f, 1.0f), 0.48f, 0.00f);
    g_Scene7->BuildTrianglesAndAddToVirtualScene();
    break;
  }
}