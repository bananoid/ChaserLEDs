#ifndef COMPOSITION_H
#define COMPOSITION_H

#include "config.h"

#include <Arduino.h>
#include <FastLED.h>

#include "Strip.h"
#include "LEDShader.h"

class Composition
{
private:
public:
  LEDShader *shaders[NUM_SHADER_PER_COMPISITION];
  Composition();
  virtual void update(Strip *strip, float deltaTime);
};

#endif
