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
  Auto,
  Scene1,
  Scene2
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
  LinkedList<Scene *> scenes;
  Scene *currentScene;
  int currentSceneIdx = 0;
  long currentMinute = 0;
  SceneManager(CRGB *leds);
  virtual void update(float deltaTime);
  void clockTick(Clock *clock) override;

  void audioClockTick() override;

  Scene *createRandomScene();
  void setCurrentSceneInx(int inx);
  void setNextScene();
  void doAutoRotateWithTime();

  void checkButtonsState();

  SelectionMode selectionMode = Auto;

  Scene *createScene1();
  Scene *createScene2();
};

#endif
