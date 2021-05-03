#ifndef CLASS_HEADER_SCENE_LOADER
#define CLASS_HEADER_SCENE_LOADER
#include "scene_loader.h"
#endif


void CreateProgramForScene(int scene)
{
  // We delete the program because it unloads shaders completely
  if( g_ProgramId != 0 ) {
    glDeleteProgram(g_ProgramId); g_ProgramId = 0;
  }

  switch (scene)
  {
  case 2:
    g_sceneVertexShader = LoadShader_Vertex(Scene2::shader_vertex_filepath);
    g_sceneFragmentShader = LoadShader_Fragment(Scene2::shader_fragment_filepath);
    break;
  case 3:
    g_sceneVertexShader = LoadShader_Vertex(Scene3::shader_vertex_filepath);
    g_sceneFragmentShader = LoadShader_Fragment(Scene3::shader_fragment_filepath);
    break;
  case 4:
    g_sceneVertexShader = LoadShader_Vertex(Scene4::shader_vertex_filepath);
    g_sceneFragmentShader = LoadShader_Fragment(Scene4::shader_fragment_filepath);
    break;

  default:
    printf("No scene given to create, idling.\n");
  }
  // Criamos um programa de GPU utilizando os shaders carregados acima
  g_ProgramId = CreateGpuProgram(g_sceneVertexShader, g_sceneFragmentShader);
  if( g_sceneVertexShader != 0 ) {
    glDetachShader(g_ProgramId, g_sceneVertexShader);
    glDeleteShader(g_sceneVertexShader);
    g_sceneVertexShader = 0;
    }
  if( g_sceneFragmentShader != 0 ) {
    glDetachShader(g_ProgramId, g_sceneFragmentShader);
    glDeleteShader(g_sceneFragmentShader);
    g_sceneFragmentShader = 0;
  }

}