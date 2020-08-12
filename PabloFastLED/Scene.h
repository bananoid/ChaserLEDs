#ifndef SCENE_H
#define SCENE_H

#include <LinkedList.h>

#include "config.h"

#include "Composition.h"
#include "Strip.h"

class Scene
{
private:
public:
  LinkedList<Composition *> compositions;
  Strip **strips;
  Scene(Strip **strips);
  virtual void addComposition(Composition *composition);
  virtual void update(float deltaTime);
};

#endif
