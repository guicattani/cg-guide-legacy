#version 330 core

layout (location = 0) in vec4 model_coefficients;
layout (location = 1) in vec4 normal_coefficients;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 compensate_view_matrices_positions;
uniform bool second_camera;

out vec4 position_world;
out vec4 normal;

void main()
{
    if(second_camera) {
      vec4 model_div_w = model * model_coefficients;
      if(model_div_w.w > 0)
        model_div_w = model_div_w/model_div_w.w;
      gl_Position = projection * view * model_div_w;

      normal = inverse(transpose(model)) * normal_coefficients;
      position_world = model * model_coefficients;
    }
    else {
      gl_Position = projection * view * model * model_coefficients;
      normal = inverse(transpose(model)) * normal_coefficients;
      position_world = model * model_coefficients;
    }

    normal.w = 0.0;
}
