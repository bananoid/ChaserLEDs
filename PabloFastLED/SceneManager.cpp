#include "SceneManager.h"

#include "Compositions/Vein.h"

SceneManager::SceneManager(CRGB *leds)
{
  scenes = LinkedList<Scene *>();

  for (int i = 0; i < NUM_STRIPS; i++)
  {
    strips[i] = new Strip();
    strips[i]->leds = leds;
    strips[i]->numOfLed = NUM_LEDS_PER_STRIP;
    strips[i]->startInx = NUM_LEDS_PER_STRIP * i;
  }

  Composition *compVein = new Vein();

  Scene *scene;

  scene = new Scene(strips);
  scene->addComposition(compVein);
  scene->addComposition(compVein);
  scene->addComposition(compVein);
  scenes.add(scene);

  currentScene = scene;
}

void SceneManager::update(float deltaTime)
{
  currentScene->update(deltaTime);
}