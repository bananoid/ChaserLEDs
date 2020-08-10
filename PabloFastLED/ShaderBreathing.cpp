#include "ShaderBreathing.h"
// #include "mathUtils.h"

void ShaderBreathing::render(Strip *strip, BlendingMode blendingMode)
{
  float intensity;
  float value;
  float x;
  CRGB color;
  for (int i = strip->startInx; i < strip->numOfLed + strip->startInx; i++)
  {

    x = (this->position + i) * scale;

    intensity = sinf(fmod(x, TWO_PI)) * 0.5 + 0.5;
    intensity = intensity * (1.0 - density) + density;

    value = intensity * brightness;
    color = CHSV(hue, saturation, value);

    blend(strip->leds, i, color, blendingMode);
  }
}