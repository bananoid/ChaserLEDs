#include "ChaserShader.h"
#include "mathUtils.h"

void ChaserShader::render(CRGB *leds)
{
  float dot;

  //// Tunderbolt
  // for (int i = 0; i < this->numPixels; i++)
  // {
  //   dot = rnd(((int)(i + time * this->numPixels)) / this->numPixels);
  //   leds[i] = CHSV(0, 0, dot * 255);
  // }

  for (int i = 0; i < this->numPixels; i++)
  {
    float size = 10;
    float speed = 1.;
    float density = 0.1;

    dot = rnd(((int)(i + time * speed * size)) / size) > density ? 0 : 1;
    leds[i] = CHSV(0, 255, dot * 255);
  }
}