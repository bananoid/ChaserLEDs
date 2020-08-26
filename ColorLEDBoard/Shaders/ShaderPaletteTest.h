#ifndef SHADER_PALETTE_TEST_H
#define SHADER_PALETTE_TEST_H

#include "../LEDShader.h"
#include "../GFXUtils.h"

class ShaderPaletteTest : public LEDShader
{
public:
  ShaderPaletteTest() : LEDShader(){};
  void update(Strip *strip, float deltaTime)
  {
    LEDShader::update(strip, deltaTime);

    CRGB color;
    float x;

    for (int i = strip->startInx; i < strip->numOfLed + strip->startInx; i++)
    {
      x = (this->position + i) * scale * scaleOffset;

      // color = CHSV(hueWithOffset, saturation, 255);
      color = GFXUtilsSingleton.getPaletteColor(x);

      blend(strip->leds, i, color);
    }
  }
};

#endif