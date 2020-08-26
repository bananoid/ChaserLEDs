#ifndef SHADER_NOISE_H
#define SHADER_NOISE_H

#include "../LEDShader.h"

class ShaderNoise : public LEDShader
{
public:
  ShaderNoise() : LEDShader(){};
  void update(Strip *strip, float deltaTime)
  {
    LEDShader::update(strip, deltaTime);

    float intensity;
    float value;
    float x;
    CRGB color;

    float den = density + densityOffset;

    for (int i = strip->startInx; i < strip->numOfLed + strip->startInx; i++)
    {
      x = this->position + i * scale * scaleOffset;

      intensity = GFXUtils::rnd(x) > density ? 1 : 0;

      value = intensity * brightness;
      color = CHSV(hueWithOffset, saturation, value);

      blend(strip->leds, i, color);
    }
  }
};

#endif