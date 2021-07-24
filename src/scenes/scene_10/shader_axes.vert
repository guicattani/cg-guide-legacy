#version 330 core

// Atributos de vértice recebidos como entrada ("in") pelo Vertex Shader.
// Veja a função BuildTriangle() em "main.cpp".
layout (location = 0) in vec4 model_coefficients;
layout (location = 1) in vec4 color_coefficients;

// Matrizes computadas no código C++ e enviadas para a GPU
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform bool render_as_black;
out vec4 cor_interpolada_pelo_rasterizador;

void main()
{

    gl_Position = projection * view * model * model_coefficients;
    cor_interpolada_pelo_rasterizador = color_coefficients;
}
