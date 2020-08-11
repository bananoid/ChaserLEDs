#include "Composition.h"

#include "ChaserShader.h"
#include "ShaderBreathing.h"

Composition::Composition()
{

  shaders[0] = new ShaderBreathing();
  shaders[0]->blendingMode = BACKGROUND;
  shaders[0]->brightness = 255;
  shaders[0]->scale = 0.2;
  shaders[0]->speed = -2.3;
  shaders[0]->hue = 20;
  shaders[0]->density = 0.0;

  shaders[1] = new ChaserShader();
  shaders[1]->blendingMode = NORMAL;
  shaders[1]->brightness = 255;
  shaders[1]->scale = 0.7;
  shaders[1]->speed = 2.1;
  shaders[1]->hue = 0;
  shaders[1]->density = 0.3;

  shaders[2] = new ShaderBreathing();
  shaders[2]->blendingMode = NORMAL;
  shaders[2]->brightness = 255;
  shaders[2]->scale = 0.003;
  shaders[2]->speed = -30;
  shaders[2]->hue = 150;
  shaders[2]->density = 0.0;
}

void Composition::update(float deltaTime)
{
  for (int i = 0; i < MAX_SHADERS_COUNT; i++)
  {
    shaders[i]->update(deltaTime);
  }
}

void Composition::render(Strip *strip)
{
  for (int i = 0; i < MAX_SHADERS_COUNT; i++)
  {
    shaders[i]->render(strip);
  }
}