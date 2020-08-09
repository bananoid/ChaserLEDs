#include "ChaserShader.h"
#include "mathUtils.h"
#include "Perlin.h"

void ChaserShader::render(CRGB *leds)
{
  float intensity;

  for (int i = 0; i < this->numPixels; i++)
  {
    // density = sinf(time * 0.5234) * 0.4 + 0.5;

    float x = i * scale + time * speed;

    intensity = chaserNoise(x, density);

    leds[i] = CHSV(0, 255, intensity * 255);
  }
}