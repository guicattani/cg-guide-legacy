
#ifndef CLASS_HEADER_BEZIER
#define CLASS_HEADER_BEZIER
#include "bezier.h"
#endif

#ifndef CLASS_HEADER_SCENE_GLOBALS
#define CLASS_HEADER_SCENE_GLOBALS
#include "globals_scenes.h"
#endif

glm::vec3 lerp(float t, glm::vec3 a, glm::vec3 b)
{
  return a + t * (b - a);
}

glm::vec3 bezier3(float t, glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d)
{
  glm::vec3 ab = lerp(t, a, b);
  glm::vec3 bc = lerp(t, b, c);
  glm::vec3 cd = lerp(t, c, d);
  glm::vec3 abc = lerp(t, ab, bc);
  glm::vec3 bcd = lerp(t, bc, cd);
  glm::vec3 abcd = lerp(t, abc, bcd);

  return abcd;
}

void bezier3MinMax(GraphMinMax* graphMinMax, glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d) {
  for(int i = 0; i <= 100; i++) {
    glm::vec3 bezier = bezier3((float) i/100, a, b, c, d);
    if(bezier.x < graphMinMax->x.min)
      graphMinMax->x.min = bezier.x;
    if(bezier.x > graphMinMax->x.max)
      graphMinMax->x.max = bezier.x;

    if(bezier.y < graphMinMax->y.min)
      graphMinMax->y.min = bezier.y;
    if(bezier.y > graphMinMax->y.max)
      graphMinMax->y.max = bezier.y;

    if(bezier.z < graphMinMax->z.min)
      graphMinMax->z.min = bezier.z;
    if(bezier.z > graphMinMax->z.max)
      graphMinMax->z.max = bezier.z;
  }
}


void sampledBezierPoints(GLfloat *coefficients, int samples, glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d)
{
  for (int i = 0; i < samples; i++)
  {
    auto point = bezier3(i / (float)samples, a, b, c, d);

    int offset = i * 4;
    coefficients[offset] = point.x;
    coefficients[offset + 1] = point.y;
    coefficients[offset + 2] = point.z;
    coefficients[offset + 3] = 1.0f;
  }
}
