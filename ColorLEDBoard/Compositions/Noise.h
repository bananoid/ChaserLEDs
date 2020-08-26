#ifndef COMPISITION_NOISE_H
#define COMPISITION_NOISE_H

#include "../Composition.h"

#include "../Shaders/ChaserShader.h"
#include "../Shaders/ShaderBreathing.h"
#include "../Shaders/ShaderNoise.h"

class Noise : public Composition
{
public:
  Noise()
  {
    LEDShader *shader;

    shader = new ShaderNoise();
    shader->blendingMode = BACKGROUND;
    shader->scale = 1.123874;
    shader->speed = 0.123;
    shader->density = 0.9;
    shader->hue = 0;
    shader->saturation = 0;
    shader->brightness = 255;
    addShader(shader);

    shader = new ShaderNoise();
    shader->blendingMode = NORMAL;
    shader->scale = 0.121234;
    shader->speed = 1.23;
    shader->density = 0.9;
    shader->hue = 0;
    shader->saturation = 255;
    shader->brightness = 255;
    addShader(shader);

    shader = new ShaderNoise();
    shader->blendingMode = NORMAL;
    shader->scale = 0.2234;
    shader->speed = 1.4234;
    shader->density = 0.9;
    shader->hue = 140;
    shader->saturation = 255;
    shader->brightness = 255;
    addShader(shader);
  };
};
#endif