#ifndef CLASS_INITIALIZE_GLOBALS
#define CLASS_INITIALIZE_GLOBALS
#include "globals.h"

// Razão de proporção da janela (largura/altura). Veja função FramebufferSizeCallback().
float g_ScreenRatio = 1.0f;

// Ângulos de Euler que controlam a rotação de um dos cubos da cena virtual
float g_AngleX = 0.0f;
float g_AngleY = 0.0f;
float g_AngleZ = 0.0f;

// Ãngulos de Euler que controlam a rotação de um dos cubos da cena virtual
float g_MoveX = 0.0f;
float g_MoveY = 0.0f;
float g_MoveZ = 0.0f;

// Abaixo definimos as variáveis que efetivamente definem a câmera virtual.
// Veja slide 165 do documento "Aula_08_Sistemas_de_Coordenadas.pdf".
//glm::vec4 camera_position_c  ;
//glm::vec4 camera_lookat_l    ;
//glm::vec4 camera_view_vector ;
//glm::vec4 camera_up_vector   ;
//glm::vec4 camera_right_vector;

bool WPressed = false;
bool SPressed = false;
bool APressed = false;
bool DPressed = false;

// "g_LeftMouseButtonPressed = true" se o usuário está com o botão esquerdo do mouse
// pressionado no momento atual. Veja função MouseButtonCallback().
bool g_LeftMouseButtonPressed = false;

// Variáveis que definem a câmera em coordenadas esféricas, controladas pelo
// usuário através do mouse (veja função CursorPosCallback()). A posição
// efetiva da câmera é calculada dentro da função main(), dentro do loop de
// renderização.
float g_CameraTheta = 0.0f; // ângulo no plano ZX em relação ao eixo Z
float g_CameraPhi = 0.0f;   // ângulo em relação ao eixo Y
float g_CameraDistance = 2.5f; // Distância da câmera para a origem

// Variável que controla o tipo de projeção utilizada: perspectiva ou ortográfica.
bool g_UsePerspectiveProjection = true;

std::map<const char*, SceneObject> Globals::g_VirtualScene;
double Globals::g_LastCursorPosX, Globals::g_LastCursorPosY;
ImGuiIO* Globals::g_Io;
#endif