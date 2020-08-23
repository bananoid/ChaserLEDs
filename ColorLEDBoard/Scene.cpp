#include "Scene.h"

#include <Arduino.h>
#include "GFXUtils.h"
#include <Arduino.h>

Scene::Scene(Strip **strips)
{
  compositions = LinkedList<Composition *>();
  this->strips = strips;

  for (int i = 0; i < OPERATION_TIME_MAX_EXP_DIVIDER; i++)
  {
    timelineOperations[i] = new LinkedList<SceneOperationType>();
  }
}

Scene::~Scene()
{
}

void Scene::addComposition(Composition *composition)
{
  compositions.add(composition);
}

void Scene::applyOperation(SceneOperationType op)
{
  switch (op)
  {
  case SOP_Sorted:
    opSort();
    break;
  case SOP_Random:
    opRandomize();
    break;
  case SOP_ShiftFW:
    opShiftFW();
    break;
  case SOP_ShiftBW:
    opShiftBW();
    break;
  case SOP_RandomSpeed:
    opRandomSpeed();
    break;
  default:
    break;
  }
}

void Scene::addTimelineOperation(int division, SceneOperationType operation)
{
  division = division - 1;
  division = max(division, 0);
  division = min(division, OPERATION_TIME_MAX_EXP_DIVIDER - 1);
  timelineOperations[division]->add(operation);
}

void Scene::update(float deltaTime)
{
  int compInx;
  Composition *comp;

  StripToComp stp = stripsToComp;
  if (isMirrored)
  {
    stp = mirror(stp);
  }
  for (int i = 0; i < NUM_STRIPS; i++)
  {
    compInx = stp.map[i] % compositions.size();
    comp = compositions.get(compInx);

    comp->speedOffset = speedOffset;
    comp->hueOffset = hueOffset;

    comp->update(strips[i], deltaTime);
  }
}

void Scene::nextStep()
{
  LinkedList<SceneOperationType> *ops;
  SceneOperationType opType;
  long ticksCount = MasterClock.ticksCount;

  int div;

  for (int i = 0; i < OPERATION_TIME_MAX_EXP_DIVIDER; i++)
  {
    div = ((int)powf(2, i));

    if (ticksCount % div == 0)
    {
      ops = timelineOperations[i];
      for (int j = 0; j < ops->size(); j++)
      {
        opType = ops->get(j);
        applyOperation(opType);
      }
    }
  }
}

void Scene::opSort()
{
  for (int i = 0; i < NUM_STRIPS; i++)
  {
    stripsToComp.map[i] = i % compositions.size();
  }
}

void Scene::opRandomize()
{
  for (int i = 0; i < NUM_STRIPS; i++)
  {
    stripsToComp.map[i] = random(compositions.size());
  }
}

void Scene::opShiftFW()
{
  int temp = stripsToComp.map[NUM_STRIPS - 1];
  for (int i = NUM_STRIPS - 1; i >= 1; i--)
  {
    stripsToComp.map[i] = stripsToComp.map[i - 1];
  }
  stripsToComp.map[0] = temp;
}

void Scene::opShiftBW()
{
  int temp = stripsToComp.map[0];
  for (int i = 0; i < NUM_STRIPS - 1; i++)
  {
    stripsToComp.map[i] = stripsToComp.map[i + 1];
  }
  stripsToComp.map[NUM_STRIPS - 1] = temp;
}

void Scene::opRandomSpeed()
{
  int dir = random(0, 20) > 0 ? -1 : 1;

  // int fastSpeed = random(0, 20) > 0 ? 0 : 1;
  // speedOffset = random(100, 1000 + 500 * speedOffset) / 100.0 * dir;

  speedOffset = random(500, 1000) / 100.0 * dir;
}

StripToComp Scene::mirror(StripToComp stripsToComp)
{
  for (int i = 0; i < NUM_STRIPS / 2; i++)
  {
    stripsToComp.map[NUM_STRIPS - 1 - i] = stripsToComp.map[i];
  }

  return stripsToComp;
}