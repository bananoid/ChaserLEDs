#include "LEDShader.h"

LEDShader::LEDShader(long numPixels)
{
  this->numPixels = numPixels;
}

void LEDShader::update(float deltaTime)
{
  time += deltaTime * speed;
}

void LEDShader::render(CRGB *leds)
{
  float hue;
  for (int i = 0; i < this->numPixels; i++)
  {
    hue = (float)i / (float)this->numPixels + time * 1;
    leds[i] = CHSV(hue * 255, 255, 255);
  }
}