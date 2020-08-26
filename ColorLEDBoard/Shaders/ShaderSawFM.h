#ifndef SHADER_SAW_FM_H
#define SHADER_SAW_FM_H

#include "../LEDShader.h"
#include "../GFXUtils.h"

class ShaderSawFM : public LEDShader
{
public:
  ShaderSawFM() : LEDShader(){};
  void update(Strip *strip, float deltaTime)
  {
    LEDShader::update(strip, deltaTime);

    float intensity;
    float value;
    float h;
    float x;
    CRGB color;

    float oscA, oscB;
    float den = density + densityOffset;

    for (int i = strip->startInx; i < strip->numOfLed + strip->startInx; i++)
    {

      x = (this->position + i) * (scale * scaleOffset) / 30;

      oscA = sinf(fmod(-x * 0.05439234 + 1.04156, TWO_PI));
      oscB = sinf(fmod(-x * 0.002454332 + 1.34156, TWO_PI));

      intensity = GFXUtils::fract(abs(oscA * oscB * 30));
      intensity = powf(intensity, (1.1 - den) * 4);
      value = intensity * brightness;
      intensity = powf(intensity, (1.1 - den) * 2);
      h = intensity * 90 + hueWithOffset + sinf(oscB * x * .8) * 10;
      h -= 40;
      intensity = powf(intensity, (1.1 - den) * 2);
      // intensity = intensity * (1.0 - den * 6) + den * 6;

      color = CHSV(fmod(h, 255), saturation * (1 - intensity * 0.5), value);

      blend(strip->leds, i, color);
    }
  }
};

#endif