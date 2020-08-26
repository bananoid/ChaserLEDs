#ifndef SHADER_BREATHING_H
#define SHADER_BREATHING_H

#include "../LEDShader.h"

class ShaderBreathing : public LEDShader
{
public:
  ShaderBreathing() : LEDShader(){};
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

      x = (this->position + i) * scale * scaleOffset;

      intensity = sinf(fmod(x, TWO_PI)) * 0.5 + 0.5;
      intensity = intensity * (1.0 - den) + den;

      value = intensity * brightness;
      color = CHSV(hueWithOffset, saturation, value);

      blend(strip->leds, i, color);
    }
  }
};

#endif