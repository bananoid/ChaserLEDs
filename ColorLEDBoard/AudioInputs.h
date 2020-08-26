#ifndef AUDIO_INPUTS_H
#define AUDIO_INPUTS_H

#include <Arduino.h>

#include <IntervalTimer.h>

#include "config.h"
class AudioInputs;

class AudioInputsDelegate
{
public:
  virtual void audioClockTick();
  virtual void breakDownBegin();
  virtual void breakDownEnd();
};

#define CLOCK_DEBOUNCE_TIME 62000 // 200000

static void kickTrig_outer();

class AudioInputs
{
private:
  IntervalTimer timer;

public:
  float low = 0;
  float mid = 0;
  float hight = 0;

  float breakDownLevel = 0;
  float breakDownDecaySpeed = 0.035;
  float breakDownFadeValue = 0;
  float breakDownFadeSpeed = 0.0000002;
  float breakDownEndFadeSpeed = 0.00001;

  bool onBreakDown = false;

  // bool clockIn = false;
  unsigned long lastClockInTime = 0;
  unsigned long lastUpdateTime;

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

    // timer.begin(kickTrig_outer, 10000);

    attachInterrupt(AUDIO_IN_CLOCK_PIN, kickTrig_outer, RISING);
  }

  void kickTrig()
  {
    unsigned long curTime = micros();
    long clockDeltaTime = curTime - lastClockInTime;

    bool clockIn = digitalRead(AUDIO_IN_CLOCK_PIN);

    if (clockIn && clockDeltaTime > CLOCK_DEBOUNCE_TIME)
    {
      lastClockInTime = curTime;
      if (delegate)
      {
        delegate->audioClockTick();
      }
      breakDownLevel = 1;
      digitalWrite(AUDIO_DEBUG_CLOCK_LED_PIN, true);
      delay(10);
      digitalWrite(AUDIO_DEBUG_CLOCK_LED_PIN, false);
    }
  }

  void update()
  {
    unsigned long curTime = micros();

    long deltaTime = curTime - lastUpdateTime;
    lastUpdateTime = curTime;

    float bdDeacay = breakDownDecaySpeed * deltaTime / 20000.0;
    breakDownLevel -= bdDeacay;
    breakDownLevel = max(0, breakDownLevel);

    if (breakDownLevel <= 0.0)
    {
      if (!onBreakDown)
      {
        onBreakDown = true;
        delegate->breakDownBegin();
        breakDownFadeValue = 1;
      }
      breakDownFadeValue += (0 - breakDownFadeValue) * breakDownFadeSpeed * deltaTime;
    }
    else
    {
      if (onBreakDown)
      {
        onBreakDown = false;
        delegate->breakDownEnd();
      }
      breakDownFadeValue += (1 - breakDownFadeValue) * breakDownEndFadeSpeed * deltaTime;
    }

    float lowFilterSpeed = 0.7;
    float midFilterSpeed = 0.1;
    // float highFilterSpeed = 0.7;

    low += (digitalRead(AUDIO_IN_LOW_PIN) - low) * lowFilterSpeed;
    mid += (digitalRead(AUDIO_IN_MID_PIN) - mid) * midFilterSpeed;
    // hight += (digitalRead(AUDIO_IN_HIGH_PIN) - hight) * highFilterSpeed;
    hight = digitalRead(AUDIO_IN_HIGH_PIN);

    // if (curTime / 400000 % 2 == 0)
    // {
    //   Serial.print(bdDeacay);
    //   Serial.print(" ");
    //   Serial.println(breakDownLevel);
    // }

    // analogWrite(AUDIO_DEBUG_LOW_LED_PIN, low * 255);
    // analogWrite(AUDIO_DEBUG_MID_LED_PIN, mid * 255);
    // analogWrite(AUDIO_DEBUG_HIGH_LED_PIN, hight * 255);

    analogWrite(AUDIO_DEBUG_LOW_LED_PIN, breakDownLevel * 255);
    analogWrite(AUDIO_DEBUG_MID_LED_PIN, breakDownFadeValue * 255);
    digitalWrite(AUDIO_DEBUG_HIGH_LED_PIN, onBreakDown);
  }
};

extern AudioInputs MasterAudioInput;

static void kickTrig_outer()
{
  MasterAudioInput.kickTrig();
}

#endif