#include "Clock.h"

#include <Arduino.h>

static void tick_outer();
static void tap_outer();

Clock::Clock()
{
  ticksCount = 0;
  beatTime = DEFAULT_BEAT_TIME;

  lastTapTime = 0;
  tapCount = 0;

  delegate = NULL;
}

void Clock::begin()
{

#ifdef CLOCK_LED_PIN
  pinMode(CLOCK_LED_PIN, OUTPUT);
#endif
  pinMode(CLOCK_TAP_PIN, INPUT_PULLUP);
  attachInterrupt(CLOCK_TAP_PIN, tap_outer, FALLING);

  setClockSpeed(DEFAULT_BEAT_TIME);
}

void Clock::tap()
{
  unsigned long curTime = micros();

  long deltaTapTime = curTime - lastTapTime;

  if (deltaTapTime > TAP_TIME_OUT)
  {
    tapCount = 0;
  }

  if (deltaTapTime < TAP_DEBOUNCE_TIME)
  {
    return;
  }

  if (tapCount == 0)
  {
    firstTapTime = curTime;
  }

  lastTapTime = curTime;
  tapCount++;

  if (tapCount >= TAP_MAX_COUNT)
  {
    long bT = (lastTapTime - firstTapTime) / (TAP_MAX_COUNT - 1);
    ticksBeatCount = 0;
    ticksCount = 0;
    tapCount = 0;
    setClockSpeed(bT);
  }

#ifdef CLOCK_LED_PIN
  digitalWrite(CLOCK_LED_PIN, true);
  delay(10);
  digitalWrite(CLOCK_LED_PIN, false);
#endif
}

void Clock::tick()
{

  long deltaTapTime = micros() - lastTapTime;

  if (deltaTapTime > TAP_TIME_OUT)
  {
    tapCount = 0;
  }

  if (tapCount == 0)
  {
#ifdef CLOCK_LED_PIN
    if (ticksBeatCount == 0)
    {
      digitalWrite(CLOCK_LED_PIN, true);
    }
    else
    {
      digitalWrite(CLOCK_LED_PIN, false);
    }
#endif
  }

  ticksBeatCount++;
  ticksCount++;

  if (ticksBeatCount >= TICK_PER_BEAT)
  {
    ticksBeatCount = 0;
  }

  if (delegate)
  {
    delegate->clockTick(this);
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

static void tap_outer()
{
  MasterClock.tap();
}