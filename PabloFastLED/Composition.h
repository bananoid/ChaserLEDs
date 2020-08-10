#ifndef COMPOSITION_H
#define COMPOSITION_H

#include <Arduino.h>
#include <FastLED.h>

#include "LEDShader.h"

#include "Strip.h"
#include "Layer.h"

#define MAX_LAYER_COUNT 2

class Composition
{
private:
public:
  Layer *layers[MAX_LAYER_COUNT];
  Composition();
  virtual void update(float deltaTime);
  virtual void render(Strip *strip);
};

#endif
