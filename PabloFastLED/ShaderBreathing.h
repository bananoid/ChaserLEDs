#ifndef SHADER_BREATHING_H
#define SHADER_BREATHING_H

#include "LEDShader.h"

class ShaderBreathing : public LEDShader
{
public:
  ShaderBreathing() : LEDShader(){};
  void update(Strip *strip, float deltaTime) override;
};

#endif