#ifndef COMPISITION_VEIN_H
#define COMPISITION_VEIN_H

#include "../Composition.h"

#include "../Shaders/ChaserShader.h"
#include "../Shaders/ShaderBreathing.h"

class Vein : public Composition
{
public:
  Vein()
  {
    LEDShader *shader;

    shader = new ShaderBreathing();
    shader->blendingMode = BACKGROUND;
    shader->scale = 0.2;
    shader->speed = -2.3;
    shader->density = 0.0;
    shader->hue = 20;
    shader->saturation = 255;
    shader->brightness = 255;
    addShader(shader);

    shader = new ChaserShader();
    shader->blendingMode = NORMAL;
    shader->scale = 0.7;
    shader->speed = 2.1;
    shader->density = 0.3;
    shader->hue = 0;
    shader->saturation = 255;
    shader->brightness = 255;
    addShader(shader);

    shader = new ShaderBreathing();
    shader->blendingMode = NORMAL;
    shader->scale = 0.003;
    shader->speed = -30;
    shader->density = 0.0;
    shader->hue = 150;
    shader->saturation = 255;
    shader->brightness = 255;
    addShader(shader);
  };
};
#endif