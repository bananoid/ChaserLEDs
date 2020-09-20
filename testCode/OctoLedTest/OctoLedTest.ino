#define USE_OCTOWS2811
#include <OctoWS2811.h>
#include <FastLED.h>

#define NUM_LEDS_PER_STRIP 300
#define NUM_STRIPS 8

CRGB leds[NUM_STRIPS * NUM_LEDS_PER_STRIP];

// Pin layouts on the teensy 3:
// OctoWS2811: 2,14,7,8,6,20,21,5

void fillAll(CRGB color, int stripInx)
{
  // for (int i = 0; i < NUM_STRIPS; i++)
  // {
  for (int j = 0; j < NUM_LEDS_PER_STRIP; j++)
  {
    leds[(stripInx * NUM_LEDS_PER_STRIP) + j] = color;
  }
  // }
}

void indexTest(CRGB color, int speed)
{
  int i = 0;
  // for (int i = 0; i < NUM_STRIPS; i++)
  // {
  for (int j = 0; j < NUM_LEDS_PER_STRIP; j++)
  {
    leds[(i * NUM_LEDS_PER_STRIP) + j] = color;
    LEDS.show();
    delay(speed);
  }
  // }
}

void setup()
{
  LEDS.addLeds<OCTOWS2811>(leds, NUM_LEDS_PER_STRIP);

  LEDS.setBrightness(255);
  LEDS.setDither(0);

  // LEDS.setMaxPowerInVoltsAndMilliamps(5, 10000);
}

void loop()
{
  fillAll(CRGB::White, 0);
  LEDS.show();
  fillAll(CRGB::Red, 1);
  LEDS.show();
  fillAll(CRGB::Green, 2);
  LEDS.show();
  fillAll(CRGB::Blue, 3);
  LEDS.show();
  delay(500);

  fillAll(CRGB::White, 1);
  LEDS.show();
  fillAll(CRGB::Red, 2);
  LEDS.show();
  fillAll(CRGB::Green, 3);
  LEDS.show();
  fillAll(CRGB::Blue, 4);
  LEDS.show();
  delay(500);

  // delay(3000);

  // fillAll(CRGB::Black);
  // LEDS.show();
  // indexTest(CRGB::White, 50);

  // delay(3000);

  // fillAll(CRGB::Red);
  // LEDS.show();

  // delay(3000);

  // fillAll(CRGB::Black);
  // LEDS.show();
  // indexTest(CRGB::Red, 50);

  // delay(3000);
}