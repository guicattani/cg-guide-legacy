#version 330 core

layout (location = 0) in vec4 NDC_coefficients;
layout (location = 1) in vec4 color_coefficients;

out vec4 interpolated_color;

void main()
{

    gl_Position = vec4(NDC_coefficients.x, NDC_coefficients.y, NDC_coefficients.z, 1.0);
    interpolated_color = color_coefficients;
}
