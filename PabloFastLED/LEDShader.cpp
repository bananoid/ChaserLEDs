#include "LEDShader.h"

LEDShader::LEDShader(long numPixels)
{
  this->numPixels = numPixels;
}

void LEDShader::update(float deltaTime)
{
  position += deltaTime * speed;
}

void LEDShader::render(CRGB *leds, int startInx)
{
  // float hue;
  // for (int i = 0; i < this->numPixels; i++)
  // {
  //   hue = (float)i / (float)this->numPixels + position;
  //   leds[i] = CHSV(hue * 255, 255, 255);
  // }
}