#include "Scene.h"

#include <Arduino.h>
#include "GFXUtils.h"

Scene::Scene(Strip **strips)
{
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
  for (int i = 0; i < NUM_STRIPS; i++)
  {
    compInx = stripsToComp[i];
    compositions.get(compInx)->update(strips[i], deltaTime);
  }
}

void Scene::nextStep()
{
  for (int i = 0; i < NUM_STRIPS; i++)
  {
    stripsToComp[i] = random(compositions.size());
  }
  stepCount++;
}