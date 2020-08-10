#include <FastLED.h>
#include "LEDShader.h"
#include "ChaserShader.h"

#define NUM_LEDS_PER_STRIP 300
#define NUM_STRIPS 7

// CRGB stripes[NUM_STRIPS][NUM_LEDS_PER_STRIP];
CRGB leds[NUM_STRIPS * NUM_LEDS_PER_STRIP];

ChaserShader *shader1;
ChaserShader *shader2;
ChaserShader *shader3;
ChaserShader *shader4;

// LEDShader *currentShader;
// CRGB leds0[NUM_LEDS_PER_STRIP];

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

  // LEDS.clear();
  clearAll();

  shader1 = new ChaserShader(NUM_LEDS_PER_STRIP);
  shader2 = new ChaserShader(NUM_LEDS_PER_STRIP);
  shader3 = new ChaserShader(NUM_LEDS_PER_STRIP);
  shader4 = new ChaserShader(NUM_LEDS_PER_STRIP);

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

  // LEDS.clear();
  clearAll();

  for (int stripInx = 0; stripInx < NUM_STRIPS; stripInx++)
  {

    shader1->speed = 2;
    shader2->speed = -3;
    shader3->speed = -1;
    shader4->speed = -10;

    shader1->hue = 10;
    shader2->hue = 150;
    shader3->hue = 150;
    shader4->hue = 150;

    shader1->brightness = 255;
    shader2->brightness = 255;
    shader3->brightness = 200;
    shader4->brightness = 255;

    shader1->density = 0.1;
    shader2->density = 0.1;
    shader3->density = 0.3;
    shader4->density = 0.1;

    shader1->update(deltaTimeF);
    shader2->update(deltaTimeF);
    shader3->update(deltaTimeF);
    shader4->update(deltaTimeF);

    shader1->render(leds, NUM_LEDS_PER_STRIP * stripInx);
    // shader2->render(leds, NUM_LEDS_PER_STRIP * stripInx);
    // shader3->render(leds, NUM_LEDS_PER_STRIP * stripInx);
    // shader4->render(leds, NUM_LEDS_PER_STRIP * stripInx);
  }

  LEDS.show();

  deltaTime = millis() - time;
  Serial.println(deltaTime);
}