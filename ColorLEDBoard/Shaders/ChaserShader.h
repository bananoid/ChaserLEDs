#ifndef CHASER_SHADER_H
#define CHASER_SHADER_H

#include "../LEDShader.h"

class ChaserShader : public LEDShader
{
public:
  ChaserShader() : LEDShader(){};
  void update(Strip *strip, float deltaTime)
  {
    LEDShader::update(strip, deltaTime);

    float intensity;
    float value;
    float x;
    CRGB color;

    float den = density * densityOffset;

    for (int i = strip->startInx; i < strip->numOfLed + strip->startInx; i++)
    {
      x = this->position + i * scale * scaleOffset;

      intensity = GFXUtils::chaserNoise(x, den);

      value = intensity * brightness;
      color = CHSV(hueWithOffset, saturation, value);

      blend(strip->leds, i, color);
    }
  }
};

#endif