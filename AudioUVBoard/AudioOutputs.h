#ifndef AUDIO_OUTPUT_H
#define AUDIO_OUTPUT_H

#include <Arduino.h>

#include "config.h"

class AudioOutputs
{
private:
public:
  float low = 0;
  float mid = 0;
  float hight = 0;

  AudioOutputs()
  {
  }
  void update()
  {
  }
};
extern AudioOutputs MasterAudioInput;
#endif