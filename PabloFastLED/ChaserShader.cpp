#include "ChaserShader.h"

void ChaserShader::render(Strip *strip, BlendingMode blendingMode)
{
  float intensity;
  float value;
  float x;
  CRGB color;
  for (int i = strip->startInx; i < strip->numOfLed + strip->startInx; i++)
  {

    x = this->position + i * scale;

    intensity = GFXUtils::chaserNoiseSmooth(x, density);

    value = intensity * brightness;
    color = CHSV(hue, saturation, value);

    blend(strip->leds, i, color, blendingMode);
  }
}