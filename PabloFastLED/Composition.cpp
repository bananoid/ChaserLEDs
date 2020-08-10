#include "Composition.h"

Composition::Composition()
{
  layers[0] = new Layer();
  layers[0]->blendingMode = BACKGROUND;
  layers[0]->shader = new ShaderBreathing();
  layers[1]->shader->brightness = 255;
  layers[0]->shader->scale = 1;
  layers[0]->shader->hue = 10;
  layers[0]->shader->density = 0.1;

  layers[1] = new Layer();
  layers[1]->blendingMode = ADD;
  layers[1]->shader = new ChaserShader();
  layers[1]->shader->brightness = 255;
  layers[1]->shader->speed = -1.9;
  layers[1]->shader->hue = 150;
  layers[1]->shader->density = 0.2;
}

void Composition::update(float deltaTime)
{
  for (int i = 0; i < MAX_LAYER_COUNT; i++)
  {
    layers[i]->shader->update(deltaTime);
  }
}

void Composition::render(Strip *strip)
{
  for (int i = 0; i < MAX_LAYER_COUNT; i++)
  {
    layers[i]->shader->render(strip, layers[i]->blendingMode);
  }
}