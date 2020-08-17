#ifndef COMPISITION_RAIN_H
#define COMPISITION_RAIN_H

#include "../Composition.h"

#include "../Shaders/ChaserShader.h"
#include "../Shaders/ShaderBreathing.h"

class Rain : public Composition
{
public:
  Rain()
  {
    LEDShader *shader;

    // shader = new ShaderBreathing();
    // shader->blendingMode = BACKGROUND;
    // shader->scale = 0.2;
    // shader->speed = -2.3;
    // shader->density = 0.0;
    // shader->hue = 20;
    // shader->saturation = 255;
    // shader->brightness = 255;
    // addShader(shader);

    shader = new ChaserShader();
    shader->blendingMode = BACKGROUND;
    shader->scale = 1.7;
    shader->speed = 10.1;
    shader->density = 0.03;
    shader->hue = 140;
    shader->saturation = 0;
    shader->brightness = 255;
    addShader(shader);

    shader = new ChaserShader();
    shader->blendingMode = NORMAL;
    shader->scale = 0.001;
    shader->speed = 1.;
    shader->density = 0.05;
    shader->hue = 150;
    shader->saturation = 0;
    shader->brightness = 255;
    addShader(shader);

    shader = new ChaserShader();
    shader->blendingMode = NORMAL;
    shader->scale = 0.1;
    shader->speed = 0.5;
    shader->density = 0.3;
    shader->hue = 140;
    shader->saturation = 0;
    shader->brightness = 200;
    addShader(shader);
  };
};
#endif