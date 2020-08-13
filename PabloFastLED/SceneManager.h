#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "config.h"

#include <LinkedList.h>

#include "Composition.h"
#include "Scene.h"
#include "Strip.h"

class SceneManager
{
private:
public:
  Strip *strips[NUM_STRIPS];
  LinkedList<Scene *> scenes;
  Scene *currentScene;
  SceneManager(CRGB *leds);
  virtual void update(float deltaTime);
};

#endif
