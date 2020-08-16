#ifndef SCENE_H
#define SCENE_H

#include <LinkedList.h>

#include "config.h"

#include "Composition.h"
#include "Strip.h"
#include "Clock.h"

class Scene
{
private:
  int stripsToComp[NUM_STRIPS];
  int animationSteps;

public:
  int stepCount = 0;
  LinkedList<Composition *> compositions;
  Strip **strips;
  Scene(Strip **strips);

  float speedOffset = 1;
  float hueOffset = 0;

  virtual void addComposition(Composition *composition);
  virtual void nextStep();
  virtual void update(float deltaTime);
  virtual void setAnimationSpeed(float speed);
  virtual void randomize();
  virtual void shiftFW();
  virtual void shiftBW();
  virtual void mirror();
};

#endif
