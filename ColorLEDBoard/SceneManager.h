#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "config.h"

#include "LinkedList.h"

#include "Composition.h"
#include "Scene.h"
#include "Strip.h"
#include "Clock.h"
#include "AudioInputs.h"

#define SCENE_FUNCTION_COUNT 1

enum SelectionMode
{
  AUTO,
  FIRE,
  AMBIENT
};

class SceneManager : public ClockDelegate, public AudioInputsDelegate
{
private:
  LinkedList<Composition *> allCompositions;

public:
  bool clockFromAudio = true;
  // void setClockFromAudio(bool fromAudio);
  int stepCount = 0;
  Strip *strips[NUM_STRIPS];

  LinkedList<Scene *> beatScenes;
  LinkedList<Scene *> breakDownScenes;

  Scene *fireSceneBeat;
  Scene *fireSceneBreakDown;

  Scene *ambientSceneBeat;
  Scene *ambientSceneBreakDown;

  Scene *currentScene;
  int currentSceneIdx = 0;
  long currentMinute = 0;
  SceneManager(CRGB *leds);
  virtual void update(float deltaTime);
  void clockTick(Clock *clock) override;

  void audioClockTick() override;
  void breakDownBegin() override;
  void breakDownEnd() override;

  void setCurrentSceneInx(int inx);
  void setNextScene();
  // void doAutoRotateWithTime();

  void checkButtonsState();

  SelectionMode selectionMode = AUTO;

  Scene *createTechnoScene(bool breakDown);
  Scene *createFireScene(bool breakDown);
  Scene *createAmbientScene(bool breakDown);
};

#endif
