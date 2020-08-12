#include "SceneManager.h"

#include "Compositions/Vein.h"

SceneManager::SceneManager(CRGB *leds)
{
  for (int i = 0; i < NUM_STRIPS; i++)
  {
    strips[i] = new Strip();
    strips[i]->leds = leds;
    strips[i]->numOfLed = NUM_LEDS_PER_STRIP;
    strips[i]->startInx = NUM_LEDS_PER_STRIP * i;
  }

  compositions[0] = new Vein();
}

void SceneManager::update(float deltaTime)
{
  for (int stripInx = 0; stripInx < NUM_STRIPS; stripInx++)
  {
    compositions[0]->update(strips[stripInx], deltaTime);
  }
}