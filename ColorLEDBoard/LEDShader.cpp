#include "LEDShader.h"
#include <Arduino.h>

LEDShader::LEDShader()
{
  position = random(100000) / 1000.0;
}

void LEDShader::update(Strip *strip, float deltaTime)
{
  position += deltaTime * speed * speedOffset;

  hueWithOffset = hue + hueOffset;
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
    leds[ledInx].r = min((float)leds[ledInx].r + (float)color.r, 255);
    leds[ledInx].g = min((float)leds[ledInx].g + (float)color.g, 255);
    leds[ledInx].b = min((float)leds[ledInx].b + (float)color.b, 255);
    break;
  case MULTIPLY:
    leds[ledInx].r *= color.r / 255.0;
    leds[ledInx].g *= color.g / 255.0;
    leds[ledInx].b *= color.b / 255.0;
    break;

  default:
    break;
  }
}
