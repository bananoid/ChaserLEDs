#ifndef SCENE_H
#define SCENE_H

#include <LinkedList.h>

#include "config.h"

#include "Composition.h"
#include "Strip.h"

class Scene
{
private:
  int stripsToComp[NUM_STRIPS];

public:
  int stepCount = 0;
  LinkedList<Composition *> compositions;
  Strip **strips;
  Scene(Strip **strips);
  virtual void addComposition(Composition *composition);
  virtual void nextStep();
  virtual void update(float deltaTime);
};

#endif
