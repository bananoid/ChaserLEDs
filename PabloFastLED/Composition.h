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
  LinkedList<LEDShader *> *shaders;
  Composition();
  float hueOffset = 0;
  virtual void addShader(LEDShader *shader);
  virtual void update(Strip *strip, float deltaTime);
};

#endif
