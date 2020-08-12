#include "SceneManager.h"

#include "Compositions/Vein.h"
#include "Compositions/Rain.h"

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
  Composition *compRain = new Rain();

  Scene *scene;

  scene = new Scene(strips);
  scene->addComposition(compRain);
  scene->addComposition(compVein);
  scenes.add(scene);

  currentScene = scene;
}

void SceneManager::update(float deltaTime)
{
  currentScene->update(deltaTime);
}