#version 330 core

layout (location = 0) in vec4 model_coefficients;
layout (location = 1) in vec4 normal_coefficients;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform bool second_camera;
uniform float simulate_perspective_slider;
uniform mat4 first_camera_projection;
uniform mat4 first_camera_view;

out vec4 position_world;
out vec4 normal;

void main()
{
    vec4 position_perspective, position_simulated;
    normal = inverse(transpose(model)) * normal_coefficients;
    position_world = model * model_coefficients;

    if(second_camera) {
      vec4 model_div_w = first_camera_projection * first_camera_view * model * model_coefficients;
      model_div_w.x = -model_div_w.x;
      if(model_div_w.w > 0)
        model_div_w = model_div_w/model_div_w.w;
      position_simulated = projection * view * model_div_w;
    }

    position_perspective = projection * view * model * model_coefficients;

    if(second_camera)
      gl_Position = mix(position_perspective, position_simulated, simulate_perspective_slider);
    else
      gl_Position = position_perspective;

    normal.w = 0.0;
}
