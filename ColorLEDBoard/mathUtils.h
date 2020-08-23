float fract(float x)
{
  return x - ((int)x);
}

float rnd(float x)
{
  return fract((sinf(x) * 0.5 + 0.5) * 1e4);
}

float clamp(float x, float minV, float maxV)
{
  return min(max(x, minV), maxV);
}

float mix(float a, float b, float t)
{
  return a * (1.0 - t) + b * t;
}

float smoothstep(float start, float stop, float x)
{
  float t = clamp((x - start) / (stop - start), 0.0, 1.0);
  return t * t * (3.0 - 2.0 * t);
}

struct vec2
{
  float x;
  float y;
  vec2(float x, float y)
  {
    this->x = x;
    this->y = y;
  }
};

float dot(vec2 a, vec2 b)
{
  return a.x * b.x + a.y * b.y;
}

float chaserNoise(float x, float density)
{
  float i = (int)x;
  float f = fract(x);
  float denR = 0.05;
  float a = smoothstep(density + denR, density - denR, rnd(i));
  float b = smoothstep(density + denR, density - denR, rnd(i + 1));

  float u = smoothstep(0, 1, f);
  return mix(a, b, u);
}

vec2 sinf(vec2 st)
{
  return vec2(sinf(st.x), sinf(st.y));
}

vec2 random2(vec2 st)
{
  st = vec2(dot(st, vec2(127.1, 311.7)),
            dot(st, vec2(269.5, 183.3)));
  return vec2(
      -1.0 + 2.0 * fract(sinf(st.x) * 43758.5453123),
      -1.0 + 2.0 * fract(sinf(st.x) * 43758.5453123));
}

float pnoise(float x, float y)
{
  float ix = floor(x);
  float fx = fract(x);
  float iy = floor(y);
  float fy = fract(y);

  float ux = fx * fx * (3.0 - 2.0 * fx);
  float uy = fy * fy * (3.0 - 2.0 * fy);

  return mix(mix(dot(random2(vec2(ix, iy)), vec2(fx, fy)),
                 dot(random2(vec2(ix + 1.0, iy)), vec2(fx - 1.0, fy)), ux),
             mix(dot(random2(vec2(ix, iy + 1.0)), vec2(fx, fy - 1.0)),
                 dot(random2(vec2(ix + 1.0, iy + 1.0)), vec2(fx - 1.0, fy - 1.0)), ux),
             uy);
}

float snoise(float x)
{
  return (sinf(2.0 * x) + sinf(PI * x)) * 0.5 + 0.5;
}