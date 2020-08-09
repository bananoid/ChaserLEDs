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
  float speed = 1;
  float density = 1;
  float scale = 1;
  int blendingMode = BLEND_NORMAL;
  long numPixels;

  LEDShader(long numPixels);
  virtual void update(float deltaTime);
  virtual void render(CRGB *leds);
};

#endif
