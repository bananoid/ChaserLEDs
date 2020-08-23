#include "SceneManager.h"

#include "Compositions/Vein.h"
#include "Compositions/Rain.h"
#include "Compositions/SimpleColor.h"
#include "Compositions/Test.h"

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

  allCompositions.add(new Test());

  allCompositions.add(new SimpleColor(CHSV(0, 0, 255)));
  allCompositions.add(new SimpleColor(CHSV(0, 255, 255)));
  allCompositions.add(new Vein());
  allCompositions.add(new Rain());

  currentScene = createRandomScene();
}

void SceneManager::update(float deltaTime)
{
  if (autoRotateSceneMode)
  {
    doAutoRotateWithTime();
  }

  if (currentScene == NULL)
  {
    return;
  }

  // currentScene->intencityMult = MasterAudioInput.mid * 2 + 0.1;
  // currentScene->speedOffset = 0.5 + MasterAudioInput.low * 2;

  currentScene->update(deltaTime);
}

void SceneManager::clockTick(Clock *clock)
{
  if (clockFromAudio)
  {
    return;
  }
  // if (MasterClock.ticksCount % (TICK_PER_BEAT * 256) == 0)
  // {
  //   if (currentScene != NULL)
  //   {
  //     delete currentScene;
  //   }

  //   currentScene = createRandomScene();
  // }

  if (currentScene == NULL)
  {
    return;
  }

  currentScene->nextStep();
}

void SceneManager::audioClockTick()
{
  if (currentScene == NULL)
  {
    return;
  }

  currentScene->nextStep();
}

void SceneManager::doAutoRotateWithTime()
{
  long minute = millis() / 60000;

  if (currentMinute != minute)
  {
    currentMinute = minute;

    if (minute % 1 == 0)
    {
    }

    if (currentSceneIdx % 2 == 0)
    {
      digitalWrite(2, true);
    }
    else
    {
      digitalWrite(2, false);
    }
  }
}

void SceneManager::setCurrentSceneInx(int inx)
{
  currentSceneIdx = inx;
  currentSceneIdx = currentSceneIdx % SCENE_FUNCTION_COUNT;

  switch (inx)
  {
  case 0:
    currentScene = createRandomScene();
    break;

  default:
    break;
  }
}

void SceneManager::setNextScene()
{
  currentSceneIdx++;
  setCurrentSceneInx(currentSceneIdx);
}

Scene *SceneManager::createRandomScene()
{
  Scene *scene = new Scene(strips);

  //Add Compositions
  scene->addComposition(allCompositions.get(0));
  scene->addComposition(allCompositions.get(0));
  scene->addComposition(allCompositions.get(2));
  scene->addComposition(allCompositions.get(0));
  scene->addComposition(allCompositions.get(1));
  scene->addComposition(allCompositions.get(0));
  scene->addComposition(allCompositions.get(0));
  scene->addComposition(allCompositions.get(3));
  scene->addComposition(allCompositions.get(4));
  scene->addComposition(allCompositions.get(1));
  scene->addComposition(allCompositions.get(0));
  scene->addComposition(allCompositions.get(0));
  scene->addComposition(allCompositions.get(0));
  scene->addComposition(allCompositions.get(0));
  scene->addComposition(allCompositions.get(0));
  // scene->addComposition(allCompositions.get(1));
  // scene->addComposition(allCompositions.get(1));
  // scene->addComposition(allCompositions.get(1));

  //Apply initial operations
  scene->applyOperation(SOP_Sorted);
  // scene->applyOperation(SOP_Random);

  // Set Timeline Operations

  scene->addTimelineOperation(9, SOP_Random);
  scene->addTimelineOperation(5, SOP_RandomSpeed);
  scene->addTimelineOperation(4, SOP_ShiftFW);
  // scene->addTimelineOperation(3, SOP_ShiftBW);

  scene->isMirrored = true;

  return scene;
}

// Scene *SceneManager::createScene1()
// {
// }

// Scene *SceneManager::createScene2()
// {
// }