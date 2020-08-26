#ifndef COMPISITION_CHASER_01_H
#define COMPISITION_CHASER_01_H

#include "../Composition.h"

#include "../Shaders/ChaserShader.h"
#include "../Shaders/ShaderBreathing.h"
#include "../Shaders/ShaderFM.h"

class Chaser01 : public Composition
{
public:
  Chaser01()
  {
    LEDShader *shader;

    shader = new ShaderFM();
    shader->blendingMode = BACKGROUND;
    shader->scale = 0.2;
    shader->speed = 1;
    shader->density = -4.0;
    shader->hue = 0;
    shader->saturation = 0;
    shader->brightness = 255;
    addShader(shader);

    shader = new ShaderFM();
    shader->blendingMode = ADD;
    shader->scale = 0.02;
    shader->speed = -0.8;
    shader->density = -8.0;
    shader->hue = 0;
    shader->saturation = 0;
    shader->brightness = 255;
    addShader(shader);

    shader = new ShaderFM();
    shader->blendingMode = ADD;
    shader->scale = 0.007;
    shader->speed = -0.812;
    shader->density = -2.0;
    shader->hue = 0;
    shader->saturation = 255;
    shader->brightness = 255;
    addShader(shader);
  };
};
#endif