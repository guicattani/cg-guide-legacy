#ifndef CLASS_ADD_HEADERS
#define CLASS_ADD_HEADERS
#include "headers.h"
#endif

#ifndef CLASS_HEADER_INITIALIZE_GLOBALS
#define CLASS_HEADER_INITIALIZE_GLOBALS
#include "globals.h"
#endif

#ifndef CLASS_HEADER_MATRICES
#define CLASS_HEADER_MATRICES
#include "matrices.h"
#endif

// Declaração de várias funções utilizadas em main().  Essas estão definidas
// logo após a definição de main() neste arquivo.
void ComputeNormals(ObjModel *model);            // Computa normais de um ObjModel, caso não existam.
void DrawVirtualObject(SceneObject sceneObject); // Desenha um objeto armazenado em virtualScene
void PrintObjModelInfo(ObjModel *);              // Função para debugging
GLuint LoadTextureImage(const char* filename);   // Função que carrega uma imagem para ser utilizada como textura
