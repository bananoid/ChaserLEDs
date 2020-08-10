#include "ChaserShader.h"
#include "mathUtils.h"

void ChaserShader::render(Strip *strip)
{
  float intensity;
  float value;
  float x;

  for (int i = strip->startInx; i < strip->numOfLed + strip->startInx; i++)
  {

    x = this->position + i;

    intensity = chaserNoise(x, density);

    value = intensity * brightness;
    strip->leds[i] = CHSV(hue, saturation, value);
  }
}