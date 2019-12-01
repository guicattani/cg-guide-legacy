#ifndef CLASS_ADD_HEADERS
#define CLASS_ADD_HEADERS
#include "headers.h"
#endif

// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

#pragma region [rgba(80, 80, 0, 0.2)] HEADERS
#ifndef CLASS_HEADER_MATRICES
#define CLASS_HEADER_MATRICES
#include "matrices.h"
#endif
#ifndef CLASS_HEADER_INITIALIZE_GLOBALS
#define CLASS_HEADER_INITIALIZE_GLOBALS
#include "initialize_globals.h"
#endif
#ifndef CLASS_HEADER_SCENE
#define CLASS_HEADER_SCENE
#include "scene.h"
#endif
#ifndef CLASS_HEADER_MODEL_LOADER
#define CLASS_HEADER_MODEL_LOADER
#include "model_loader.h"
#endif
#ifndef CLASS_HEADER_SHADERS
#define CLASS_HEADER_SHADERS
#include "shaders.h"
#endif
#ifndef CLASS_HEADER_CAMERA
#define CLASS_HEADER_CAMERA
#include "camera.h"
#endif
#include "callbacks.h"
#include "interface.h"
#include "opengl_loader.h"
#include "scene_loader.h"

GLuint BuildTriangles();

#pragma endregion HEADERS

#pragma region [rgba(20, 20, 100, 0.3)] MAIN
int main(int, char**)
{
	// Setup window
	if (!glfwInit())
	{
		fprintf(stderr, "ERROR: glfwInit() failed.\n");
		std::exit(1);
	}

	// GL 3.0 + GLSL 130
	const char* glsl_version = "#version 130";
	InitializeOpenGL3();

	// Create window with graphics context
	GLFWwindow* window = glfwCreateWindow(800, 800, "TCC - Guilherme", NULL, NULL);
	if (window == NULL)
		return 1;

	SetCallbacks(window);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync

	bool err = InitializeOpenGLLoader();
	if (err)
	{
		fprintf(stderr, "Failed to initialize OpenGL loader!\n");
		return 1;
	}
	PrintGPUInformation();

  int starting_scene = 4;

  //Criamos todas instâncias de scenes
  Scene_3 scene_3 = Scene_3();
  Scene_4 scene_4 = Scene_4();

  CreateProgramForScene(starting_scene);
  switch(starting_scene){
    case 3:
      scene_3.LoadShaderVariables(g_ProgramId);
      scene_3.BuildTrianglesAndAddToVirtualScene();
      break;
    case 4:
      scene_4.LoadShaderVariables(g_ProgramId);
      // Construímos a representação de objetos geométricos através de malhas de triângulos
      ObjModel spheremodel("../data/sphere.obj");
      ComputeNormals(&spheremodel);
      scene_4.BuildTrianglesAndAddToVirtualScene(&spheremodel);

      ObjModel bunnymodel("../data/bunny.obj");
      ComputeNormals(&bunnymodel);
      scene_4.BuildTrianglesAndAddToVirtualScene(&bunnymodel);

      ObjModel planemodel("../data/plane.obj");
      ComputeNormals(&planemodel);
      scene_4.BuildTrianglesAndAddToVirtualScene(&planemodel);
      break;
  }

	// Habilitamos o Z-buffer. Veja slide 108 do documento "Aula_09_Projecoes.pdf".
	glEnable(GL_DEPTH_TEST);

  // Habilitamos o Backface Culling. Veja slides 22-34 do documento "Aula_13_Clipping_and_Culling.pdf".
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glFrontFace(GL_CCW);

	// Variáveis auxiliares utilizadas para chamada de função
	// TextRendering_ShowModelViewProjection(), armazenando matrizes 4x4.
	glm::mat4 the_projection;
	// glm::mat4 the_model;
	glm::mat4 the_view;

  //Inicializa a Interface (Imgui)
  Interface interface = Interface(true);
  interface.Init(window, glsl_version);

  g_MainCamera = new Camera(g_ProgramId);
#pragma endregion MAIN

#pragma region [rgba(50, 100, 100, 0.2)] DRAW_LOOP
// Main loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(g_ClearColor.x, g_ClearColor.y, g_ClearColor.z, g_ClearColor.w);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Poll and handle events (inputs, window resize, etc.)
		// You can read the Globals::g_Io.WantCaptureMouse, Globals::g_Io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
		// - When Globals::g_Io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
		// - When Globals::g_Io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
		// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
		glfwPollEvents();
		// Pedimos para a GPU utilizar o programa de GPU criado acima (contendo
		// os shaders de vértice e fragmentos).
		glUseProgram(g_ProgramId);

    g_MainCamera->Enable();

    the_projection = g_MainCamera->projection;
    the_view = g_MainCamera->view;

    switch(starting_scene){
      case 3:
        scene_3.Render();
        break;
      case 4:
        scene_4.Render();
        break;
    }

    interface.Show(window);
    glfwSwapBuffers(window);
	}

  interface.CleanUp();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
#pragma endregion DRAW_LOOP
