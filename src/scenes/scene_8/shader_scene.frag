#version 330 core

in vec4 position_world;
in vec4 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

#define SPHERE 0
#define SPHERE_2 1
#define CAMERA 2
#define PLANE 3
#define SPHERE_LOOK_AT 4
uniform int object_id;

out vec3 color;

void main()
{
    // Obtemos a posição da câmera utilizando a inversa da matriz que define o
    // sistema de coordenadas da câmera.
    vec4 origin = vec4(0.0, 0.0, 0.0, 1.0);
    vec4 camera_position = inverse(view) * origin;

    vec4 p = position_world;

    // Normal do fragmento atual, interpolada pelo rasterizador a partir das
    // normais de cada vértice.
    vec4 n = normalize(normal);

    // Vetor que define o sentido da fonte de luz em relação ao ponto atual.
    vec4 l = normalize(vec4(1.0,1.0,0.5,0.0));

    // Vetor que define o sentido da câmera em relação ao ponto atual.
    vec4 v = normalize(camera_position - p);

    // Vetor que define o sentido da reflexão especular ideal.
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
    else if ( object_id == SPHERE_2 )
    {
        // Propriedades espectrais da esfera
        Kd = vec3(0.0,0.0,0.8);
        Ks = vec3(0.0,0.0,0.0);
        Ka = Kd / 2;
        q = 1.0;
    }
    else if ( object_id == SPHERE_LOOK_AT )
    {
        // Propriedades espectrais da esfera
        Kd = vec3(1.0,0.0,0.0);
        Ks = vec3(0.0,0.0,0.0);
        Ka = Kd / 2;
        q = 1.0;
    }
    else if ( object_id == CAMERA )
    {
        // Propriedades espectrais da esfera
        Kd = vec3(1.0,1.0,1.0);
        Ks = vec3(0.0,0.0,0.0);
        Ka = Kd / 2;
        q = 1.0;
    }
    else if ( object_id == PLANE )
    {
        // Propriedades espectrais da esfera
        Kd = vec3(0.6,0.6,0.6);
        Ks = vec3(0.0,0.0,0.0);
        Ka = Kd / 2;
        q = 1.0;
    }
    else // Objeto desconhecido = preto
    {
        Kd = vec3(0.0,0.0,0.0);
        Ks = vec3(0.0,0.0,0.0);
        Ka = vec3(0.0,0.0,0.0);
        q = 1.0;
    }

    // Espectro da fonte de iluminação
    vec3 I = vec3(1.0,1.0,1.0);

    // Espectro da luz ambiente
    vec3 Ia = vec3(0.2,0.2,0.2);

    // Termo difuso utilizando a lei dos cossenos de Lambert
    vec3 lambert_diffuse_term = Kd * I * max(0,dot(n,l));

    // Termo ambiente
    vec3 ambient_term = Ka * Ia; // PREENCHA AQUI o termo ambiente

    // Termo especular utilizando o modelo de iluminação de Phong
    vec3 phong_specular_term  = Ks * I * pow(max(0,dot(r,v)), q);

    color = lambert_diffuse_term + ambient_term + phong_specular_term;
    color = pow(color, vec3(1.0,1.0,1.0)/2.2);
}
