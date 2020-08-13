#include "Clock.h"

static void tick_outer();

Clock::Clock()
{
  ticksCount = 0;
  lastTapTime = 0;
  beatTime = DEFAULT_BEAT_TIME;
}

void Clock::begin()
{
  pinMode(CLOCK_LED_PIN, OUTPUT);
  setClockSpeed(DEFAULT_BEAT_TIME);
}

void Clock::tap()
{
}

void Clock::tick()
{
  if (ticksBeatCount == 0)
  {
    digitalWrite(CLOCK_LED_PIN, true);
  }
  else
  {
    digitalWrite(CLOCK_LED_PIN, false);
  }

  ticksBeatCount++;
  ticksCount++;

  if (ticksBeatCount >= TICK_PER_BEAT)
  {
    ticksBeatCount = 0;
  }
}

void Clock::setClockSpeed(long beatTime)
{
  this->beatTime = beatTime;
  timer.begin(tick_outer, beatTime / TICK_PER_BEAT);
}

Clock MasterClock;

static void tick_outer()
{
  MasterClock.tick();
}