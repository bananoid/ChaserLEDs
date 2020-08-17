#ifndef COMPISITION_SIMPLE_COLOR_H
#define COMPISITION_SIMPLE_COLOR_H

#include "../Composition.h"

#include "../ChaserShader.h"
#include "../ShaderBreathing.h"

class SimpleColor : public Composition
{
public:
  SimpleColor(CHSV color)
  {
    LEDShader *shader;

    shader = new ShaderBreathing();
    shader->blendingMode = BACKGROUND;
    shader->scale = 0.2;
    shader->speed = -5.0;
    shader->density = .3;
    shader->hue = color.h;
    shader->saturation = color.s;
    shader->brightness = color.v;
    addShader(shader);

    // shader = new ShaderBreathing();
    // shader->blendingMode = BACKGROUND;
    // shader->scale = 0.2;
    // shader->speed = -5.0;
    // shader->density = -10.4;
    // shader->hue = color.h;
    // shader->saturation = color.s;
    // shader->brightness = color.v;
    // addShader(shader);

    // shader = new ShaderBreathing();
    // shader->blendingMode = ADD;
    // shader->scale = 0.02;
    // shader->speed = 8.45;
    // shader->density = -10.4;
    // shader->hue = color.h;
    // shader->saturation = color.s;
    // shader->brightness = color.v;
    // addShader(shader);
  };
};
#endif