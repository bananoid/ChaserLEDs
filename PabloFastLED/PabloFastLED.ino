#include <FastLED.h>
#define NUM_STRIPS 3
#define NUM_LEDS_PER_STRIP 300

CRGB leds[NUM_STRIPS][NUM_LEDS_PER_STRIP];

// CRGB leds0[NUM_LEDS_PER_STRIP];

void setup()
{
  FastLED.addLeds<WS2812, 2, GRB>(leds[0], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812, 5, GRB>(leds[1], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812, 6, GRB>(leds[2], NUM_LEDS_PER_STRIP);

  FastLED.clear();
}

void loop()
{
  for (int stripInx = 0; stripInx < NUM_STRIPS; stripInx++)
  {
    for (int ledInx = 0; ledInx < NUM_LEDS_PER_STRIP; ledInx++)
    {
      leds[stripInx][ledInx] = CHSV((float)ledInx / (float)NUM_LEDS_PER_STRIP * 100.0, 255, 255);
    }
  }

  FastLED.show();
}