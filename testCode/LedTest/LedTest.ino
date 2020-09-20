#include <FastLED.h>

#define NUM_LEDS_PER_STRIP 300
#define NUM_STRIPS 6
#define LED_PORTS_FIRST_PIN 19

CRGB leds[NUM_STRIPS * NUM_LEDS_PER_STRIP];

// LED computations are done in parallel in the ports 19,18,14,15,17,16,22  ,23,20,21,26,27
// LED computations are done in parallel in the ports 14,15,16,17,18,19,20,21,22,23,26,27
// LED computations are done in parallel in the ports 10,12,11,13,6,9,32,8,7

void fillAll(CRGB color)
{
  for (int i = 0; i < NUM_STRIPS; i++)
  {
    for (int j = 0; j < NUM_LEDS_PER_STRIP; j++)
    {
      leds[(i * NUM_LEDS_PER_STRIP) + j] = color;
    }
  }
}

void indexTest(CRGB color, int speed)
{
  for (int i = 0; i < NUM_STRIPS; i++)
  {
    for (int j = 0; j < NUM_LEDS_PER_STRIP; j++)
    {
      leds[(i * NUM_LEDS_PER_STRIP) + j] = color;
      LEDS.show();
      delay(speed);
    }
  }
}

void setup()
{
  Serial.begin(9600);

  LEDS.addLeds<NUM_STRIPS, WS2811, 19, GRB>(leds, NUM_LEDS_PER_STRIP);

  LEDS.setBrightness(255);
  LEDS.setDither(0);
  LEDS.setMaxPowerInVoltsAndMilliamps(5, 10000);
}

void loop()
{
  fillAll(CRGB::White);
  LEDS.show();

  delay(3000);

  fillAll(CRGB::Black);
  LEDS.show();
  indexTest(CRGB::White, 50);

  delay(3000);

  fillAll(CRGB::Red);
  LEDS.show();

  delay(3000);

  fillAll(CRGB::Black);
  LEDS.show();
  indexTest(CRGB::Red, 50);

  delay(3000);
}