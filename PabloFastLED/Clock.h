#ifndef CLOCK_H
#define CLOCK_H

#include <Arduino.h>
#include <IntervalTimer.h>

#define DEFAULT_BEAT_TIME 500000 // 120 BPM in microsectonds
#define TICK_PER_BEAT 32
#define TAP_TIME_OUT 2000000 // 30 BPM minumum clock

#define CLOCK_LED_PIN 13

class ClockDelegate
{
  virtual void clockTick();
};

class Clock
{
private:
  IntervalTimer timer;
  long beatTime; // Time in microseconds
  unsigned long ticksCount;
  int ticksBeatCount;
  unsigned long lastTapTime;

public:
  ClockDelegate *delegate;
  Clock();
  virtual void begin();
  virtual void tick();
  virtual void tap();
  virtual void setClockSpeed(long beatTime);
};

extern Clock MasterClock;

#endif