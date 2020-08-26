#ifndef COMPOSITION_H
#define COMPOSITION_H

#include "config.h"

#include <Arduino.h>
#include <FastLED.h>
#include "LinkedList.h"

#include "Strip.h"
#include "LEDShader.h"

class Composition
{
private:
public:
  LinkedList<LEDShader *> *shaders;
  Composition();
  float intencityMult = 1;
  float speedOffset = 1;
  float hueOffset = 0;
  float scaleOffset = 1;
  float densityOffset = 1;
  virtual void addShader(LEDShader *shader);
  virtual void update(Strip *strip, float deltaTime);
};

#endif
