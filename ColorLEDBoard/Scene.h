#ifndef SCENE_H
#define SCENE_H

#include "LinkedList.h"

#include "config.h"

#include "Composition.h"
#include "Strip.h"
#include "Clock.h"

#define OPERATION_TIME_MAX_EXP_DIVIDER 12 // 2^8 => 128 beat => 64 bars

enum SceneOperationType
{
  SOP_Sorted,
  SOP_Random,
  SOP_ShiftFW,
  SOP_ShiftBW,
  SOP_RandomSpeed
};

struct StripToComp
{
  int map[NUM_STRIPS];
};

class Scene
{
private:
  StripToComp stripsToComp;

public:
  Strip **strips;
  LinkedList<Composition *> compositions;
  LinkedList<SceneOperationType> *timelineOperations[OPERATION_TIME_MAX_EXP_DIVIDER];

  bool isMirrored = false;

  float speedOffset = 1;
  float hueOffset = 0;

  Scene(Strip **strips);
  virtual ~Scene();

  virtual void addComposition(Composition *composition);
  virtual void applyOperation(SceneOperationType operation);
  virtual void addTimelineOperation(int division, SceneOperationType operation);

  virtual void nextStep();
  virtual void update(float deltaTime);

  // Operations
  virtual void opSort();
  virtual void opRandomize();
  virtual void opShiftFW();
  virtual void opShiftBW();
  virtual void opRandomSpeed();

  //
  virtual StripToComp mirror(StripToComp stripsToComp);
};

#endif
