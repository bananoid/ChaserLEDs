#include <Arduino.h>
#include <FastLED.h>
#include "Strip.h"

#ifndef LEDSHADER_H
#define LEDSHADER_H

#define BLEND_NORMAL 1
#define BLEND_ADD 2
#define BLEND_MULTIPLY 3

class LEDShader
{
private:
public:
  float position = 0;
  float speed = 1;

  float density = 1;
  // float scale = 1;

  float brightness = 255;
  float saturation = 255;
  float hue = 255;

  int blendingMode = BLEND_NORMAL;

  LEDShader();
  virtual void update(float deltaTime);
  virtual void render(Strip *strip);
};

#endif
