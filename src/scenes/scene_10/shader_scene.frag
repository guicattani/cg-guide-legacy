#version 330 core

in vec4 position_world;
in vec4 normal;
in vec4 position_model;
in vec2 texcoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform sampler2D diffuseTexture;
uniform bool use_world_coordinates;

uniform sampler2D cubemapTopTexture;
uniform sampler2D cubemapBottomTexture;
uniform sampler2D cubemapLeftTexture;
uniform sampler2D cubemapRightTexture;
uniform sampler2D cubemapFrontTexture;
uniform sampler2D cubemapBackTexture;

uniform vec4 bbox_min;
uniform vec4 bbox_max;
uniform vec4 bbox_center;

uniform float cylinder_height;

uniform vec4 arrow_position;
uniform vec4 arrow_point_in_plane;

uniform int texture_projection;
#define SPHERICAL_PROJECTION 0
#define CYLINDRICAL_PROJECTION 1
#define AA_BOUNDING_BOX_PROJECTION 2
#define CUBE_MAP 3
#define TEXTURE_COORDINATES 4

out vec3 color;

#define M_PI   3.14159265358979323846
#define M_PI_2 1.57079632679489661923
void main()
{
    float U = 0.0;
    float V = 0.0;

    vec4 position;
    if(use_world_coordinates)
      position = position_world;
    else
      position = position_model;

    int cube_map_index;

    if ( texture_projection == SPHERICAL_PROJECTION )
    {
        vec4 dashP = bbox_center + normalize(position - bbox_center);

        float angleRo = sqrt(pow(dashP.x, 2) + pow(dashP.y, 2) + pow(dashP.z, 2));
        float angleTheta = atan(dashP.x, dashP.z);
        float anglePhi = asin(dashP.y / angleRo);

        U = (angleTheta + M_PI)/(2 * M_PI);
        V = (anglePhi + M_PI_2)/M_PI;
    }
    else if ( texture_projection == CYLINDRICAL_PROJECTION )
    {
        vec4 dashP = bbox_center + normalize(position - bbox_center);

        float angleTheta = atan(dashP.x / dashP.z);

        U = (angleTheta + M_PI)/(2 * M_PI);
        V = position.y / (cylinder_height * abs(bbox_min.y - bbox_max.y));
    }
    else if ( texture_projection == AA_BOUNDING_BOX_PROJECTION )
    {
        float minx = bbox_min.x;
        float maxx = bbox_max.x;

        float miny = bbox_min.y;
        float maxy = bbox_max.y;

        float minz = bbox_min.z;
        float maxz = bbox_max.z;

        U = (position.x - minx)/(maxx - minx);
        V = (position.y - miny)/(maxy - miny);
    }
    else if ( texture_projection == CUBE_MAP )
    {
      vec4 dashP = position - bbox_center;

      float absX = abs(dashP.x);
      float absY = abs(dashP.y);
      float absZ = abs(dashP.z);

      bool isXPositive = dashP.x > 0 ? true : false;
      bool isYPositive = dashP.y > 0 ? true : false;
      bool isZPositive = dashP.z > 0 ? true : false;

      float maxAxis, uc, vc;

      // POSITIVE X
      if (isXPositive && absX >= absY && absX >= absZ) {
        // u (0 to 1) goes from +z to -z
        // v (0 to 1) goes from -y to +y
        maxAxis = absX;
        uc = -dashP.z;
        vc = dashP.y;
        cube_map_index = 0;
      }
      // NEGATIVE X
      if (!isXPositive && absX >= absY && absX >= absZ) {
        // u (0 to 1) goes from -z to +z
        // v (0 to 1) goes from -y to +y
        maxAxis = absX;
        uc = dashP.z;
        vc = dashP.y;
        cube_map_index = 1;
      }
      // POSITIVE Y
      if (isYPositive && absY >= absX && absY >= absZ) {
        // u (0 to 1) goes from -x to +x
        // v (0 to 1) goes from +z to -z
        maxAxis = absY;
        uc = dashP.x;
        vc = -dashP.z;
        cube_map_index = 2;
      }
      // NEGATIVE Y
      if (!isYPositive && absY >= absX && absY >= absZ) {
        // u (0 to 1) goes from -x to +x
        // v (0 to 1) goes from -z to +z
        maxAxis = absY;
        uc = dashP.x;
        vc = dashP.z;
        cube_map_index = 3;
      }
      // POSITIVE Z
      if (isZPositive && absZ >= absX && absZ >= absY) {
        // u (0 to 1) goes from -x to +x
        // v (0 to 1) goes from -y to +y
        maxAxis = absZ;
        uc = dashP.x;
        vc = dashP.y;
        cube_map_index = 4;
      }
      // NEGATIVE Z
      if (!isZPositive && absZ >= absX && absZ >= absY) {
        // u (0 to 1) goes from +x to -x
        // v (0 to 1) goes from -y to +y
        maxAxis = absZ;
        uc = -dashP.x;
        vc = dashP.y;
        cube_map_index = 5;
      }

      // Convert range from -1 to 1 to 0 to 1
      U = 0.5f * (uc / maxAxis + 1.0f);
      V = 0.5f * (vc / maxAxis + 1.0f);
    }
    else if ( texture_projection == TEXTURE_COORDINATES )
    {
        // Coordenadas de textura do plano, obtidas do arquivo OBJ.
        U = texcoords.x;
        V = texcoords.y;
    }

    vec4 origin = vec4(0.0, 0.0, 0.0, 1.0);
    vec4 camera_position = inverse(view) * origin;

    vec4 p = position_world;
    vec4 n = normalize(normal);
    vec4 l = normalize(vec4(1.0,1.0,0.0,0.0));
    vec4 v = normalize(camera_position - p);

    // Obtemos a refletância difusa a partir da leitura da imagem TextureImage0
    vec3 Kd0;
    if(texture_projection != CUBE_MAP)
      Kd0 = texture(diffuseTexture, vec2(U,V)).rgb;
    else if (cube_map_index == 0)
      Kd0 = texture(cubemapLeftTexture, vec2(U,V)).rgb;
    else if (cube_map_index == 1)
      Kd0 = texture(cubemapRightTexture, vec2(U,V)).rgb;
    else if (cube_map_index == 2)
      Kd0 = texture(cubemapTopTexture, vec2(U,V)).rgb;
    else if (cube_map_index == 3)
      Kd0 = texture(cubemapBottomTexture, vec2(U,V)).rgb;
    else if (cube_map_index == 4)
      Kd0 = texture(cubemapFrontTexture, vec2(U,V)).rgb;
    else
      Kd0 = texture(cubemapBackTexture, vec2(U,V)).rgb;

    if ( texture_projection == AA_BOUNDING_BOX_PROJECTION )
    {
      float distance_point = distance(arrow_point_in_plane, vec4(position.x, position.y, 1.0, 1.0));
      if(distance_point < 0.07) {
        Kd0 = vec3(0.0, 0.0, 0.0);
      }
      if(distance_point < 0.06) {
        Kd0 = vec3(0.0, 1.0, 0.0);
      }
    }
    else
    {
      float angle_between_arrow_and_position = acos(dot(normalize(bbox_center - arrow_position), normalize(bbox_center - position)));

      if(angle_between_arrow_and_position < 0.07) {
        Kd0 = vec3(0.0, 0.0, 0.0);
      }
      if(angle_between_arrow_and_position < 0.06) {
        Kd0 = vec3(0.0, 1.0, 0.0);
      }
    }

    // Equação de Iluminação
    float lambert = max(0,dot(n,l));

    color = Kd0 * (lambert + 0.1);

    // Cor final com correção gamma, considerando monitor sRGB.
    // Veja https://en.wikipedia.org/w/index.php?title=Gamma_correction&oldid=751281772#Windows.2C_Mac.2C_sRGB_and_TV.2Fvideo_standard_gammas
    color = pow(color, vec3(1.0,1.0,1.0) / 2.2);
}
