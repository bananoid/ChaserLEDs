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
  case SOP_Mirror:
    opMirror();
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
  timelineOperations[division]->add(operation);
}

void Scene::update(float deltaTime)
{
  int compInx;
  Composition *comp;

  for (int i = 0; i < NUM_STRIPS; i++)
  {
    compInx = stripsToComp[i] % compositions.size();
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
    stripsToComp[i] = i % compositions.size();
  }
}

void Scene::opRandomize()
{
  for (int i = 0; i < NUM_STRIPS; i++)
  {
    stripsToComp[i] = random(compositions.size());
  }
}

void Scene::opShiftFW()
{
  int temp = stripsToComp[NUM_STRIPS - 1];
  for (int i = NUM_STRIPS - 1; i >= 0; i--)
  {
    stripsToComp[i + 1] = stripsToComp[i];
  }
  stripsToComp[0] = temp;
}

void Scene::opShiftBW()
{
  int temp = stripsToComp[0];
  for (int i = 0; i < NUM_STRIPS - 1; i++)
  {
    stripsToComp[i] = stripsToComp[i + 1];
  }
  stripsToComp[NUM_STRIPS - 1] = temp;
}

void Scene::opMirror()
{
  // TODO: do it
}

void Scene::opRandomSpeed()
{
  int dir = random(0, 2) > 0 ? -1 : 1;
  speedOffset = random(50, 800) / 100.0 * dir;
}