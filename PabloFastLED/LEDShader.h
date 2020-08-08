#include <Arduino.h>
#include <FastLED.h>

#ifndef LEDSHADER_H
#define LEDSHADER_H

#define BLEND_NORMAL 1
#define BLEND_ADD 2
#define BLEND_MULTIPLY 3

class LEDShader
{
private:
public:
  float time = 0;
  int blendingMode = BLEND_NORMAL;
  long numPixels;

  LEDShader(long numPixels);
  virtual void render(CRGB *leds);
};

#endif
