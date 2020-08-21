#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "config.h"

#include "LinkedList.h"

#include "Composition.h"
#include "Scene.h"
#include "Strip.h"
#include "Clock.h"

#define SCENE_FUNCTION_COUNT 1

class SceneManager : public ClockDelegate
{
private:
  LinkedList<Composition *> allCompositions;

public:
  bool autoRotateSceneMode = true;
  int stepCount = 0;
  Strip *strips[NUM_STRIPS];
  LinkedList<Scene *> scenes;
  Scene *currentScene;
  int currentSceneIdx = 0;
  long currentMinute = 0;
  SceneManager(CRGB *leds);
  virtual void update(float deltaTime);
  void clockTick(Clock *clock) override;
  Scene *createRandomScene();
  void setCurrentSceneInx(int inx);
  void setNextScene();
  void doAutoRotateWithTime();
};

#endif
