#version 330 core

in vec4 position_world;
in vec4 normal;
in vec2 tex_coords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform sampler2D diffuseTexture;

#define SPHERE 0
uniform int object_id;

out vec3 color;

void main()
{
    vec4 origin = vec4(0.0, 0.0, 0.0, 1.0);
    vec4 camera_position = inverse(view) * origin;

    vec4 p = position_world;
    vec4 n = normalize(normal);
    vec4 l = normalize(vec4(1.0,1.0,0.5,0.0));
    vec4 v = normalize(camera_position - p);
    vec4 r = -l + 2 * n * dot(n,l);

    // Parâmetros que definem as propriedades espectrais da superfície
    vec3 Kd; // Refletância difusa
    vec3 Ks; // Refletância especular
    vec3 Ka; // Refletância ambiente
    float q; // Expoente especular para o modelo de iluminação de Phong

    if ( object_id == SPHERE )
    {
        // Propriedades espectrais da esfera
        Kd = vec3(0.8,0.4,0.08);
        Ks = vec3(0.0,0.0,0.0);
        Ka = Kd / 2;
        q = 1.0;
    }
    else // Objeto desconhecido = preto
    {
        Kd = vec3(0.1,0.1,0.1);
        Ks = vec3(0.0,0.0,0.0);
        Ka = vec3(0.0,0.0,0.0);
        q = 1.0;
    }

    vec3 I = vec3(1.0,1.0,1.0);
    vec3 Ia = vec3(0.2,0.2,0.2);
    vec3 lambert_diffuse_term = Kd * I * max(0,dot(n,l));
    vec3 ambient_term = Ka * Ia; // PREENCHA AQUI o termo ambiente
    vec3 phong_specular_term  = Ks * I * pow(max(0,dot(r,v)), q);

    color = (lambert_diffuse_term + ambient_term + phong_specular_term) * texture(diffuseTexture, tex_coords).rgb;
    color = pow(color, vec3(1.0,1.0,1.0)/2.2);
}
