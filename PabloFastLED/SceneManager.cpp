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

  // Build Scenes

  Composition *compVein = new Vein();

  Composition *compRain = new Rain();

  Composition *compVein2 = new Vein();
  compVein2->shaders->get(0)->hue = 50;
  compVein2->shaders->get(1)->hue = 50;
  compVein2->shaders->get(2)->hue = 50;

  Composition *compRain2 = new Rain();
  compVein2->shaders->get(0)->hue = 90;
  compVein2->shaders->get(1)->hue = 90;
  compVein2->shaders->get(2)->hue = 90;

  Composition *compVein3 = new Vein();
  compVein2->shaders->get(0)->hue = 120;
  compVein2->shaders->get(1)->hue = 120;
  compVein2->shaders->get(2)->hue = 120;

  Composition *compVein4 = new Vein();
  compVein2->shaders->get(0)->hue = 200;
  compVein2->shaders->get(1)->hue = 200;
  compVein2->shaders->get(2)->hue = 200;

  Composition *compVein5 = new Vein();
  compVein2->shaders->get(0)->hue = 30;
  compVein2->shaders->get(1)->hue = 30;
  compVein2->shaders->get(2)->hue = 20;

  scenes = LinkedList<Scene *>();
  Scene *scene;

  scene = new Scene(strips);
  scene->addComposition(compRain);
  scene->addComposition(compVein);
  scene->addComposition(compVein2);
  scene->addComposition(compRain2);
  scene->addComposition(compVein3);
  scene->addComposition(compVein4);
  scene->addComposition(compVein5);

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
  currentScene->nextStep();
}

