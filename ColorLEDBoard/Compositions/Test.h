#ifndef COMPISITION_TEST_H
#define COMPISITION_TEST_H

#include "../Composition.h"

#include "../Shaders/ChaserShader.h"
#include "../Shaders/ShaderBreathing.h"
#include "../Shaders/ShaderFM.h"
#include "../Shaders/ShaderSawFM.h"

class Test : public Composition
{
public:
  Test()
  {
    LEDShader *shader;

    shader = new ShaderSawFM();
    shader->blendingMode = BACKGROUND;
    shader->scale = 1.0;
    shader->speed = 1.0;
    shader->density = 0.0;
    shader->hue = 180;
    shader->saturation = 255;
    shader->brightness = 255;
    addShader(shader);

    shader = new ShaderFM();
    shader->blendingMode = ADD;
    shader->scale = 0.433;
    shader->speed = -0.234;
    shader->density = 0;
    shader->hue = 0;
    shader->saturation = 255;
    shader->brightness = 255;
    addShader(shader);
  };
};
#endif