#include "SceneManager.h"

#include "Compositions/Vein.h"
#include "Compositions/Rain.h"
#include "Compositions/SimpleColor.h"

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
  allCompositions.add(new SimpleColor(CHSV(0, 255, 255)));
  allCompositions.add(new SimpleColor(CHSV(0, 0, 255)));
  allCompositions.add(new SimpleColor(CHSV(100, 255, 255)));
  allCompositions.add(new SimpleColor(CHSV(100, 100, 255)));
  allCompositions.add(new SimpleColor(CHSV(200, 255, 255)));
  allCompositions.add(new SimpleColor(CHSV(200, 100, 255)));
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
  if (MasterClock.ticksCount % (TICK_PER_BEAT * 256) == 0)
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

  //Apply initial operations
  scene->applyOperation(SOP_Sorted);
  // scene->applyOperation(SOP_Random);

  // Set Timeline Operations

  scene->addTimelineOperation(8, SOP_Random);
  scene->addTimelineOperation(4, SOP_RandomSpeed);
  scene->addTimelineOperation(2, SOP_ShiftFW);
  scene->addTimelineOperation(3, SOP_ShiftBW);

  scene->isMirrored = true;

  return scene;
}
