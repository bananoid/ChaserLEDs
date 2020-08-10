#ifndef STRIP_H
#define STRIP_H

class Strip
{
public:
  int startInx = 0;
  int numOfLed = 300;
  CRGB *leds;
};

#endif