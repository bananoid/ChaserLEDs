#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "config.h"

#include "Composition.h"
#include "Strip.h"

class SceneManager
{
private:
public:
  Strip *strips[NUM_STRIPS];
  Composition *compositions[NUM_COMPOSITION];
  SceneManager(CRGB *leds);
  virtual void update(float deltaTime);
};

#endif
