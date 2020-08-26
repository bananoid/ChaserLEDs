#include "SceneManager.h"

#include "Compositions/Vein.h"
#include "Compositions/Rain.h"
#include "Compositions/SimpleColor.h"
#include "Compositions/Test.h"
#include "Compositions/Waves.h"
#include "Compositions/Noise.h"
#include "Compositions/Chaser01.h"
#include "Compositions/Waves2.h"
#include "GFXUtils.h"

SceneManager::SceneManager(CRGB *leds)
{

  pinMode(INTERNAL_CLOCK_SWITCH_PIN, INPUT_PULLUP);
  pinMode(SCENE_AUTO_BUTTON_PIN, INPUT_PULLUP);
  pinMode(SCENE_SELECT_1_BUTTON_PIN, INPUT_PULLUP);
  pinMode(SCENE_SELECT_2_BUTTON_PIN, INPUT_PULLUP);

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

  // allCompositions.add(new Test());                         // 0
  allCompositions.add(new SimpleColor(CHSV(0, 0, 255)));   // 1
  allCompositions.add(new SimpleColor(CHSV(0, 255, 255))); // 2
  allCompositions.add(new Vein());                         // 3
  allCompositions.add(new Rain());                         // 4
  allCompositions.add(new Waves());                        // 5
  allCompositions.add(new Noise());                        // 6
  allCompositions.add(new Chaser01());                     // 7
  allCompositions.add(new Waves2());                       // 8

  for (int i = 0; i < SCENE_FUNCTION_COUNT; i++)
  {
    beatScenes.add(createTechnoScene(false));
    breakDownScenes.add(createTechnoScene(true));
  }

  fireSceneBeat = createFireScene(false);
  fireSceneBreakDown = createFireScene(true);

  ambientSceneBeat = createAmbientScene(false);
  ambientSceneBreakDown = createAmbientScene(true);

  currentScene = beatScenes.get(0);
}

void SceneManager::update(float deltaTime)
{
  checkButtonsState();

  // if (selectionMode == Auto)
  // {
  //   doAutoRotateWithTime();
  // }

  if (currentScene == NULL)
  {
    return;
  }

  if (MasterAudioInput.onBreakDown)
  {
    currentScene->speedOffset = MasterAudioInput.breakDownFadeValue * 0.4 + 0.4;
    // currentScene->speedOffset += GFXUtils::clamp(MasterAudioInput.midFilterVal * 5 + 0.4, 0, 1);

    currentScene->hueOffset = (1 - MasterAudioInput.breakDownFadeValue) * 20;

    currentScene->scaleOffset = MasterAudioInput.breakDownFadeValue * 1.2 + 0.3;

    currentScene->intencityMult = GFXUtils::clamp(MasterAudioInput.midFilterVal * 3, 0.5, 1);
  }

  // currentScene->densityOffset = 0;
  // currentScene->densityOffset = (1 - GFXUtils::clamp(MasterAudioInput.midFilterVal * 10, 0, 1)) * -10;

  currentScene->update(deltaTime);
}

void SceneManager::checkButtonsState()
{
  if (!digitalRead(SCENE_AUTO_BUTTON_PIN) && selectionMode != AUTO)
  {
    Serial.println("AUTO");
    selectionMode = AUTO;
    setNextScene();
    return;
  }

  if (!digitalRead(SCENE_SELECT_1_BUTTON_PIN) && selectionMode != FIRE)
  {
    Serial.println("FIRE");
    selectionMode = FIRE;
    setNextScene();
    return;
  }

  if (!digitalRead(SCENE_SELECT_2_BUTTON_PIN) && selectionMode != AMBIENT)
  {
    Serial.println("AMBIENT");
    selectionMode = AMBIENT;
    setNextScene();
    return;
  }
}

void SceneManager::clockTick(Clock *clock)
{
  if (clockFromAudio)
  {
    return;
  }

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

void SceneManager::breakDownBegin()
{
  setNextScene();
};
void SceneManager::breakDownEnd()
{
  setNextScene();
};

// void SceneManager::doAutoRotateWithTime()
// {
//   long minute = millis() / 60000;

//   if (currentMinute != minute)
//   {
//     currentMinute = minute;

//     if (minute % 1 == 0)
//     {
//     }

//     if (currentSceneIdx % 2 == 0)
//     {
//       digitalWrite(2, true);
//     }
//     else
//     {
//       digitalWrite(2, false);
//     }
//   }
// }

void SceneManager::setCurrentSceneInx(int inx)
{
  if (selectionMode == AUTO)
  {
    currentSceneIdx = inx;
    currentSceneIdx = currentSceneIdx % SCENE_FUNCTION_COUNT;

    currentScene = MasterAudioInput.onBreakDown ? breakDownScenes.get(currentSceneIdx) : beatScenes.get(currentSceneIdx);
  }

  if (selectionMode == FIRE)
  {
    currentScene = MasterAudioInput.onBreakDown ? fireSceneBreakDown : fireSceneBeat;
  }

  if (selectionMode == AMBIENT)
  {
    currentScene = MasterAudioInput.onBreakDown ? ambientSceneBreakDown : ambientSceneBeat;
  }

  currentScene->nextStep();
}

void SceneManager::setNextScene()
{
  setCurrentSceneInx(currentSceneIdx + 1);
}

Scene *SceneManager::createTechnoScene(bool breakDown)
{
  Scene *scene = new Scene(strips);

  int inx;
  if (!breakDown)
  {
    int count = random(2, 6);
    for (int i = 0; i < count; i++)
    {
      inx = random(allCompositions.size());
      scene->addComposition(allCompositions.get(inx));
    }
  }
  else
  {
    inx = random(allCompositions.size());
    scene->addComposition(allCompositions.get(inx));
  }

  if (random(1000) > 500)
  {
    scene->applyOperation(SOP_Random);
  }
  else
  {
    scene->applyOperation(SOP_Sorted);
  }

  if (random(1000) > 10)
  {
    scene->addTimelineOperation(1, SOP_Random);
  }

  if (random(1000) > 10)
  {
    scene->addTimelineOperation(1, SOP_ShiftFW);
  }

  scene->isMirrored = random(2) > 1;

  scene->speed = random(2, 4);
  scene->hueOffset = random(255);

  return scene;
}

Scene *SceneManager::createFireScene(bool breakDown)
{
  Scene *scene = new Scene(strips);

  if (!breakDown)
  {
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

    //Apply initial operations
    // scene->applyOperation(SOP_Sorted);
    scene->applyOperation(SOP_Random);

    scene->speed = 5;
    // Set Timeline Operations

    scene->addTimelineOperation(1, SOP_Random);
    // scene->addTimelineOperation(1, SOP_RandomSpeed);
    scene->addTimelineOperation(1, SOP_ShiftFW);
    // scene->addTimelineOperation(3, SOP_ShiftBW);

    scene->isMirrored = true;
  }
  else
  {
    scene->addComposition(allCompositions.get(8));

    scene->applyOperation(SOP_Sorted);

    scene->addTimelineOperation(1, SOP_Random);
    scene->addTimelineOperation(1, SOP_ShiftFW);

    scene->isMirrored = false;
  }

  return scene;
}

Scene *SceneManager::createAmbientScene(bool breakDown)
{
  Scene *scene = new Scene(strips);

  //Add Compositions
  scene->addComposition(allCompositions.get(2));
  scene->addComposition(allCompositions.get(4));

  scene->hueOffset = 160;
  scene->speedOffset = 0.2;

  //Apply initial operations
  scene->applyOperation(SOP_Sorted);
  // scene->applyOperation(SOP_Random);

  // Set Timeline Operations

  scene->addTimelineOperation(1, SOP_Random);
  scene->addTimelineOperation(1, SOP_RandomSpeed);
  scene->addTimelineOperation(1, SOP_ShiftFW);
  // scene->addTimelineOperation(3, SOP_ShiftBW);

  scene->isMirrored = false;

  return scene;
}