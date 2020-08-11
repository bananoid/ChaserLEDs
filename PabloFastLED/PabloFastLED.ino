#include <FastLED.h>
#include "LEDShader.h"
#include "ChaserShader.h"

#include "Strip.h"
#include "Composition.h"

#define NUM_LEDS_PER_STRIP 300
#define NUM_STRIPS 7

CRGB leds[NUM_STRIPS * NUM_LEDS_PER_STRIP];

Strip *strips[NUM_STRIPS];

Composition *composition;

// IntervalTimer frameTimer;

float deltaTime = 0;

void clearAll()
{
  for (int i = 0; i < NUM_STRIPS; i++)
  {
    for (int j = 0; j < NUM_LEDS_PER_STRIP; j++)
    {
      leds[(i * NUM_LEDS_PER_STRIP) + j] = CRGB::Black;
    }
  }
}

void setup()
{
  // LED computations are done in parallel in the ports 19,18,14,15,17,16,22
  LEDS.addLeds<NUM_STRIPS, WS2811, 19, GRB>(leds, NUM_LEDS_PER_STRIP);

  LEDS.setBrightness(255);
  LEDS.setDither(0);

  for (int i = 0; i < NUM_STRIPS; i++)
  {
    strips[i] = new Strip();
    strips[i]->leds = leds;
    strips[i]->numOfLed = NUM_LEDS_PER_STRIP;
    strips[i]->startInx = NUM_LEDS_PER_STRIP * i;
  }

  clearAll();

  composition = new Composition();

  // frameTimer.begin(drawFrame, 1000000 / 30);
}

void loop()
{
  drawFrame();
}

void drawFrame()
{

  float time = millis();
  float deltaTimeF = deltaTime * 0.001; // To pass delta time to seconds

  clearAll();

  for (int stripInx = 0; stripInx < NUM_STRIPS; stripInx++)
  {
    composition->update(deltaTimeF);
    composition->render(strips[stripInx]);
  }

  LEDS.show();

  deltaTime = millis() - time;
  Serial.println(deltaTime);
}