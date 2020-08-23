#include "Composition.h"

Composition::Composition()
{
  shaders = new LinkedList<LEDShader *>();
}

void Composition::addShader(LEDShader *shader)
{
  shaders->add(shader);
}

void Composition::update(Strip *strip, float deltaTime)
{
  LEDShader *shader;
  for (int i = 0; i < shaders->size(); i++)
  {
    shader = shaders->get(i);
    shader->brightness = 255 * intencityMult;
    shader->speedOffset = speedOffset;
    shader->hueOffset = hueOffset;
    shader->update(strip, deltaTime);
  }
}
