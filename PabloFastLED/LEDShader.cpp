#include "LEDShader.h"

LEDShader::LEDShader()
{
}

void LEDShader::update(float deltaTime)
{
  position += deltaTime * speed;
}

void LEDShader::render(Strip *strip, BlendingMode blendingMode)
{
  // float hue;
  // for (int i = 0; i < this->numPixels; i++)
  // {
  //   hue = (float)i / (float)this->numPixels + position;
  //   leds[i] = CHSV(hue * 255, 255, 255);
  // }
}

void LEDShader::blend(CRGB *leds, int ledInx, CRGB color, BlendingMode blendingMode)
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