#ifndef AUDIO_INPUTS_H
#define AUDIO_INPUTS_H

#include <Arduino.h>

#include "config.h"

class AuidoInputs
{
private:
public:
  float low = 0;
  float mid = 0;
  float hight = 0;
  bool clockIn = false;

  AuidoInputs()
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

    float lowFilterSpeed = 0.7;
    float midFilterSpeed = 0.1;
    float highFilterSpeed = 0.7;

    low += (digitalRead(AUDIO_IN_LOW_PIN) - low) * lowFilterSpeed;
    mid += (digitalRead(AUDIO_IN_MID_PIN) - mid) * midFilterSpeed;
    hight += (digitalRead(AUDIO_IN_HIGH_PIN) - hight) * highFilterSpeed;

    digitalWrite(AUDIO_DEBUG_CLOCK_LED_PIN, clockIn);

    analogWrite(AUDIO_DEBUG_LOW_LED_PIN, low * 255);
    analogWrite(AUDIO_DEBUG_MID_LED_PIN, mid * 255);
    analogWrite(AUDIO_DEBUG_HIGH_LED_PIN, hight * 255);
  }
};

extern AuidoInputs MasterAudioInput;

#endif