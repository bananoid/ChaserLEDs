#include "ChaserShader.h"
#include "mathUtils.h"

void ChaserShader::render(Strip *strip, BlendingMode blendingMode)
{
  float intensity;
  float value;
  float x;
  CRGB color;
  for (int i = strip->startInx; i < strip->numOfLed + strip->startInx; i++)
  {

    x = this->position + i;

    intensity = chaserNoise(x, density);

    value = intensity * brightness;
    color = CHSV(hue, saturation, value);

    switch (blendingMode)
    {
    case BACKGROUND:
      strip->leds[i] = color;
      break;
    case NORMAL:
      strip->leds[i] = color; //TODO: alpha blending
      break;
    case ADD:
      strip->leds[i].r += color.r;
      strip->leds[i].g += color.g;
      strip->leds[i].b += color.b;
      break;
    case MULTIPLY:
      strip->leds[i].r *= color.r;
      strip->leds[i].g *= color.g;
      strip->leds[i].b *= color.b;
      break;

    default:
      break;
    }
  }
}