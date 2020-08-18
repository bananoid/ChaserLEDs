#ifndef CLOCK_H
#define CLOCK_H

#include <Arduino.h>
#include <IntervalTimer.h>

#define DEFAULT_BEAT_TIME 500000 // 120 BPM in microsectonds
#define TICK_PER_BEAT 8          // Max resolition 1/32 Bar => 1/8 Beat
#define TAP_MAX_COUNT 8
#define TAP_TIME_OUT 2000000     // 30 BPM  => min clock speed
#define TAP_DEBOUNCE_TIME 200000 // 300 BPM => max clock speed

#define CLOCK_LED_PIN 13
#define CLOCK_TAP_PIN 3

class Clock;

class ClockDelegate
{
public:
  virtual void clockTick(Clock *clock);
};

class Clock
{
private:
  IntervalTimer timer;
  long beatTime; // Time in microseconds

  unsigned long firstTapTime;
  unsigned long lastTapTime;
  int tapCount;

public:
  unsigned long ticksCount;
  int ticksBeatCount;
  ClockDelegate *delegate;
  Clock();
  virtual void begin();
  virtual void tick();
  virtual void tap();
  virtual void setClockSpeed(long beatTime);
};

extern Clock MasterClock;

#endif