#include "LEDShader.h"

#ifndef CHASER_SHADER_H
#define CHASER_SHADER_H

class ChaserShader : public LEDShader
{
public:
  ChaserShader() : LEDShader(){};
  void render(Strip *strip) override;
};

#endif