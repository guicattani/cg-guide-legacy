#ifndef CLASS_ADD_HEADERS
#define CLASS_ADD_HEADERS
#include "headers.h"
#endif


glm::vec3 lerp(float t, glm::vec3 a, glm::vec3 b);
glm::vec3 bezier3(float t, glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d);
void bezier3MinMax(GraphMinMax* graphMinMax, glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d);
void sampledBezierPoints(GLfloat *coefficients, int samples, glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d);