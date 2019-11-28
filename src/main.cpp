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
#include "callbacks.h"
#include "shaders.h"
#include "interface.h"
#include "camera.h"
#include "opengl_loader.h"

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

  //Criamos todas instâncias de scenes
  Scene_3 scene;

	GLuint vertex_shader_id = LoadShader_Vertex("../src/shader_vertex.glsl");
	GLuint fragment_shader_id = LoadShader_Fragment("../src/shader_fragment.glsl");

	// Criamos um programa de GPU utilizando os shaders carregados acima
	GLuint program_id = CreateGpuProgram(vertex_shader_id, fragment_shader_id);
	// Construímos a representação de um triângulo
	GLuint vertex_array_object_id = scene.BuildTriangles();

	// Buscamos o endereço das variáveis definidas dentro do Vertex Shader.
	// Utilizaremos estas variáveis para enviar dados para a placa de vídeo
	// (GPU)! Veja arquivo "shader_vertex.glsl".
	GLint model_uniform = glGetUniformLocation(program_id, "model"); // Variável da matriz "model"
	GLint render_as_black_uniform = glGetUniformLocation(program_id, "render_as_black"); // Variável booleana em shader_vertex.glsl

	// Habilitamos o Z-buffer. Veja slide 108 do documento "Aula_09_Projecoes.pdf".
	glEnable(GL_DEPTH_TEST);

	// Variáveis auxiliares utilizadas para chamada de função
	// TextRendering_ShowModelViewProjection(), armazenando matrizes 4x4.
	glm::mat4 the_projection;
	glm::mat4 the_model;
	glm::mat4 the_view;

  //Inicializa a Interface (Imgui)
  Interface interface = Interface(true);
  interface.Init(window, glsl_version);

  Camera main_camera = Camera(program_id);

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
		glUseProgram(program_id);
		// "Ligamos" o VAO. Informamos que queremos utilizar os atributos de
		// vértices apontados pelo VAO criado pela função BuildTriangles(). Veja
		// comentários detalhados dentro da definição de BuildTriangles().
		glBindVertexArray(vertex_array_object_id);

    main_camera.Enable();

    //RENDER
		// Vamos desenhar 3 instâncias (cópias) do cubo
		for (int i = 1; i <= 3; ++i)
		{
			// Cada cópia do cuCamerao possui uma matriz de modelagem independente,
			// já que cada cópiCamera estará em uma posição (rotação, escala, ...)
			// diferente em relação ao espaço global (World Coordinates). Veja
			// slide 138 do documento "Aula_08_Sistemas_de_Coordenadas.pdf".
			glm::mat4 model;
			if (i == 1)
			{
				// A primeira cópia do cubo não sofrerá nenhuma transformação
				// de modelagem. Portanto, sua matriz "model" é a identidade, e
				// suas coordenadas no espaço global (World Coordinates) seráo
				// *exatamente iguais* a suas coordenadas no espaço do modelo
				// (Model Coordinates).
				model = Matrix_Identity();
			}
			else if (i == 2)
			{
				// A segunda cópia do cubo sofrerá um escalamento não-uniforme,
				// seguido de uma rotação no eixo (1,1,1), e uma translação em Z (nessa ordem!).
				model = Matrix_Translate(0.0f, 0.0f, -2.0f) // TERCEIRO translação
					* Matrix_Rotate(3.141592f / 8.0f, glm::vec4(1.0f, 1.0f, 1.0f, 0.0f)) // SEGUNDO rotação
					* Matrix_Scale(2.0f, 0.5f, 0.5f); // PRIMEIRO escala
			}
			else if (i == 3)
			{
				// A terceira cópia do cubo sofrerá rotações em X,Y e Z (nessa
				// ordem) seguindo o sistema de ângulos de Euler, e após uma
				// translação em X. Veja slide 62 do documento
				// "Aula_07_Transformacoes_Geometricas_3D.pdf".
				model = Matrix_Translate(-2.0f, 0.0f, 0.0f) // QUARTO translação
					* Matrix_Rotate_Z(g_AngleZ)  // TERCEIRO rotação Z de Euler
					* Matrix_Rotate_Y(g_AngleY)  // SEGUNDO rotação Y de Euler
					* Matrix_Rotate_X(g_AngleX); // PRIMEIRO rotação X de Euler
			  // Armazenamos as matrizes model, view, e projection do terceiro cubo
			  // para mostrar elas na tela através da função TextRendering_ShowModelViewProjection().
				the_model = model;
				the_projection = main_camera.projection;
				the_view = main_camera.view;
			}

			// Enviamos a matriz "model" para a placa de vídeo (GPU). Veja o
			// arquivo "shader_vertex.glsl", onde esta é efetivamente
			// aplicada em todos os pontos.
			glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(model));
			// Informamos para a placa de vídeo (GPU) que a variável booleana
			// "render_as_black" deve ser colocada como "false". Veja o arquivo
			// "shader_vertex.glsl".
			glUniform1i(render_as_black_uniform, false);
			// Pedimos para a GPU rasterizar os vértices do cubo apontados pelo
			// VAO como triângulos, formando as faces do cubo. Esta
			// renderização irá executar o Vertex Shader definido no arquivo
			// "shader_vertex.glsl", e o mesmo irá utilizar as matrizes
			// "model", "view" e "projection" definidas acima e já enviadas
			// para a placa de vídeo (GPU).
			//
			// Veja a definição de Globals::g_VirtualScene["cube_faces"] dentro da
			// função BuildTriangles(), e veja a documentação da função
			// glDrawElements() em http://docs.gl/gl3/glDrawElements.
			glDrawElements(
				Globals::g_VirtualScene["cube_faces"].rendering_mode, // Veja slide 178 do documento "Aula_04_Modelagem_Geometrica_3D.pdf".
				Globals::g_VirtualScene["cube_faces"].num_indices,    //
				GL_UNSIGNED_INT,
				(void*)Globals::g_VirtualScene["cube_faces"].first_index
			);

			// Pedimos para OpenGL desenhar linhas com largura de 4 pixels.
			glLineWidth(4.0f);
			// Pedimos para a GPU rasterizar os vértices dos eixos XYZ
			// apontados pelo VAO como linhas. Veja a definição de
			// Globals::g_VirtualScene["axes"] dentro da função BuildTriangles(), e veja
			// a documentação da função glDrawElements() em
			// http://docs.gl/gl3/glDrawElements.
			//
			// Importante: estes eixos seráo desenhamos com a matriz "model"
			// definida acima, e portanto sofreráo as mesmas transformações
			// geométricas que o cubo. Isto é, estes eixos estaráo
			// representando o sistema de coordenadas do modelo (e não o global)!
			glDrawElements(
				Globals::g_VirtualScene["axes"].rendering_mode,
				Globals::g_VirtualScene["axes"].num_indices,
				GL_UNSIGNED_INT,
				(void*)Globals::g_VirtualScene["axes"].first_index
			);

			// Informamos para a placa de vídeo (GPU) que a variável booleana
			// "render_as_black" deve ser colocada como "true". Veja o arquivo
			// "shader_vertex.glsl".
			glUniform1i(render_as_black_uniform, true);
			// Pedimos para a GPU rasterizar os vértices do cubo apontados pelo
			// VAO como linhas, formando as arestas pretas do cubo. Veja a
			// definição de Globals::g_VirtualScene["cube_edges"] dentro da função
			// BuildTriangles(), e veja a documentação da função
			// glDrawElements() em http://docs.gl/gl3/glDrawElements.
			glDrawElements(
				Globals::g_VirtualScene["cube_edges"].rendering_mode,
				Globals::g_VirtualScene["cube_edges"].num_indices,
				GL_UNSIGNED_INT,
				(void*)Globals::g_VirtualScene["cube_edges"].first_index
			);
			// Desenhamos um ponto de tamanho 15 pixels em cima do terceiro vértice
			// do terceiro cubo. Este vértice tem coordenada de modelo igual é
			// (0.5, 0.5, 0.5, 1.0).
			if (i == 3)
			{
				glPointSize(15.0f);
				glDrawArrays(GL_POINTS, 3, 1);
			}
		}

		// Agora queremos desenhar os eixos XYZ de coordenadas GLOBAIS.
		// Para tanto, colocamos a matriz de modelagem igual é identidade.
		// Veja slide 134 do documento "Aula_08_Sistemas_de_Coordenadas.pdf".
		glm::mat4 model = Matrix_Identity();
		// Enviamos a nova matriz "model" para a placa de vídeo (GPU). Veja o
		// arquivo "shader_vertex.glsl".
		glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(model));
		// Pedimos para OpenGL desenhar linhas com largura de 10 pixels.
		glLineWidth(10.0f);
		// Informamos para a placa de vídeo (GPU) que a variável booleana
		// "render_as_black" deve ser colocada como "false". Veja o arquivo
		// "shader_vertex.glsl".
		glUniform1i(render_as_black_uniform, false);

		// Pedimos para a GPU rasterizar os vértices dos eixos XYZ
		// apontados pelo VAO como linhas. Veja a definição de
		// Globals::g_VirtualScene["axes"] dentro da função BuildTriangles(), e veja
		// a documentação da função glDrawElements() em
		// http://docs.gl/gl3/glDrawElements.
		glDrawElements(
			Globals::g_VirtualScene["axes"].rendering_mode,
			Globals::g_VirtualScene["axes"].num_indices,
			GL_UNSIGNED_INT,
			(void*)Globals::g_VirtualScene["axes"].first_index
		);

		// "Desligamos" o VAO, evitando assim que operações posteriores venham a
		// alterar o mesmo. Isso evita bugs.
		glBindVertexArray(0);

		// Pegamos um vértice com coordenadas de modelo (0.5, 0.5, 0.5, 1) e o
		// passamos por todos os sistemas de coordenadas armazenados nas
		// matrizes the_model, the_view, e the_projection; e escrevemos na tela
		// as matrizes e pontos resultantes dessas transformações.
		glm::vec4 p_model(0.5f, 0.5f, 0.5f, 1.0f);

    interface.Show(window);
    glfwSwapBuffers(window);
	}

  interface.CleanUp();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
#pragma endregion DRAW_LOOP
