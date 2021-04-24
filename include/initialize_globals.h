#include "globals.h"

static double g_LimitFPS = 1.0 / 60.0;

// Razão de proporção da janela (largura/altura). Veja função FramebufferSizeCallback().
float g_ScreenRatio = 1.0f;

// Ângulos de Euler que controlam a rotação de um dos cubos da cena virtual
float g_AngleX = 0.0f;
float g_AngleY = 0.0f;
float g_AngleZ = 0.0f;

// Ângulos de Euler que controlam a rotação de um dos cubos da cena virtual
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
float g_CameraTheta = 0.0f;    // ângulo no plano ZX em relação ao eixo Z
float g_CameraPhi = 0.0f;      // ângulo em relação ao eixo Y
float g_CameraDistance = 2.5f; // Distância da câmera para a origem

// Variável que controla o tipo de projeção utilizada: perspectiva ou ortográfica.
bool g_UsePerspectiveProjection = true;

// Variável que controla o culling de faces
bool g_BackfaceCulling = true;
bool g_BackfaceCullingMonitor = true;

// Variável que controla o tamanho do near plane do frustum.
float g_FrustumNearPlane = -0.1f;

// Variável que controla o tamanho do far plane do frustum.
float g_FrustumFarPlane = -10.0f;

GLuint g_ProgramId;

Camera *g_MainCamera;

int g_CurrentScene = 3;
bool g_SceneChanged = false;

bool g_HoldTime = false;
int g_Frames = 0;
int g_Updates = 0;

double g_NowTime = 0;
double g_DeltaTime = 0;
double g_LastTime = 0;

// Variável que controla a cor do plano de clear.
ImVec4 g_ClearColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

std::map<std::string, SceneObject> Globals::g_VirtualScene;
double Globals::g_LastCursorPosX, Globals::g_LastCursorPosY;
ImGuiIO *Globals::g_Io;