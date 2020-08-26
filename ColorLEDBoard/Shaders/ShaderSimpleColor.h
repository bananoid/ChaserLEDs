#ifndef SHADER_SIMPLE_COLOR_H
#define SHADER_SIMPLE_COLOR_H

#include "../LEDShader.h"

class ShaderSimpleColor : public LEDShader
{
public:
  ShaderSimpleColor() : LEDShader(){};
  void update(Strip *strip, float deltaTime)
  {
    LEDShader::update(strip, deltaTime);

    CRGB color;

    for (int i = strip->startInx; i < strip->numOfLed + strip->startInx; i++)
    {

      color = CHSV(hueWithOffset, saturation, 255);
      
      blend(strip->leds, i, color);
    }
  }
};

#endif