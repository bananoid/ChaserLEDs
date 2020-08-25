#ifndef AUDIO_INPUTS_H
#define AUDIO_INPUTS_H

#include <Arduino.h>

#include "config.h"
class AudioInputs;

class AudioInputsDelegate
{
public:
  virtual void audioClockTick();
};

#define CLOCK_DEBOUNCE_TIME 200000 // 200000

class AudioInputs
{
private:
public:
  float low = 0;
  float mid = 0;
  float hight = 0;
  bool clockIn = false;
  unsigned long lastClockInTime = 0;
  AudioInputsDelegate *delegate;

  AudioInputs()
  {
    pinMode(AUDIO_IN_CLOCK_PIN, INPUT);
    pinMode(AUDIO_IN_LOW_PIN, INPUT);
    pinMode(AUDIO_IN_MID_PIN, INPUT);
    pinMode(AUDIO_IN_HIGH_PIN, INPUT);

    pinMode(AUDIO_DEBUG_CLOCK_LED_PIN, OUTPUT);
    pinMode(AUDIO_DEBUG_LOW_LED_PIN, OUTPUT);
    pinMode(AUDIO_DEBUG_MID_LED_PIN, OUTPUT);
    pinMode(AUDIO_DEBUG_HIGH_LED_PIN, OUTPUT);
  }
  void update()
  {
    clockIn = digitalRead(AUDIO_IN_CLOCK_PIN);

    unsigned long curTime = micros();
    long clockDeltaTime = curTime - lastClockInTime;

    if (clockIn && clockDeltaTime > CLOCK_DEBOUNCE_TIME)
    {
      lastClockInTime = curTime;
      if (delegate)
      {
        delegate->audioClockTick();
      }
    }

    float lowFilterSpeed = 0.7;
    float midFilterSpeed = 0.1;
    float highFilterSpeed = 0.7;

    low += (digitalRead(AUDIO_IN_LOW_PIN) - low) * lowFilterSpeed;
    mid += (digitalRead(AUDIO_IN_MID_PIN) - mid) * midFilterSpeed;
    // hight += (digitalRead(AUDIO_IN_HIGH_PIN) - hight) * highFilterSpeed;
    hight = digitalRead(AUDIO_IN_HIGH_PIN);

    digitalWrite(AUDIO_DEBUG_CLOCK_LED_PIN, clockIn);

    analogWrite(AUDIO_DEBUG_LOW_LED_PIN, low * 255);
    analogWrite(AUDIO_DEBUG_MID_LED_PIN, mid * 255);
    analogWrite(AUDIO_DEBUG_HIGH_LED_PIN, hight * 255);
  }
};

extern AudioInputs MasterAudioInput;

#endif