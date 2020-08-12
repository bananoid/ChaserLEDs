#ifndef COMPOSITION_H
#define COMPOSITION_H

#include "config.h"

#include <Arduino.h>
#include <FastLED.h>
#include <LinkedList.h>

#include "Strip.h"
#include "LEDShader.h"

class Composition
{
private:
public:
  // LEDShader *shaders[NUM_SHADER_PER_COMPISITION];
  LinkedList<LEDShader *> *shaders;
  Composition();
  virtual void addShader(LEDShader *shader);
  virtual void update(Strip *strip, float deltaTime);
};

#endif
