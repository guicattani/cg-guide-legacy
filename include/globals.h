#ifndef CLASS_ADD_HEADERS
#define CLASS_ADD_HEADERS
#include "headers.h"
#endif

#ifndef CLASS_HEADER_SHADER
#define CLASS_HEADER_SHADER
#include "shader.h"
#endif

// Razão de proporção da janela (largura/altura). Veja função FramebufferSizeCallback().
extern float g_ScreenRatio;

// Ângulos de Euler que controlam a rotação de um dos cubos da cena virtual
extern float g_AngleX;
extern float g_AngleY;
extern float g_AngleZ;

// Ângulos de Euler que controlam a rotação de um dos cubos da cena virtual
extern float g_MoveX;
extern float g_MoveY;
extern float g_MoveZ;

extern bool ShiftPressed;
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
extern float g_CameraTheta;    // ângulo no plano ZX em relação ao eixo Z
extern float g_CameraPhi;      // ângulo em relação ao eixo Y
extern float g_CameraDistance; // Distância da câmera para a origem

// Variável que controla o tipo de projeção utilizada: perspectiva ou ortográfica.
extern bool g_UsePerspectiveProjection;

// Variável que controla o culling de faces
extern bool g_BackfaceCulling;
extern bool g_BackfaceCullingMonitor;

// Variável que controla a posição do near plane do frustum.
extern float g_FrustumNearPlane;

// Variável que controla a posição do far plane do frustum.
extern float g_FrustumFarPlane;

// Variável que controla a cor do plano de clear.
extern ImVec4 g_ClearColor;

extern GLuint g_ProgramId;
extern GLuint g_sceneVertexShader;
extern GLuint g_sceneFragmentShader;

extern int g_CurrentScene;
extern bool g_SceneChanged; // TODO Decide if this is going to be used

extern unsigned int g_NumLoadedTextures;

extern bool g_HoldTime;
extern int g_Frames;
extern int g_Updates;

extern double g_NowTime, g_DeltaTime, g_LastTime;

extern map<string, Image> g_Images;
extern map<char, Character> Characters;

extern FT_Library g_FreeType;
extern FT_Face g_FtFace;

extern GLFWwindow *g_Window;

class Globals
{
public:
  // Variáveis globais que armazenam a última posição do cursor do mouse, para
  // que possamos calcular quanto que o mouse se movimentou entre dois instantes
  // de tempo. Utilizadas no callback CursorPosCallback() abaixo.
  static double g_LastCursorPosX, g_LastCursorPosY;
  static double g_CurrentCursorPosX, g_CurrentCursorPosY;

  // Variável que controla o ImGui.
  static ImGuiIO *g_Io;
};