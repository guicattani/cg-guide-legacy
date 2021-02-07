template <typename T>
T lerp(float t, T a, T b)
{
  return a + t * (b - a);
}

template <typename T>
T bezier3(float t, T a, T b, T c, T d)
{
  T ab = lerp(t, a, b);
  T bc = lerp(t, b, c);
  T cd = lerp(t, c, d);
  T abc = lerp(t, ab, bc);
  T bcd = lerp(t, bc, cd);
  T abcd = lerp(t, abc, bcd);
  return abcd;
}

template <typename T>
void sampledBezierPoints(GLfloat *coefficients, int samples, T a, T b, T c, T d)
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

void createBezierIndices(GLuint *indices, int amount)
{
  for (int i = 0; i < amount; i++)
  {
    int offset = i * 2;
    indices[offset] = i;
    indices[offset] = i + 1;
  }
}