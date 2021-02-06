#ifndef CLASS_HEADER_SCENE_LOADER
#define CLASS_HEADER_SCENE_LOADER
#include "scene_loader.h"
#endif

void CreateProgramForScene(int scene)
{
  switch (scene)
  {
  case 2:
    // Criamos um programa de GPU utilizando os shaders carregados acima
    g_ProgramId = CreateGpuProgram(
        LoadShader_Vertex(Scene2::shader_vertex_filepath),
        LoadShader_Fragment(Scene2::shader_fragment_filepath));
    break;
  case 3:
    // Criamos um programa de GPU utilizando os shaders carregados acima
    g_ProgramId = CreateGpuProgram(
        LoadShader_Vertex(Scene3::shader_vertex_filepath),
        LoadShader_Fragment(Scene3::shader_fragment_filepath));
    break;
  case 4:
    // Criamos um programa de GPU utilizando os shaders carregados acima
    g_ProgramId = CreateGpuProgram(
        LoadShader_Vertex(Scene4::shader_vertex_filepath),
        LoadShader_Fragment(Scene4::shader_fragment_filepath));
    break;

  default:
    printf("No scene given to create, idling.\n");
  }
}