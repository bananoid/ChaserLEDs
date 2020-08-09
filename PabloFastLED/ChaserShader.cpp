#include "ChaserShader.h"
#include "mathUtils.h"
#include "Perlin.h"

void ChaserShader::render(CRGB *leds)
{
  float intensity;
  float value;
  float x;

  for (int i = 0; i < this->numPixels; i++)
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