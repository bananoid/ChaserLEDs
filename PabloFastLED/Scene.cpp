#include "Scene.h"

#include <Arduino.h>
#include "GFXUtils.h"

Scene::Scene(Strip **strips)
{
  animationSteps = 2;
  compositions = LinkedList<Composition *>();
  this->strips = strips;
}

void Scene::addComposition(Composition *composition)
{
  compositions.add(composition);
}

void Scene::update(float deltaTime)
{
  int compInx;
  Composition *comp;

  for (int i = 0; i < NUM_STRIPS; i++)
  {
    hueOffset += deltaTime * 0.01;

    compInx = stripsToComp[i] % compositions.size();
    comp = compositions.get(compInx);
    comp->hueOffset = hueOffset;
    comp->update(strips[i], deltaTime);
  }
}

void Scene::nextStep()
{
  if (stepCount % (32 * 32) == 0)
  {
    randomize();
  }

  if (stepCount % (32 * 1) == 0)
  {
    shiftFW();
    mirror();
  }

  stepCount++;
}

// speed = R[0-1]; animationSteps = N[ ..., 32, 16, 8, 4, 2, 1]
void Scene::setAnimationSpeed(float speed)
{
  int expVal = (1 - speed) * 8; // max division is 8 = 2^8 = 256
  animationSteps = powf(2, expVal);
  animationSteps = max(animationSteps, 1);
}

void Scene::randomize()
{
  for (int i = 0; i < NUM_STRIPS; i++)
  {
    stripsToComp[i] = random(compositions.size());
    // stripsToComp[i] = i % compositions.size();
  }
}

void Scene::shiftFW()
{
  int temp = stripsToComp[NUM_STRIPS - 1];
  for (int i = NUM_STRIPS - 1; i >= 0; i--)
  {
    stripsToComp[i + 1] = stripsToComp[i];
  }
  stripsToComp[0] = temp;
}

void Scene::shiftBW()
{
  int temp = stripsToComp[0];
  for (int i = 0; i < NUM_STRIPS - 1; i++)
  {
    stripsToComp[i] = stripsToComp[i + 1];
  }
  stripsToComp[NUM_STRIPS - 1] = temp;
}

void Scene::mirror()
{
  // TODO: do it
}