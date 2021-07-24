#version 330 core

in vec4 position_world;
in vec4 normal;
in vec4 position_model;
in vec2 texcoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform sampler2D diffuseTexture;

uniform vec4 bbox_min;
uniform vec4 bbox_max;

uniform int texture_projection;
#define SPHERICAL_PROJECTION 0
#define CYLINDRICAL_PROJECTION 1
#define AA_BOUNDING_BOX_PROJECTION 2
#define TEXTURE_COORDINATES 3

out vec3 color;

#define M_PI   3.14159265358979323846
#define M_PI_2 1.57079632679489661923
void main()
{
    vec4 origin = vec4(0.0, 0.0, 0.0, 1.0);
    vec4 camera_position = inverse(view) * origin;

    vec4 p = position_world;
    vec4 n = normalize(normal);
    vec4 l = normalize(vec4(1.0,1.0,0.0,0.0));
    vec4 v = normalize(camera_position - p);

    float U = 0.0;
    float V = 0.0;

    if ( texture_projection == SPHERICAL_PROJECTION )
    {
        vec4 bbox_center = (bbox_min + bbox_max) / 2.0;
        float radius = length(position_model - bbox_center);

        vec4 dashP = bbox_center + radius*normalize(position_model - bbox_center);

        float angleRo = sqrt(pow(dashP.x, 2) + pow(dashP.y, 2) + pow(dashP.z, 2));
        float angleTheta = atan(dashP.x, dashP.z);
        float anglePhi = asin(dashP.y / angleRo);

        U = (angleTheta + M_PI)/(2 * M_PI);
        V = (anglePhi + M_PI_2)/M_PI;

    }
    else if ( texture_projection == CYLINDRICAL_PROJECTION )
    {
        vec4 bbox_center = (bbox_min + bbox_max) / 2.0;
        float radius = length(position_model - bbox_center);

        vec4 dashP = bbox_center + radius*normalize(position_model - bbox_center);
        float angleTheta = atan(dashP.x, dashP.z);

        float miny = bbox_min.y;
        float maxy = bbox_max.y;

        U = (angleTheta + M_PI)/(2 * M_PI);
        V = (position_model.y)/(maxy - miny);
    }
    else if ( texture_projection == AA_BOUNDING_BOX_PROJECTION )
    {
        float minx = bbox_min.x;
        float maxx = bbox_max.x;

        float miny = bbox_min.y;
        float maxy = bbox_max.y;

        float minz = bbox_min.z;
        float maxz = bbox_max.z;

        U = (position_model.x - minx)/(maxx - minx);
        V = (position_model.y - miny)/(maxy - miny);
    }
    else if ( texture_projection == TEXTURE_COORDINATES )
    {
        // Coordenadas de textura do plano, obtidas do arquivo OBJ.
        U = texcoords.x;
        V = texcoords.y;
    }

    // Obtemos a refletância difusa a partir da leitura da imagem TextureImage0
    vec3 Kd0 = texture(diffuseTexture, vec2(U,V)).rgb;

    // Equação de Iluminação
    float lambert = max(0,dot(n,l));

    color = Kd0 * (lambert + 0.1);

    // Cor final com correção gamma, considerando monitor sRGB.
    // Veja https://en.wikipedia.org/w/index.php?title=Gamma_correction&oldid=751281772#Windows.2C_Mac.2C_sRGB_and_TV.2Fvideo_standard_gammas
    color = pow(color, vec3(1.0,1.0,1.0) / 2.2);
}
