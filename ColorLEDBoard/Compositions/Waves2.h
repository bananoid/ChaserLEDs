#ifndef COMPISITION_WAVES_2_H
#define COMPISITION_WAVES_2_H

#include "../Composition.h"

#include "../Shaders/ChaserShader.h"
#include "../Shaders/ShaderFM.h"

class Waves2 : public Composition
{
public:
  Waves2()
  {
    LEDShader *shader;

    shader = new ShaderFM();
    shader->blendingMode = BACKGROUND;
    shader->scale = 0.02;
    shader->speed = 0.01;
    shader->density = -1.0;
    shader->hue = 0;
    shader->saturation = 255;
    shader->brightness = 255;
    addShader(shader);

    shader = new ShaderFM();
    shader->blendingMode = ADD;
    shader->scale = 0.12234;
    shader->speed = -0.01123;
    shader->density = -1.0;
    shader->hue = 30;
    shader->saturation = 255;
    shader->brightness = 255;
    addShader(shader);

    shader = new ShaderFM();
    shader->blendingMode = ADD;
    shader->scale = 0.8234;
    shader->speed = -0.013423;
    shader->density = -2.0;
    shader->hue = 60;
    shader->saturation = 255;
    shader->brightness = 255;
    addShader(shader);
  };
};
#endif