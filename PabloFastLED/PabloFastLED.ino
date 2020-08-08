#include <FastLED.h>
#include "LEDShader.h"

#define NUM_STRIPS 7
#define NUM_LEDS_PER_STRIP 300

CRGB stripes[NUM_STRIPS][NUM_LEDS_PER_STRIP];

LEDShader *shader;

// LEDShader *currentShader;
// CRGB leds0[NUM_LEDS_PER_STRIP];

IntervalTimer frameTimer;

void setup()
{
  FastLED.addLeds<WS2812, 2, GRB>(stripes[0], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812, 5, GRB>(stripes[1], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812, 6, GRB>(stripes[2], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812, 7, GRB>(stripes[0], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812, 8, GRB>(stripes[1], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812, 14, GRB>(stripes[2], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812, 20, GRB>(stripes[2], NUM_LEDS_PER_STRIP);

  FastLED.clear();

  shader = new LEDShader(NUM_LEDS_PER_STRIP);

  // frameTimer.begin(drawFrame, 1000000 / 60);
}

void loop()
{
  drawFrame();
}

void drawFrame()
{

  float time = millis();
  for (int stripInx = 0; stripInx < NUM_STRIPS; stripInx++)
  {
    shader->time = time * 0.001;

    shader->render(stripes[stripInx]);
  }
  FastLED.show();

  float lastFrameTime = millis() - time;
  Serial.println(lastFrameTime);
}