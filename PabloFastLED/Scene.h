#ifndef SCENE_H
#define SCENE_H

#include "LinkedList.h"

#include "config.h"

#include "Composition.h"
#include "Strip.h"
#include "Clock.h"

#define OPERATION_TIME_MAX_EXP_DIVIDER 8 // 2^8 => 128 beat => 64 bars

enum SceneOperationType
{
  Sorted,
  Random,
  ShiftFW,
  ShiftBW,
  Mirror
};

class Scene
{
private:
  int stripsToComp[NUM_STRIPS];
  int animationSteps;

public:
  int stepCount = 0;
  LinkedList<Composition *> *compositions;
  Strip **strips;
  Scene(Strip **strips);
  virtual ~Scene();

  // LinkedList<SceneOperationType>
  int timelineOperation[OPERATION_TIME_MAX_EXP_DIVIDER];

  float speedOffset = 1;
  float hueOffset = 0;

  virtual void addComposition(Composition *composition);
  virtual void addTimelineOperation(int division, SceneOperationType operation);

  virtual void nextStep();
  virtual void update(float deltaTime);
  virtual void setAnimationSpeed(float speed);
  virtual void randomize();
  virtual void shiftFW();
  virtual void shiftBW();
  virtual void mirror();
};

#endif
