#include "ChaserShader.h"

void ChaserShader::update(Strip *strip, float deltaTime)
{
  LEDShader::update(strip, deltaTime);

  float intensity;
  float value;
  float x;
  CRGB color;
  for (int i = strip->startInx; i < strip->numOfLed + strip->startInx; i++)
  {

    x = this->position + i * scale;

    intensity = GFXUtils::chaserNoiseSmooth(x, density);

    value = intensity * brightness;
    color = CHSV(hueWithOffset, saturation, value);

    blend(strip->leds, i, color);
  }
}