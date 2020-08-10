#include "LEDShader.h"

#ifndef SHADER_BREATHING_H
#define SHADER_BREATHING_H

class ShaderBreathing : public LEDShader
{
public:
  ShaderBreathing() : LEDShader(){};
  void render(Strip *strip, BlendingMode blendingMode) override;
};

#endif