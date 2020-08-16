#include "ShaderBreathing.h"

void ShaderBreathing::update(Strip *strip, float deltaTime)
{
  LEDShader::update(strip, deltaTime);

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
    color = CHSV(hueWithOffset, saturation, value);

    blend(strip->leds, i, color);
  }
}