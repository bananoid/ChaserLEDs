#include <FastLED.h>

#define NUM_LEDS_PER_STRIP 300
#define NUM_STRIPS 7

CRGB leds[NUM_STRIPS * NUM_LEDS_PER_STRIP];

void setup()
{
  Serial.begin(9600);
  Serial.println("Starting...");

  // LED computations are done in parallel in the ports 19,18,14,15,17,16,22
  LEDS.addLeds<NUM_STRIPS, WS2811, 19, GRB>(leds, NUM_LEDS_PER_STRIP);
}

int step = 0;

void loop()
{

  Serial.println("Loop start");
  for (int i = 0; i < NUM_STRIPS; i++)
  {
    for (int j = 0; j < NUM_LEDS_PER_STRIP; j++)
    {
      leds[(i * NUM_LEDS_PER_STRIP) + j] = CRGB::Green;
    }
  }

  for (int i = 0; i < NUM_STRIPS; i++)
  {
    leds[(i * NUM_LEDS_PER_STRIP) + step] = CRGB::Red;
  }

  Serial.println(step);
  step += 1;
  if (step >= NUM_LEDS_PER_STRIP)
  {
    step = 0;
  }

  LEDS.show();
}
