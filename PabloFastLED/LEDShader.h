#ifndef LEDSHADER_H
#define LEDSHADER_H

#include <Arduino.h>
#include <FastLED.h>
#include "Strip.h"
#include "GFXUtils.h"

enum BlendingMode
{
  BACKGROUND,
  NORMAL,
  ADD,
  MULTIPLY
};

class LEDShader
{
private:
public:
  float position = 0;
  float speed = 1;

  float density = 1;
  float scale = 1;

  float brightness = 255;
  float saturation = 255;
  float hue = 255;

  BlendingMode blendingMode = NORMAL;

  LEDShader();
  virtual void update(float deltaTime);
  virtual void render(Strip *strip);
  virtual void blend(CRGB *leds, int ledInx, CRGB color);
};

#endif
