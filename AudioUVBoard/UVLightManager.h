#ifndef UV_LIGHT_MANAGER_H
#define UV_LIGHT_MANAGER_H

#include "config.h"

class UVLightManager
{
private:
  /* data */
public:
  int pins[UV_PINS_COUNT] = UV_PINS;
  bool barsState[UV_PINS_COUNT];
  unsigned long clock = 0;
  int mod = 2;
  UVLightManager()
  {
  }

  void begin()
  {
    for (int i = 0; i < UV_PINS_COUNT; i++)
    {
      pinMode(pins[i], OUTPUT);
    }
  }

  void update()
  {
  }

  void clockTick()
  {
    if ((clock) % random(1, 8) == 0)
    {
      mod = random(1, 8);
    }
    for (int i = 0; i < UV_PINS_COUNT; i++)
    {
      if ((clock + i) % mod == 0)
      {
        barsState[i] = !barsState[i];
        digitalWrite(pins[i], barsState[i]);
      }
    }

    clock++;
  }
};

#endif