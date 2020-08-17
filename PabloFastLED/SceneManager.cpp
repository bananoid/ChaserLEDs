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

  currentScene = createRandomScene();
}

void SceneManager::update(float deltaTime)
{
  if (currentScene == NULL)
  {
    return;
  }
  currentScene->update(deltaTime);
}

void SceneManager::clockTick(Clock *clock)
{
  if (MasterClock.ticksCount % TICK_PER_BEAT * 4 == 0)
  {
    if (currentScene != NULL)
    {
      delete currentScene;
    }

    currentScene = createRandomScene();
  }

  if (currentScene == NULL)
  {
    return;
  }

  currentScene->nextStep();
}

Scene *SceneManager::createRandomScene()
{
  Scene *scene = new Scene(strips);

  //Add Compositions
  scene->addComposition(allCompositions.get(0));
  scene->addComposition(allCompositions.get(1));
  scene->addComposition(allCompositions.get(1));
  scene->addComposition(allCompositions.get(1));
  scene->addComposition(allCompositions.get(1));
  scene->addComposition(allCompositions.get(1));
  scene->addComposition(allCompositions.get(1));
  scene->addComposition(allCompositions.get(1));

  //Apply initial operations
  // scene->applyOperation(SOP_Sorted);
  scene->applyOperation(SOP_Random);

  // Set Timeline Operations
  scene->addTimelineOperation(3, SOP_RandomSpeed);
  scene->addTimelineOperation(4, SOP_ShiftBW);

  return scene;
}
