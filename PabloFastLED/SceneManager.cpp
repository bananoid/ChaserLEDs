#include "SceneManager.h"

#include "Compositions/Vein.h"
#include "Compositions/Rain.h"

SceneManager::SceneManager(CRGB *leds)
{
  // Initialize Strips

  for (int i = 0; i < NUM_STRIPS; i++)
  {
    strips[i] = new Strip();
    strips[i]->leds = leds;
    strips[i]->numOfLed = NUM_LEDS_PER_STRIP;
    strips[i]->startInx = NUM_LEDS_PER_STRIP * i;
  }

  // Initialize Compositon

  allCompositions = LinkedList<Composition *>();
  allCompositions.add(new Vein());
  allCompositions.add(new Rain());

  // Build Scenes

  Composition *compVein = new Vein();
  Composition *compRain = new Rain();

  scenes = LinkedList<Scene *>();
  Scene *scene;

  scene = new Scene(strips);
  scene->addComposition(compRain);
  scene->addComposition(compVein);

  scene->nextStep();
  scenes.add(scene);

  currentScene = scene;
}

void SceneManager::update(float deltaTime)
{
  currentScene->update(deltaTime);
}

void SceneManager::clockTick(Clock *clock)
{
  // if (MainClock.ticksCount % 32 == 0)
  // {
  //   currentScene = createRandomScene();
  // }

  currentScene->nextStep();
}

static Scene *SceneManager::createRandomScene()
{
}
