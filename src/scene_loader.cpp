#ifndef CLASS_HEADER_SCENE_LOADER
#define CLASS_HEADER_SCENE_LOADER
#include "scene_loader.h"
#endif

void CreateProgramForScene(int scene) {
  switch(scene) {
    case 3:
      // Criamos um programa de GPU utilizando os shaders carregados acima
      g_ProgramId = CreateGpuProgram(
          LoadShader_Vertex(Scene_3::shader_vertex_filepath),
          LoadShader_Fragment(Scene_3::shader_fragment_filepath)
        );
      break;
    case 4:
      // Criamos um programa de GPU utilizando os shaders carregados acima
      g_ProgramId = CreateGpuProgram(
          LoadShader_Vertex(Scene_4::shader_vertex_filepath),
          LoadShader_Fragment(Scene_4::shader_fragment_filepath)
        );
      break;

    default:
        printf("No scene given to create, idling.\n");
  }
}