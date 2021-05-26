#ifndef CLASS_HEADER_SCENE_LOADER
#define CLASS_HEADER_SCENE_LOADER
#include "scene_loader.h"
#endif

void CreateScene(int scene)
{
  switch (scene)
  {
  case 2:
    g_Scene2->camera = new Camera2D(g_Scene2->shader.ID);
    break;
  case 3:
    g_Scene3->camera = new FreeCamera(g_Scene3->shader.ID);
    g_Scene3->BuildTrianglesAndAddToVirtualScene();
    break;
  case 4:
    g_Scene4->camera = new FreeCamera(g_Scene4->shader.ID);
    g_Scene4->CreateBezierLine();

    ObjModel bunnymodel("../data/bunny.obj");
    ComputeNormals(&bunnymodel);
    g_Scene4->BuildTrianglesAndAddToVirtualScene(&bunnymodel);

    ObjModel planemodel("../data/plane.obj");
    ComputeNormals(&planemodel);
    g_Scene4->BuildTrianglesAndAddToVirtualScene(&planemodel);
    break;
  }
}