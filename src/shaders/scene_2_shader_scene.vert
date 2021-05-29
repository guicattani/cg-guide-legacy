#version 330 core

// Atributos de vértice recebidos como entrada ("in") pelo Vertex Shader.
// Veja a função BuildTriangle() em "main.cpp".
layout (location = 0) in vec4 NDC_coefficients;
layout (location = 1) in vec4 color_coefficients;

// Atributos de vértice que serão gerados como saída ("out") pelo Vertex Shader.
// ** Estes serão interpolados pelo rasterizador! ** gerando, assim, valores
// para cada fragmento, os quais serão recebidos como entrada pelo Fragment
// Shader. Veja o arquivo "shader_fragment.glsl".
out vec4 cor_interpolada_pelo_rasterizador;

void main()
{
    // A variável gl_Position define a posição final de cada vértice
    // OBRIGATORIAMENTE em "normalized device coordinates" (NDC), onde cada
    // coeficiente está entre -1 e 1.  (Veja slides 163 e 168 do documento
    // "Aula_03_Rendering_Pipeline_Grafico.pdf").
    //
    // Como o código em "main.cpp" já define estes vértices em NDC (veja o
    // array NDC_coefficients), simplesmente copiamos tais valores para a
    // variável gl_Position.
    gl_Position = NDC_coefficients;

    // Como as variáveis acima são vetores com 4 coeficientes (tipo vec4),
    // também é possível acessar e modificar cada coeficiente de maneira
    // independente. Esses são indexados pelos nomes x, y, z, e w (nessa
    // ordem, isto é, 'x' é o primeiro coeficiente, 'y' é o segundo, ...):
    //
    //     gl_Position.x = NDC_coefficients.x;
    //     gl_Position.y = NDC_coefficients.y;
    //     gl_Position.z = NDC_coefficients.z;
    //     gl_Position.w = NDC_coefficients.w;
    //

    // Copiamos o atributo cor (de entrada) de cada vértice para a variável
    // "cor_interpolada_pelo_rasterizador". Esta variável será interpolada pelo
    // rasterizador, gerando valores interpolados para cada fragmento!  Veja o
    // arquivo "shader_fragment.glsl".
    cor_interpolada_pelo_rasterizador = color_coefficients;

    // Nas aulas sobre transformações geométrica veremos como transformar
    // coeficientes em outros sistemas de coordenadas para coeficientes NDC.
}
