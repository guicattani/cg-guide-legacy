#ifndef CLASS_HEADER_SCENE_LOADER
#define CLASS_HEADER_SCENE_LOADER
#include "scene_loader.h"
#endif

using namespace glm;

void CreateScene(int scene)
{
  switch (scene)
  {
  case 2:
    g_Scene2->camera = new Camera2D();
    break;
  case 3:
    g_Scene3->camera = new FreeCamera();
    g_Scene3->BuildTrianglesAndAddToVirtualScene();
    break;
  case 4:
    g_Scene4->camera = new FreeCamera();
    g_Scene4->CreateBezierLine();

    g_Scene4->sceneModels["bunny_model"] = ObjModel("../data/bunny.obj");
    ComputeNormals(&g_Scene4->sceneModels["bunny_model"]);
    g_Scene4->BuildTrianglesAndAddToVirtualScene(&g_Scene4->sceneModels["bunny_model"]);

    g_Scene4->sceneModels["plane"] = ObjModel("../data/plane.obj");
    ComputeNormals(&g_Scene4->sceneModels["plane"]);
    g_Scene4->BuildTrianglesAndAddToVirtualScene(&g_Scene4->sceneModels["plane"]);
    break;
  case 5:
    g_Scene5->camera = new FreeCamera(vec4(-1.5f, 0.5f, -0.3f, 1.0f), 0.56f, 0.07f);
    g_Scene5->BuildTrianglesAndAddToVirtualScene();
    break;
  case 6:
    g_Scene6->camera = new FreeCamera();
    g_Scene6->BuildTrianglesAndAddToVirtualScene();
    break;
  }
}