#ifndef SCENE_H
#define SCENE_H

#include <LinkedList.h>

#include "config.h"

#include "Composition.h"
#include "Strip.h"
#include "Clock.h"

enum SceneOperationType
{
  Sorted,
  Random,
  ShiftFW,
  ShiftBW,
  Mirror
};

struct SceneOperation
{
  SceneOperationType type = Sorted;
  int frequency = 32;
};

class Scene
{
private:
  int stripsToComp[NUM_STRIPS];
  int animationSteps;

public:
  int stepCount = 0;
  LinkedList<Composition *> compositions;
  LinkedList<SceneOperationType> operations;
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
