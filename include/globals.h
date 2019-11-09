#ifndef CLASS_GLOBALS
#define CLASS_GLOBALS
#include "headers.h"

// Razão de proporção da janela (largura/altura). Veja função FramebufferSizeCallback().
extern float g_ScreenRatio;

// Ângulos de Euler que controlam a rotação de um dos cubos da cena virtual
extern float g_AngleX;
extern float g_AngleY;
extern float g_AngleZ;

// Ãngulos de Euler que controlam a rotação de um dos cubos da cena virtual
extern float g_MoveX;
extern float g_MoveY;
extern float g_MoveZ;

// Abaixo definimos as variáveis que efetivamente definem a câmera virtual.
// Veja slide 165 do documento "Aula_08_Sistemas_de_Coordenadas.pdf".
//glm::vec4 camera_position_c  ;
//glm::vec4 camera_lookat_l    ;
//glm::vec4 camera_view_vector ;
//glm::vec4 camera_up_vector   ;
//glm::vec4 camera_right_vector;

extern bool WPressed;
extern bool SPressed;
extern bool APressed;
extern bool DPressed;

// "g_LeftMouseButtonPressed = true" se o usuário está com o botão esquerdo do mouse
// pressionado no momento atual. Veja função MouseButtonCallback().
extern bool g_LeftMouseButtonPressed;

// Variáveis que definem a câmera em coordenadas esféricas, controladas pelo
// usuário através do mouse (veja função CursorPosCallback()). A posição
// efetiva da câmera é calculada dentro da função main(), dentro do loop de
// renderização.
extern float g_CameraTheta; // ângulo no plano ZX em relação ao eixo Z
extern float g_CameraPhi;   // ângulo em relação ao eixo Y
extern float g_CameraDistance; // Distância da câmera para a origem

// Variável que controla o tipo de projeção utilizada: perspectiva ou ortográfica.
extern bool g_UsePerspectiveProjection;
#endif

#ifndef CLASS_STATIC_GLOBALS
#define CLASS_STATIC_GLOBALS
class Globals {
public:
  // Variável da cena atual.
  static std::map<const char*, SceneObject> g_VirtualScene;

  // Variáveis globais que armazenam a última posição do cursor do mouse, para
  // que possamos calcular quanto que o mouse se movimentou entre dois instantes
  // de tempo. Utilizadas no callback CursorPosCallback() abaixo.
  static double g_LastCursorPosX, g_LastCursorPosY;

  // Variável que controla o ImGui.
  static ImGuiIO* g_Io;
};
#endif