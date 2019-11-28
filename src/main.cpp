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
#ifndef CLASS_HEADER_DEMO
#define CLASS_HEADER_DEMO
#include "demo.h"
#endif
#include "callbacks.h"
#include "shaders.h"
#include "interface.h"
#include "camera.h"
#include "opengl_loader.h"

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

  //Criamos todas instâncias de demos
  // Demo_3 Demo;

	PrintGPUInformation();
	GLuint vertex_shader_id = LoadShader_Vertex("../src/shader_vertex.glsl");
	GLuint fragment_shader_id = LoadShader_Fragment("../src/shader_fragment.glsl");

	// Criamos um programa de GPU utilizando os shaders carregados acima
	GLuint program_id = CreateGpuProgram(vertex_shader_id, fragment_shader_id);
	// Construímos a representação de um triângulo
	GLuint vertex_array_object_id = BuildTriangles();

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

#pragma region [rgba(50, 100, 30, 0.2)] FUNCTIONS

/*
Constrói triângulos para renderização
*/
GLuint BuildTriangles()
{
  // Primeiro, definimos os atributos de cada vértice.

  // A posição de cada vértice é definida por coeficientes em um sistema de
  // coordenadas local de cada modelo geométrico. Note o uso de coordenadas
  // homogêneas.  Veja as seguintes referências:
  //
  //  - slide 27  do documento "Aula_08_Sistemas_de_Coordenadas.pdf";
  //  - slide 134 do documento "Aula_08_Sistemas_de_Coordenadas.pdf";
  //  - slide 152 do documento "Aula_09_Projecoes.pdf".
  //
  // Este vetor "model_coefficients" define a GEOMETRIA (veja 136 do
  // documento "Aula_04_Modelagem_Geometrica_3D.pdf").
  //
  GLfloat model_coefficients[] = {
    // Vértices de um cubo
    //    X      Y     Z     W
      -0.5f,  0.5f,  0.5f, 1.0f, // posição do vértice 0
      -0.5f, -0.5f,  0.5f, 1.0f, // posição do vértice 1
      0.5f, -0.5f,  0.5f, 1.0f, // posição do vértice 2
      0.5f,  0.5f,  0.5f, 1.0f, // posição do vértice 3
      -0.5f,  0.5f, -0.5f, 1.0f, // posição do vértice 4
      -0.5f, -0.5f, -0.5f, 1.0f, // posição do vértice 5
      0.5f, -0.5f, -0.5f, 1.0f, // posição do vértice 6
      0.5f,  0.5f, -0.5f, 1.0f, // posição do vértice 7
    // Vértices para desenhar o eixo X
    //    X      Y     Z     W
      0.0f,  0.0f,  0.0f, 1.0f, // posição do vértice 8
      1.0f,  0.0f,  0.0f, 1.0f, // posição do vértice 9
    // Vértices para desenhar o eixo Y
    //    X      Y     Z     W
      0.0f,  0.0f,  0.0f, 1.0f, // posição do vértice 10
      0.0f,  1.0f,  0.0f, 1.0f, // posição do vértice 11
    // Vértices para desenhar o eixo Z
    //    X      Y     Z     W
      0.0f,  0.0f,  0.0f, 1.0f, // posição do vértice 12
      0.0f,  0.0f,  1.0f, 1.0f, // posição do vértice 13
  };

  // Criamos o identificador (ID) de um Vertex Buffer Object (VBO).  Um VBO é
  // um buffer de memória que irá conter os valores de um certo atributo de
  // um conjunto de vértices; por exemplo: posição, cor, normais, coordenadas
  // de textura.  Neste exemplo utilizaremos vários VBOs, um para cada tipo de atributo.
  // Agora criamos um VBO para armazenarmos um atributo: posição.
  GLuint VBO_model_coefficients_id;
  glGenBuffers(1, &VBO_model_coefficients_id);

  // Criamos o identificador (ID) de um Vertex Array Object (VAO).  Um VAO
  // contém a definição de vários atributos de um certo conjunto de vértices;
  // isto é, um VAO irá conter ponteiros para vários VBOs.
  GLuint vertex_array_object_id;
  glGenVertexArrays(1, &vertex_array_object_id);

  // "Ligamos" o VAO ("bind"). Informamos que iremos atualizar o VAO cujo ID
  // está contido na variável "vertex_array_object_id".
  glBindVertexArray(vertex_array_object_id);

  // "Ligamos" o VBO ("bind"). Informamos que o VBO cujo ID está contido na
  // variável VBO_model_coefficients_id será modificado a seguir. A
  // constante "GL_ARRAY_BUFFER" informa que esse buffer é de fato um VBO, e
  // irá conter atributos de vértices.
  glBindBuffer(GL_ARRAY_BUFFER, VBO_model_coefficients_id);

  // Alocamos memória para o VBO "ligado" acima. Como queremos armazenar
  // nesse VBO todos os valores contidos no array "model_coefficients", pedimos
  // para alocar um número de bytes exatamente igual ao tamanho ("size")
  // desse array. A constante "GL_STATIC_DRAW" dá uma dica para o driver da
  // GPU sobre como utilizaremos os dados do VBO. Neste caso, estamos dizendo
  // que não pretendemos alterar tais dados (são estáticos: "STATIC"), e
  // também dizemos que tais dados seráo utilizados para renderizar ou
  // desenhar ("DRAW").  Pense que:
  //
  //            glBufferData()  ==  malloc() do C  ==  new do C++.
  //
  glBufferData(GL_ARRAY_BUFFER, sizeof(model_coefficients), NULL, GL_STATIC_DRAW);

  // Finalmente, copiamos os valores do array model_coefficients para dentro do
  // VBO "ligado" acima.  Pense que:
  //
  //            glBufferSubData()  ==  memcpy() do C.
  //
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(model_coefficients), model_coefficients);

  // Precisamos então informar um índice de "local" ("location"), o qual será
  // utilizado no shader "shader_vertex.glsl" para acessar os valores
  // armazenados no VBO "ligado" acima. Também, informamos a dimensão (número de
  // coeficientes) destes atributos. Como em nosso caso são pontos em coordenadas
  // homogêneas, temos quatro coeficientes por vértice (X,Y,Z,W). Isso define
  // um tipo de dado chamado de "vec4" em "shader_vertex.glsl": um vetor com
  // quatro coeficientes. Finalmente, informamos que os dados estáo em ponto
  // flutuante com 32 bits (GL_FLOAT).
  // Esta função também informa que o VBO "ligado" acima em glBindBuffer()
  // está dentro do VAO "ligado" acima por glBindVertexArray().
  // Veja https://www.khronos.org/opengl/wiki/Vertex_Specification#Vertex_Buffer_Object
  GLuint location = 0; // "(location = 0)" em "shader_vertex.glsl"
  GLint  number_of_dimensions = 4; // vec4 em "shader_vertex.glsl"
  glVertexAttribPointer(location, number_of_dimensions, GL_FLOAT, GL_FALSE, 0, 0);

  // "Ativamos" os atributos. Informamos que os atributos com índice de local
  // definido acima, na variável "location", deve ser utilizado durante o
  // rendering.
  glEnableVertexAttribArray(location);

  // "Desligamos" o VBO, evitando assim que operações posteriores venham a
  // alterar o mesmo. Isso evita bugs.
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // Agora repetimos todos os passos acima para atribuir um novo atributo a
  // cada vértice: uma cor (veja slide 137 do documento "Aula_04_Modelagem_Geometrica_3D.pdf").
  // Tal cor é definida como coeficientes RGBA: Red, Green, Blue, Alpha;
  // isto é: Vermelho, Verde, Azul, Alpha (valor de transparência).
  // Conversaremos sobre sistemas de cores nas aulas de Modelos de Iluminação.
  GLfloat color_coefficients[] = {
    // Cores dos vértices do cubo
    //  R     G     B     A
      1.0f, 0.5f, 0.0f, 1.0f, // cor do vértice 0
      1.0f, 0.5f, 0.0f, 1.0f, // cor do vértice 1
      0.0f, 0.5f, 1.0f, 1.0f, // cor do vértice 2
      0.0f, 0.5f, 1.0f, 1.0f, // cor do vértice 3
      1.0f, 0.5f, 0.0f, 1.0f, // cor do vértice 4
      1.0f, 0.5f, 0.0f, 1.0f, // cor do vértice 5
      0.0f, 0.5f, 1.0f, 1.0f, // cor do vértice 6
      0.0f, 0.5f, 1.0f, 1.0f, // cor do vértice 7
    // Cores para desenhar o eixo X
      1.0f, 0.0f, 0.0f, 1.0f, // cor do vértice 8
      1.0f, 0.0f, 0.0f, 1.0f, // cor do vértice 9
    // Cores para desenhar o eixo Y
      0.0f, 1.0f, 0.0f, 1.0f, // cor do vértice 10
      0.0f, 1.0f, 0.0f, 1.0f, // cor do vértice 11
    // Cores para desenhar o eixo Z
      0.0f, 0.0f, 1.0f, 1.0f, // cor do vértice 12
      0.0f, 0.0f, 1.0f, 1.0f, // cor do vértice 13
  };
  GLuint VBO_color_coefficients_id;
  glGenBuffers(1, &VBO_color_coefficients_id);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_color_coefficients_id);
  glBufferData(GL_ARRAY_BUFFER, sizeof(color_coefficients), NULL, GL_STATIC_DRAW);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(color_coefficients), color_coefficients);
  location = 1; // "(location = 1)" em "shader_vertex.glsl"
  number_of_dimensions = 4; // vec4 em "shader_vertex.glsl"
  glVertexAttribPointer(location, number_of_dimensions, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(location);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // Vamos então definir polígonos utilizando os vértices do array
  // model_coefficients.
  //
  // Para referência sobre os modos de renderização, veja slide 178 do
  // documento "Aula_04_Modelagem_Geometrica_3D.pdf".
  //
  // Este vetor "indices" define a TOPOLOGIA (veja slide 136 do documento
  // "Aula_04_Modelagem_Geometrica_3D.pdf").
  //
  GLuint indices[] = {
    // Definimos os índices dos vértices que definem as FACES de um cubo
    // através de 12 triângulos que seráo desenhados com o modo de renderização
    // GL_TRIANGLES.
      0, 1, 2, // triângulo 1
      7, 6, 5, // triângulo 2
      3, 2, 6, // triângulo 3
      4, 0, 3, // triângulo 4
      4, 5, 1, // triângulo 5
      1, 5, 6, // triângulo 6
      0, 2, 3, // triângulo 7
      7, 5, 4, // triângulo 8
      3, 6, 7, // triângulo 9
      4, 3, 7, // triângulo 10
      4, 1, 0, // triângulo 11
      1, 6, 2, // triângulo 12
    // Definimos os índices dos vértices que definem as ARESTAS de um cubo
    // através de 12 linhas que seráo desenhadas com o modo de renderização
    // GL_LINES.
      0, 1, // linha 1
      1, 2, // linha 2
      2, 3, // linha 3
      3, 0, // linha 4
      0, 4, // linha 5
      4, 7, // linha 6
      7, 6, // linha 7
      6, 2, // linha 8
      6, 5, // linha 9
      5, 4, // linha 10
      5, 1, // linha 11
      7, 3, // linha 12
    // Definimos os índices dos vértices que definem as linhas dos eixos X, Y,
    // Z, que seráo desenhados com o modo GL_LINES.
      8 , 9 , // linha 1
      10, 11, // linha 2
      12, 13  // linha 3
  };

  // Criamos um primeiro objeto virtual (SceneObject) que se refere às faces
  // coloridas do cubo.
  SceneObject cube_faces;
  cube_faces.name = "Cubo (faces coloridas)";
  cube_faces.first_index = (void*)0; // Primeiro índice está em indices[0]
  cube_faces.num_indices = 36;       // último índice está em indices[35]; total de 36 índices.
  cube_faces.rendering_mode = GL_TRIANGLES; // índices correspondem ao tipo de rasterização GL_TRIANGLES.

  // Adicionamos o objeto criado acima na nossa cena virtual (Globals::g_VirtualScene).
  Globals::g_VirtualScene["cube_faces"] = cube_faces;

  // Criamos um segundo objeto virtual (SceneObject) que se refere às arestas
  // pretas do cubo.
  SceneObject cube_edges;
  cube_edges.name = "Cubo (arestas pretas)";
  cube_edges.first_index = (void*)(36 * sizeof(GLuint)); // Primeiro índice está em indices[36]
  cube_edges.num_indices = 24; // último índice está em indices[59]; total de 24 índices.
  cube_edges.rendering_mode = GL_LINES; // índices correspondem ao tipo de rasterização GL_LINES.

  // Adicionamos o objeto criado acima na nossa cena virtual (Globals::g_VirtualScene).
  Globals::g_VirtualScene["cube_edges"] = cube_edges;

  // Criamos um terceiro objeto virtual (SceneObject) que se refere aos eixos XYZ.
  SceneObject axes;
  axes.name = "Eixos XYZ";
  axes.first_index = (void*)(60 * sizeof(GLuint)); // Primeiro índice está em indices[60]
  axes.num_indices = 6; // último índice está em indices[65]; total de 6 índices.
  axes.rendering_mode = GL_LINES; // índices correspondem ao tipo de rasterização GL_LINES.
  Globals::g_VirtualScene["axes"] = axes;

  // Criamos um buffer OpenGL para armazenar os índices acima
  GLuint indices_id;
  glGenBuffers(1, &indices_id);

  // "Ligamos" o buffer. Note que o tipo agora é GL_ELEMENT_ARRAY_BUFFER.
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_id);

  // Alocamos memória para o buffer.
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), NULL, GL_STATIC_DRAW);

  // Copiamos os valores do array indices[] para dentro do buffer.
  glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(indices), indices);

  // NÃO faça a chamada abaixo! Diferente de um VBO (GL_ARRAY_BUFFER), um
  // array de índices (GL_ELEMENT_ARRAY_BUFFER) não pode ser "desligado",
  // caso contrário o VAO irá perder a informação sobre os índices.
  //
  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // XXX Errado!
  //

  // "Desligamos" o VAO, evitando assim que operações posteriores venham a
  // alterar o mesmo. Isso evita bugs.
  glBindVertexArray(0);

  // Retornamos o ID do VAO. Isso é tudo que será necessário para renderizar
  // os triângulos definidos acima. Veja a chamada glDrawElements() em main().
  return vertex_array_object_id;
}
#pragma endregion FUNCTIONS
