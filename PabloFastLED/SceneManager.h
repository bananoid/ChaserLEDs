#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "config.h"

#include <LinkedList.h>

#include "Composition.h"
#include "Scene.h"
#include "Strip.h"
#include "Clock.h"

class SceneManager : public ClockDelegate
{
private:
public:
  Strip *strips[NUM_STRIPS];
  LinkedList<Scene *> scenes;
  Scene *currentScene;
  SceneManager(CRGB *leds);
  virtual void update(float deltaTime);
  void clockTick(Clock *clock) override;
};

#endif
