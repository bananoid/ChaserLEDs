#ifndef COMPISITION_TEST_H
#define COMPISITION_TEST_H

#include "../Composition.h"

#include "../Shaders/ChaserShader.h"
#include "../Shaders/ShaderBreathing.h"
#include "../Shaders/ShaderFM.h"

class Test : public Composition
{
public:
  Test()
  {
    LEDShader *shader;

    shader = new ShaderFM();
    shader->blendingMode = BACKGROUND;
    shader->scale = 0.06;
    shader->speed = 10.0;
    shader->density = 1;
    shader->hue = 5;
    shader->saturation = 255;
    shader->brightness = 255;
    addShader(shader);

    shader = new ShaderFM();
    shader->blendingMode = ADD;
    shader->scale = 0.633;
    shader->speed = -1.234;
    shader->density = 1;
    shader->hue = 20;
    shader->saturation = 255;
    shader->brightness = 255;
    addShader(shader);
  };
};
#endif