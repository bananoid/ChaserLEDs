#include "LEDShader.h"

#ifndef LAYER_H
#define LAYER_H

class Layer
{
public:
  LEDShader *shader;
  BlendingMode blendingMode = NORMAL;
  // virtual void update(float deltaTime);
  // virtual void render();
};

#endif