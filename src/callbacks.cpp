#ifndef CLASS_HEADER_SCENE_GLOBALS
#define CLASS_HEADER_SCENE_GLOBALS
#include "globals_scenes.h"
#endif

#include "callbacks.h"

// definição da função que será chamada sempre que a janela do sistema
// operacional for redimensionada, por consequência alterando o tamanho do
// "framebuffer" (região de memória onde são armazenados os pixels da imagem).
void FramebufferSizeCallback(GLFWwindow *window, int width, int height)
{
  // Indicamos que queremos renderizar em toda região do framebuffer. A
  // função "glViewport" define o mapeamento das "normalized device
  // coordinates" (NDC) para "pixel coordinates".  Essa é a operação de
  // "Screen Mapping" ou "Viewport Mapping" vista em aula (slides 32 até 40
  // do documento "Aula_07_Transformacoes_Geometricas_3D.pdf").
  glViewport(0, 0, width, height);

  // Atualizamos também a razão que define a proporção da janela (largura /
  // altura), a qual será utilizada na definição das matrizes de projeção,
  // tal que não ocorra distorções durante o processo de "Screen Mapping"
  // acima, quando NDC é mapeado para coordenadas de pixels. Veja slide 234
  // do documento "Aula_09_Projecoes.pdf".
  //
  // O cast para float é necessário pois números inteiros são arredondados ao
  // serem divididos!
  g_ScreenRatio = (float)width / height;
}

// função callback chamada sempre que o usuário aperta algum dos botões do mouse
void MouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
  if (Globals::g_Io->WantCaptureMouse)
    return;

  if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
  {
    // Se o usuário pressionou o botão esquerdo do mouse, guardamos a
    // posição atual do cursor nas variáveis Globals::g_LastCursorPosX e
    // g_LastCursorPosY.  Também, setamos a variável
    // g_LeftMouseButtonPressed como true, para saber que o usuário está
    // com o botão esquerdo pressionado.
    glfwGetCursorPos(window, &Globals::g_LastCursorPosX, &Globals::g_LastCursorPosY);
    g_LeftMouseButtonPressed = true;
  }
  if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
  {
    // Quando o usuário soltar o botão esquerdo do mouse, atualizamos a
    // variável abaixo para false.
    g_LeftMouseButtonPressed = false;
  }
}

// função callback chamada sempre que o usuário movimentar o cursor do mouse em
// cima da janela OpenGL.
void CursorPosCallback(GLFWwindow *window, double xpos, double ypos)
{
  // Abaixo executamos o seguinte: caso o botão esquerdo do mouse esteja
  // pressionado, computamos quanto que o mouse se movimento desde o último
  // instante de tempo, e usamos esta movimentação para atualizar os
  // parâmetros que definem a posição da câmera dentro da cena virtual.
  // Assim, temos que o usuário consegue controlar a câmera.

  if (!g_LeftMouseButtonPressed)
    return;

  // Deslocamento do cursor do mouse em x e y de coordenadas de tela!
  float dx = float(xpos - Globals::g_LastCursorPosX);
  float dy = float(ypos - Globals::g_LastCursorPosY);

  float phimax = 3.141592f / 2;
  float phimin = -phimax;

  //TODO fix this, this is very ugly
  switch (g_CurrentScene)
  {
  case 3:
    g_Scene3->camera->theta -= 0.01f * dx;
    g_Scene3->camera->phi += 0.01f * dy;

    if (g_Scene3->camera->phi > phimax) {
      g_Scene3->camera->phi = phimax;
    } else if (g_Scene3->camera->phi < phimin) {
      g_Scene3->camera->phi = phimin;
    }
    break;
  case 4:
    g_Scene4->camera->theta -= 0.01f * dx;
    g_Scene4->camera->phi += 0.01f * dy;

    if (g_Scene4->camera->phi > phimax) {
      g_Scene4->camera->phi = phimax;
    } else if (g_Scene4->camera->phi < phimin) {
      g_Scene4->camera->phi = phimin;
    }
    break;
  case 5:
    g_Scene5->camera->theta -= 0.01f * dx;
    g_Scene5->camera->phi += 0.01f * dy;

    if (g_Scene5->camera->phi > phimax) {
      g_Scene5->camera->phi = phimax;
    } else if (g_Scene5->camera->phi < phimin) {
      g_Scene5->camera->phi = phimin;
    }
    break;
  case 6:
    g_Scene6->camera->theta -= 0.01f * dx;
    g_Scene6->camera->phi += 0.01f * dy;

    if (g_Scene6->camera->phi > phimax) {
      g_Scene6->camera->phi = phimax;
    } else if (g_Scene6->camera->phi < phimin) {
      g_Scene6->camera->phi = phimin;
    }
    break;
  case 7:
    g_Scene7->camera->theta -= 0.01f * dx;
    g_Scene7->camera->phi += 0.01f * dy;

    if (g_Scene7->camera->phi > phimax) {
      g_Scene7->camera->phi = phimax;
    } else if (g_Scene7->camera->phi < phimin) {
      g_Scene7->camera->phi = phimin;
    }
    break;
  }
  // Atualizamos as variáveis globais para armazenar a posição atual do
  // cursor como sendo a última posição conhecida do cursor.
  Globals::g_LastCursorPosX = xpos;
  Globals::g_LastCursorPosY = ypos;
}

// função callback chamada sempre que o usuário movimenta a "rodinha" do mouse.
void ScrollCallback(GLFWwindow *window, double xoffset, double yoffset)
{
  // Atualizamos a distância da câmera para a origem utilizando a
  // movimentação da "rodinha", simulando um ZOOM.
  g_CameraDistance -= 0.1f * float(yoffset);

  if (g_CameraDistance < 0.0f)
    g_CameraDistance = 0.0f;
}

// definição da função que será chamada sempre que o usuário pressionar alguma
// tecla do teclado. Veja http://www.glfw.org/docs/latest/input_guide.html#input_key
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mod)
{
  // Se o usuário pressionar a tecla ESC, fechamos a janela.
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);

  // O código abaixo implementa a seguinte lógica:
  //   Se apertar tecla X       então g_AngleX += delta;
  //   Se apertar tecla shift+X então g_AngleX -= delta;
  //   Se apertar tecla Y       então g_AngleY += delta;
  //   Se apertar tecla shift+Y então g_AngleY -= delta;
  //   Se apertar tecla Z       então g_AngleZ += delta;
  //   Se apertar tecla shift+Z então g_AngleZ -= delta;

  float delta = float(3.141592 / 16); // 22.5 graus, em radianos.

  if (key == GLFW_KEY_X && action == GLFW_PRESS)
  {
    g_AngleX += (mod & GLFW_MOD_SHIFT) ? -delta : delta;
  }

  if (key == GLFW_KEY_Y && action == GLFW_PRESS)
  {
    g_AngleY += (mod & GLFW_MOD_SHIFT) ? -delta : delta;
  }
  if (key == GLFW_KEY_Z && action == GLFW_PRESS)
  {
    g_AngleZ += (mod & GLFW_MOD_SHIFT) ? -delta : delta;
  }

  //Movimentação free camera
  if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS)
  {
    ShiftPressed = true;
  }
  if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_RELEASE)
  {
    ShiftPressed = false;
  }

  if (key == GLFW_KEY_W && action == GLFW_PRESS)
  {
    WPressed = true;
  }
  if (key == GLFW_KEY_W && action == GLFW_RELEASE)
  {
    WPressed = false;
  }

  if (key == GLFW_KEY_S && action == GLFW_PRESS)
  {
    SPressed = true;
  }
  if (key == GLFW_KEY_S && action == GLFW_RELEASE)
  {
    SPressed = false;
  }

  if (key == GLFW_KEY_A && action == GLFW_PRESS)
  {
    APressed = true;
  }
  if (key == GLFW_KEY_A && action == GLFW_RELEASE)
  {
    APressed = false;
  }

  if (key == GLFW_KEY_D && action == GLFW_PRESS)
  {
    DPressed = true;
  }
  if (key == GLFW_KEY_D && action == GLFW_RELEASE)
  {
    DPressed = false;
  }

  // Se o usuário apertar a tecla espaço, resetamos os ângulos de Euler para zero.
  if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
  {
    g_AngleX = 0.0f;
    g_AngleY = 0.0f;
    g_AngleZ = 0.0f;
  }

  // Se o usuário apertar a tecla P, utilizamos projeção perspectiva.
  if (key == GLFW_KEY_P && action == GLFW_PRESS)
  {
    g_UsePerspectiveProjection = true;
  }

  // Se o usuário apertar a tecla O, utilizamos projeção ortográfica.
  if (key == GLFW_KEY_O && action == GLFW_PRESS)
  {
    g_UsePerspectiveProjection = false;
  }
}

// Definimos o callback para impressão de erros da GLFW no terminal
void ErrorCallback(int error, const char *description)
{
  fprintf(stderr, "ERROR: GLFW: %s\n", description);
}

/*
Cria callbacks pra todos eventos: (KeyPress, MouseButtonPress, CursorPosition, Scroll, Framebuffer, Error)
*/
void SetCallbacks(GLFWwindow *window)
{
  // Definimos a função de callback que será chamada sempre que o usuário
  // pressionar alguma tecla do teclado ...
  glfwSetKeyCallback(window, KeyCallback);
  // ... ou clicar os botões do mouse ...
  glfwSetMouseButtonCallback(window, MouseButtonCallback);
  // ... ou movimentar o cursor do mouse em cima da janela ...
  glfwSetCursorPosCallback(window, CursorPosCallback);
  // ... ou rolar a "rodinha" do mouse.
  glfwSetScrollCallback(window, ScrollCallback);
  // Definimos a função de callback que será chamada sempre que a janela for
  // redimensionada, por consequência alterando o tamanho do "framebuffer"
  // (região de memória onde são armazenados os pixels da imagem).
  glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
  // Definimos o callback para impressão de erros da GLFW no terminal
  glfwSetErrorCallback(ErrorCallback);
}
