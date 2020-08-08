float fract(float x)
{
  return x - ((int)x);
}

float rnd(float x)
{
  return fract(sinf(x) * 1e4);
}