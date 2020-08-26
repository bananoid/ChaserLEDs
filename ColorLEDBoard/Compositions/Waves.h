#ifndef COMPISITION_WAVES_H
#define COMPISITION_WAVES_H

#include "../Composition.h"

#include "../Shaders/ChaserShader.h"
#include "../Shaders/ShaderBreathing.h"

class Waves : public Composition
{
public:
  Waves()
  {
    LEDShader *shader;

    shader = new ShaderBreathing();
    shader->blendingMode = BACKGROUND;
    shader->scale = 0.2;
    shader->speed = 1;
    shader->density = -4.0;
    shader->hue = 0;
    shader->saturation = 255;
    shader->brightness = 255;
    addShader(shader);

    shader = new ShaderBreathing();
    shader->blendingMode = ADD;
    shader->scale = 0.03123;
    shader->speed = -0.90823;
    shader->density = -10.0;
    shader->hue = 20;
    shader->saturation = 100;
    shader->brightness = 255;
    addShader(shader);

    shader = new ShaderBreathing();
    shader->blendingMode = ADD;
    shader->scale = 0.03123;
    shader->speed = -1.130823;
    shader->density = -100;
    shader->hue = 30;
    shader->saturation = 0;
    shader->brightness = 255;
    addShader(shader);
  };
};
#endif