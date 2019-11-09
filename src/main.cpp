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

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

#pragma region [rgba(80, 80, 0, 0.2)] HEADERS APPLICATION
#include "matrices.h"
#include "shaders.h"
#ifndef CLASS_HEADER_INITIALIZE_GLOBALS
#define CLASS_HEADER_INITIALIZE_GLOBALS
#include "initialize_globals.h"
#endif
#include "callbacks.h"

GLuint BuildTriangles();

void SetCallbacks();

void InitializeOpenGL3();

void PrintGPUInformation();

bool InitializeOpenGLLoader();

#pragma endregion HEADERS APPLICATION

#pragma region [rgba(20, 20, 100, 0.2)] MAIN
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
    GLuint vertex_shader_id = LoadShader_Vertex("src/shader_vertex.glsl");
    GLuint fragment_shader_id = LoadShader_Fragment("src/shader_fragment.glsl");

    // Criamos um programa de GPU utilizando os shaders carregados acima
    GLuint program_id = CreateGpuProgram(vertex_shader_id, fragment_shader_id);

    // Construímos a representação de um triângulo
    GLuint vertex_array_object_id = BuildTriangles();

    // Buscamos o endereço das variáveis definidas dentro do Vertex Shader.
    // Utilizaremos estas variáveis para enviar dados para a placa de vídeo
    // (GPU)! Veja arquivo "shader_vertex.glsl".
    GLint model_uniform           = glGetUniformLocation(program_id, "model"); // Variável da matriz "model"
    GLint view_uniform            = glGetUniformLocation(program_id, "view"); // Variável da matriz "view" em shader_vertex.glsl
    GLint projection_uniform      = glGetUniformLocation(program_id, "projection"); // Variável da matriz "projection" em shader_vertex.glsl
    GLint render_as_black_uniform = glGetUniformLocation(program_id, "render_as_black"); // Variável booleana em shader_vertex.glsl

    // Habilitamos o Z-buffer. Veja slide 108 do documento "Aula_09_Projecoes.pdf".
    glEnable(GL_DEPTH_TEST);

    // Variáveis auxiliares utilizadas para chamada de função
    // TextRendering_ShowModelViewProjection(), armazenando matrizes 4x4.
    glm::mat4 the_projection;
    glm::mat4 the_model;
    glm::mat4 the_view;

    float y = 2.0f*sin(g_CameraPhi);
    float z = 2.0f*cos(g_CameraPhi)*cos(g_CameraTheta);
    float x = 2.0f*cos(g_CameraPhi)*sin(g_CameraTheta);

    glm::vec4 camera_position_c = glm::vec4(0.0f,0.0f,0.0f,1.0f);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    Globals::g_Io = &ImGui::GetIO(); (void)Globals::g_Io;
    //Globals::g_Io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //Globals::g_Io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Read 'misc/fonts/README.txt' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //Globals::g_Io.Fonts->AddFontDefault();
    //Globals::g_Io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //Globals::g_Io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //Globals::g_Io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //Globals::g_Io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
    //ImFont* font = Globals::g_Io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, Globals::g_Io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != NULL);

    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    float nearplane = -0.1f;  // posição do "near plane"
    float farplane  = -10.0f; // posição do "far plane"
    #pragma endregion MAIN

    #pragma region [rgba(50, 100, 100, 0.2)] DRAW_LOOP
    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
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

        // Computamos a posição da câmera utilizando coordenadas esféricas.  As
        // variáveis g_CameraDistance, g_CameraPhi, e g_CameraTheta são
        // controladas pelo mouse do usuário. Veja as funções CursorPosCallback()
        // e ScrollCallback().
        y = 2.0f*sin(g_CameraPhi);
        z = 2.0f*cos(g_CameraPhi)*cos(g_CameraTheta);
        x = 2.0f*cos(g_CameraPhi)*sin(g_CameraTheta);
        // Abaixo definimos as variáveis que efetivamente definem a câmera virtual.
        // Veja slide 165 do documento "Aula_08_Sistemas_de_Coordenadas.pdf".
        glm::vec4 camera_lookat_l = glm::vec4(x+camera_position_c.x,-y+camera_position_c.y,z+camera_position_c.z,1.0f); // Ponto "l", para onde a câmera (look-at) estará sempre olhando
        glm::vec4 camera_view_vector = camera_lookat_l - camera_position_c; // Vetor "view", sentido para onde a câmera está virada
        glm::vec4 camera_up_vector   = glm::vec4(0.0f,1.0f,0.0f,0.0f); // Vetor "up" fixado para apontar para o "céu" (eixo Y global)
        glm::vec4 camera_right_vector = crossproduct(camera_view_vector, camera_up_vector);
        if(WPressed)
          camera_position_c  += 0.01f*camera_view_vector;
        if(SPressed)
          camera_position_c  -= 0.01f*camera_view_vector;
        if(APressed)
          camera_position_c  -= 0.01f*camera_right_vector;
        if(DPressed)
          camera_position_c  += 0.01f*camera_right_vector;

        // Computamos a matriz "View" utilizando os parâmetros da câmera para
        // definir o sistema de coordenadas da câmera.  Veja slide 169 do
        // documento "Aula_08_Sistemas_de_Coordenadas.pdf".
        glm::mat4 view = Matrix_Camera_View(camera_position_c, camera_view_vector, camera_up_vector);
        // Agora computamos a matriz de Projeção.
        glm::mat4 projection;
        // Note que, no sistema de coordenadas da câmera, os planos near e far
        // estáo no sentido negativo! Veja slides 198-200 do documento
        // "Aula_09_Projecoes.pdf".
        if (g_UsePerspectiveProjection)
        {
            // Projeção Perspectiva.
            // Para definição do field of view (FOV), veja slide 234 do
            // documento "Aula_09_Projecoes.pdf".
            float field_of_view = 3.141592 / 3.0f;
            projection = Matrix_Perspective(field_of_view, g_ScreenRatio, nearplane, farplane);
        }
        else
        {
            // Projeção Ortográfica.
            // Para definição dos valores l, r, b, t ("left", "right", "bottom", "top"),
            // veja slide 243 do documento "Aula_09_Projecoes.pdf".
            // Para simular um "zoom" ortográfico, computamos o valor de "t"
            // utilizando a variável g_CameraDistance.
            float t = 1.5f*g_CameraDistance/2.5f;
            float b = -t;
            float r = t*g_ScreenRatio;
            float l = -r;
            projection = Matrix_Orthographic(l, r, b, t, nearplane, farplane);
        }

        // Enviamos as matrizes "view" e "projection" para a placa de vídeo
        // (GPU). Veja o arquivo "shader_vertex.glsl", onde estas são
        // efetivamente aplicadas em todos os pontos.
        glUniformMatrix4fv(view_uniform       , 1 , GL_FALSE , glm::value_ptr(view));
        glUniformMatrix4fv(projection_uniform , 1 , GL_FALSE , glm::value_ptr(projection));

        // Vamos desenhar 3 instâncias (cópias) do cubo
        for (int i = 1; i <= 3; ++i)
        {
            // Cada cópia do cubo possui uma matriz de modelagem independente,
            // já que cada cópia estará em uma posição (rotação, escala, ...)
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
            else if ( i == 2 )
            {
                // A segunda cópia do cubo sofrerá um escalamento não-uniforme,
                // seguido de uma rotação no eixo (1,1,1), e uma translação em Z (nessa ordem!).
                model = Matrix_Translate(0.0f, 0.0f, -2.0f) // TERCEIRO translação
                      * Matrix_Rotate(3.141592f / 8.0f, glm::vec4(1.0f,1.0f,1.0f,0.0f)) // SEGUNDO rotação
                      * Matrix_Scale(2.0f, 0.5f, 0.5f); // PRIMEIRO escala
            }
            else if ( i == 3 )
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
                the_projection = projection;
                the_view = view;
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
            if ( i == 3 )
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


        //############# Start the Dear ImGui frame ##############
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {
            // static float f = 0.0f;
            static int counter = 0;
            // Create a window called "Hello, world!" and append into it.
            ImGui::Begin("Settings");
            // Edit 3 floats representing a color
            ImGui::ColorEdit3("clear color", (float*)&clear_color);

            // Buttons return true when clicked (most widgets return true when edited/activated)
            if (ImGui::Button("Button"))
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Checkbox("Perspective Projection", &g_UsePerspectiveProjection);

            ImGui::Text("Block Settings");
            ImGui::SliderFloat("Angle Z", &g_AngleZ, -10.0f, 10.0f);
            ImGui::SliderFloat("Angle Y", &g_AngleY, -10.0f, 10.0f);
            ImGui::SliderFloat("Angle X", &g_AngleX, -10.0f, 10.0f);

            ImGui::Text("Frustum Settings");
            ImGui::SliderFloat("Near Plane", &nearplane, -10.0f, 10.0f);
            ImGui::SliderFloat("Far Plane", &farplane, -10.0f, 10.0f);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        // 3. Show another simple window.
        if (show_another_window)
        {
            // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Begin("Another Window", &show_another_window);
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    //############# End the Dear ImGui frame ##############

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
    cube_faces.name           = "Cubo (faces coloridas)";
    cube_faces.first_index    = (void*)0; // Primeiro índice está em indices[0]
    cube_faces.num_indices    = 36;       // último índice está em indices[35]; total de 36 índices.
    cube_faces.rendering_mode = GL_TRIANGLES; // índices correspondem ao tipo de rasterização GL_TRIANGLES.

    // Adicionamos o objeto criado acima na nossa cena virtual (Globals::g_VirtualScene).
    Globals::g_VirtualScene["cube_faces"] = cube_faces;

    // Criamos um segundo objeto virtual (SceneObject) que se refere às arestas
    // pretas do cubo.
    SceneObject cube_edges;
    cube_edges.name           = "Cubo (arestas pretas)";
    cube_edges.first_index    = (void*)(36*sizeof(GLuint)); // Primeiro índice está em indices[36]
    cube_edges.num_indices    = 24; // último índice está em indices[59]; total de 24 índices.
    cube_edges.rendering_mode = GL_LINES; // índices correspondem ao tipo de rasterização GL_LINES.

    // Adicionamos o objeto criado acima na nossa cena virtual (Globals::g_VirtualScene).
    Globals::g_VirtualScene["cube_edges"] = cube_edges;

    // Criamos um terceiro objeto virtual (SceneObject) que se refere aos eixos XYZ.
    SceneObject axes;
    axes.name           = "Eixos XYZ";
    axes.first_index    = (void*)(60*sizeof(GLuint)); // Primeiro índice está em indices[60]
    axes.num_indices    = 6; // último índice está em indices[65]; total de 6 índices.
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

/*
Cria callbacks pra todos eventos: (KeyPress, MouseButtonPress, CursorPosition, Scroll, Framebuffer, Error)
*/
void SetCallbacks(GLFWwindow* window){
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

/*
Initialize OpenGL loader
*/
bool InitializeOpenGLLoader(){
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
    return gl3wInit() != 0;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
    return glewInit() != GLEW_OK;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
    return gladLoadGL() == 0;
#else
    return false; // If you use IMGUI_IMPL_OPENGL_LOADER_CUSTOM, your loader is likely to requires some form of initialization.
#endif
}

/*
Pedimos para utilizar OpenGL versão 3.3 (ou superior)
Pedimos para utilizar o perfil "core", isto é, utilizaremos somente as
funções modernas de OpenGL.
*/
void InitializeOpenGL3(){
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

/*
Imprimimos no terminal informações sobre a GPU do sistema
*/
void PrintGPUInformation(){
    const GLubyte *vendor      = glGetString(GL_VENDOR);
    const GLubyte *renderer    = glGetString(GL_RENDERER);
    const GLubyte *glversion   = glGetString(GL_VERSION);
    const GLubyte *glslversion = glGetString(GL_SHADING_LANGUAGE_VERSION);

    printf("GPU: %s, %s, OpenGL %s, GLSL %s\n", vendor, renderer, glversion, glslversion);
}
#pragma endregion FUNCTIONS