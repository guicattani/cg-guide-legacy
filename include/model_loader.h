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
void ComputeNormals(ObjModel* model); // Computa normais de um ObjModel, caso não existam.
void DrawVirtualObject(const char* object_name); // Desenha um objeto armazenado em g_VirtualScene
void PrintObjModelInfo(ObjModel*); // Função para debugging

