#include "SceneManager.h"

#include "Compositions/Vein.h"
#include "Compositions/Rain.h"
#include "Compositions/SimpleColor.h"
#include "Compositions/Test.h"

SceneManager::SceneManager(CRGB *leds)
{

  pinMode(INTERNAL_CLOCK_SWITCH_PIN, INPUT_PULLUP);
  pinMode(SCENE_AUTO_BUTTON_PIN, INPUT_PULLUP);
  pinMode(SCENE_SELECT_1_BUTTON_PIN, INPUT_PULLUP);
  pinMode(SCENE_SELECT_2_BUTTON_PIN, INPUT_PULLUP);

  pinMode(SCENE_DEBUG_LED_PIN, OUTPUT);

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

  // currentScene->intencityMult = MasterAudioInput.mid * 2 + 0.1;
  // currentScene->speedOffset = 0.5 + MasterAudioInput.low * 2;

  currentScene->update(deltaTime);
}

void SceneManager::checkButtonsState()
{

  if (
      !digitalRead(SCENE_AUTO_BUTTON_PIN) ||
      !digitalRead(SCENE_SELECT_1_BUTTON_PIN) ||
      !digitalRead(SCENE_SELECT_2_BUTTON_PIN))
  {
    digitalWrite(SCENE_DEBUG_LED_PIN, true);
  }
  else
  {
    digitalWrite(SCENE_DEBUG_LED_PIN, false);
  }

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
}

void SceneManager::setNextScene()
{
  setCurrentSceneInx(currentSceneIdx + 1);
}

Scene *SceneManager::createTechnoScene(bool breakDown)
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
  scene->addTimelineOperation(1, SOP_ShiftFW);
  // scene->addTimelineOperation(3, SOP_ShiftBW);

  scene->isMirrored = true;

  return scene;
}

Scene *SceneManager::createFireScene(bool breakDown)
{
  Scene *scene = new Scene(strips);

  //Add Compositions
  scene->addComposition(allCompositions.get(0));

  scene->hueOffset = 130;

  //Apply initial operations
  scene->applyOperation(SOP_Sorted);
  scene->addComposition(allCompositions.get(4));
  // scene->applyOperation(SOP_Random);

  // Set Timeline Operations

  scene->addTimelineOperation(1, SOP_Random);
  scene->addTimelineOperation(1, SOP_RandomSpeed);
  scene->addTimelineOperation(1, SOP_ShiftFW);
  // scene->addTimelineOperation(3, SOP_ShiftBW);

  scene->isMirrored = false;

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