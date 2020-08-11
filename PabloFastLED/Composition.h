#ifndef COMPOSITION_H
#define COMPOSITION_H

#include <Arduino.h>
#include <FastLED.h>

#include "Strip.h"
#include "LEDShader.h"

#define MAX_SHADERS_COUNT 3

class Composition
{
private:
public:
  LEDShader *shaders[MAX_SHADERS_COUNT];
  Composition();
  virtual void update(float deltaTime);
  virtual void render(Strip *strip);
};

#endif
