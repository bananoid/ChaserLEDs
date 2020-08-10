#include <Arduino.h>
#include <FastLED.h>

#include "LEDShader.h"
#include "ChaserShader.h"
#include "Strip.h"

#ifndef COMPOSITION_H
#define COMPOSITION_H

#define SHADER_COUNT 3
#define MAX_LAYER_COUNT 2

enum BlendingMode
{
  NORMAL,
  ADD,
  MULTIPLY
};

class Layer
{
public:
  LEDShader *shader;
  BlendingMode blendingMode = NORMAL;
  // virtual void update(float deltaTime);
  // virtual void render();
};

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
