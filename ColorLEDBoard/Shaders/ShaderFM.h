#ifndef SHADER_FM_H
#define SHADER_FM_H

#include "../LEDShader.h"

class ShaderFM : public LEDShader
{
public:
  ShaderFM() : LEDShader(){};
  void update(Strip *strip, float deltaTime)
  {
    LEDShader::update(strip, deltaTime);

    float intensity;
    float value;
    float x;
    CRGB color;

    float oscA, oscB;
    float den = density * densityOffset;

    for (int i = strip->startInx; i < strip->numOfLed + strip->startInx; i++)
    {

      x = (this->position + i) * scale * scaleOffset;

      oscA = sinf(fmod(x * 0.05439234 + 1.04156, TWO_PI));
      oscB = sinf(fmod(x * 0.002454332 + 1.34156, TWO_PI));

      intensity = sinf(fmod(oscA * oscB * 30, TWO_PI)) * 0.5 + 0.5;
      intensity = powf(intensity, (1.1 - den) * 6);

      // intensity = intensity * (1.0 - density * 6) + density * 6;

      value = intensity * brightness;
      color = CHSV(hueWithOffset, saturation, value);

      blend(strip->leds, i, color);
    }
  }
};

#endif