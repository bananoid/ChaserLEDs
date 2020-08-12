#include "Scene.h"

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
  for (int stripInx = 0; stripInx < NUM_STRIPS; stripInx++)
  {
    compositions.get(0)->update(strips[stripInx], deltaTime);
  }
}
