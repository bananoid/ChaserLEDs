#include "LEDShader.h"

LEDShader::LEDShader()
{
}

void LEDShader::update(Strip *strip, float deltaTime)
{
  position += deltaTime * speed;
}

void LEDShader::blend(CRGB *leds, int ledInx, CRGB color)
{
  switch (blendingMode)
  {
  case BACKGROUND:
    leds[ledInx] = color;
    break;
  case NORMAL:
    leds[ledInx] = GFXUtils::alphaBlend(leds[ledInx], color);
    break;
  case ADD:
    leds[ledInx].r += color.r;
    leds[ledInx].g += color.g;
    leds[ledInx].b += color.b;
    break;
  case MULTIPLY:
    leds[ledInx].r *= color.r;
    leds[ledInx].g *= color.g;
    leds[ledInx].b *= color.b;
    break;

  default:
    break;
  }
}