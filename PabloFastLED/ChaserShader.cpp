#include "ChaserShader.h"
#include "mathUtils.h"
#include "Perlin.h"

void ChaserShader::render(CRGB *leds, int startInx)
{
  float intensity;
  float value;
  float x;

  for (int i = startInx; i < this->numPixels + startInx; i++)
  {

    x = this->position + i;

    intensity = chaserNoise(x, density);

    if (leds[i].r + leds[i].g + leds[i].b < 50) // to prevent mixing colors. TODO: replace with blending modes
    {
      value = intensity * brightness;
      leds[i] = CHSV(hue, saturation, value);
    }
  }
}