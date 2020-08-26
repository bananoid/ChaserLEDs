#ifndef AUDIO_INPUTS_H
#define AUDIO_INPUTS_H

#include <Arduino.h>

#include <IntervalTimer.h>

#include "config.h"
#include "GFXUtils.h"
class AudioInputs;

class AudioInputsDelegate
{
public:
  virtual void audioClockTick();
  virtual void breakDownBegin();
  virtual void breakDownEnd();
};

#define CLOCK_DEBOUNCE_TIME 62000 // 200000

#define CLOCK_MAX_BPM 600000   // 100 bpm
#define CLOCK_START_BPM 500000 // 120 bpm = 1000000 /(120 / 60)
#define CLOCK_MIN_BPM 300000   // 200 bpm

static void kickTrig_outer();
static void breakDownStartTimeout_outer();

class AudioInputs
{
private:
  IntervalTimer breakDownTimer;

public:
  double low = 0;
  double mid = 0;
  double hight = 0;

  double breakDownLevel = 0;
  double breakDownDecaySpeed = 0.035;
  double breakDownFadeValue = 0;
  double breakDownFadeSpeed = 0.0000002;
  double breakDownEndFadeSpeed = 0.00001;

  double lowFilterSpeed = 0.0007;
  double midFilterSpeed = 0.000004;

  double midFilterVal = 0;

  bool onBreakDown = false;

  // bool clockIn = false;
  unsigned long lastClockInTime = 0;
  unsigned long lastUpdateTime;

  AudioInputsDelegate *delegate;

  long lastKickDeltaTime = CLOCK_START_BPM;
  long clockDeltaTime = CLOCK_START_BPM;

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

    attachInterrupt(AUDIO_IN_CLOCK_PIN, kickTrig_outer, RISING);
  }

  void kickTrig()
  {
    unsigned long curTime = micros();

    clockDeltaTime = curTime - lastClockInTime;

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

      if (onBreakDown)
      {
        onBreakDown = false;
        delegate->breakDownEnd();
      }

      if (clockDeltaTime > CLOCK_MIN_BPM && clockDeltaTime < CLOCK_MAX_BPM)
      {
        lastKickDeltaTime = clockDeltaTime;
      }

      if (clockDeltaTime > CLOCK_MIN_BPM)
      {
        breakDownTimer.begin(breakDownStartTimeout_outer, lastKickDeltaTime * 2);
        Serial.print("start Time out ");
        Serial.println(lastKickDeltaTime);
      }

      Serial.println(clockDeltaTime);
    }
  }
  void breakDownStartTimeout()
  {
    breakDownTimer.end();
    onBreakDown = true;

    delegate->breakDownBegin();

    breakDownFadeValue = 1;
  }
  void update()
  {
    unsigned long curTime = micros();

    long deltaTime = curTime - lastUpdateTime;
    lastUpdateTime = curTime;

    float bdDeacay = breakDownDecaySpeed * deltaTime / 20000.0;
    breakDownLevel -= bdDeacay;
    breakDownLevel = max(0, breakDownLevel);

    if (onBreakDown)
    {
      breakDownFadeValue += (0 - breakDownFadeValue) * breakDownFadeSpeed * deltaTime;
    }
    else
    {
      breakDownFadeValue += (1 - breakDownFadeValue) * breakDownEndFadeSpeed * deltaTime;
    }

    // float highFilterSpeed = 0.7;

    low += (digitalRead(AUDIO_IN_LOW_PIN) - low) * lowFilterSpeed * deltaTime;
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
    digitalWrite(AUDIO_DEBUG_HIGH_LED_PIN, onBreakDown);

    // Peak form mid
    mid = (analogRead(AUDIO_IN_MID_PIN) - 80.0) / 944.0;
    mid = GFXUtils::clamp(mid, 0, 1);

    midFilterVal += (mid - midFilterVal) / midFilterSpeed * deltaTime;

    // Serial.println(analogRead(AUDIO_IN_MID_PIN));

    analogWrite(AUDIO_DEBUG_MID_LED_PIN, mid * 255);
  }
};

extern AudioInputs MasterAudioInput;

static void kickTrig_outer()
{
  MasterAudioInput.kickTrig();
}
static void breakDownStartTimeout_outer()
{
  MasterAudioInput.breakDownStartTimeout();
}

#endif