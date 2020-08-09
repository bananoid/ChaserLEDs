#include <FastLED.h>
#include "LEDShader.h"
#include "ChaserShader.h"

#define NUM_STRIPS 3
#define NUM_LEDS_PER_STRIP 300

CRGB stripes[NUM_STRIPS][NUM_LEDS_PER_STRIP];

ChaserShader *shader1;
ChaserShader *shader2;
ChaserShader *shader3;
ChaserShader *shader4;

// LEDShader *currentShader;
// CRGB leds0[NUM_LEDS_PER_STRIP];

IntervalTimer frameTimer;

float deltaTime = 0;

void setup()
{
  // Fot teensy 4.0 use 1,0,24,25,19,18,14,15,17,16,22,23,20,21,26,27

  FastLED.addLeds<WS2812, 2, GRB>(stripes[0], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812, 5, GRB>(stripes[1], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812, 6, GRB>(stripes[2], NUM_LEDS_PER_STRIP);
  // FastLED.addLeds<WS2812, 7, GRB>(stripes[0], NUM_LEDS_PER_STRIP);
  // FastLED.addLeds<WS2812, 8, GRB>(stripes[1], NUM_LEDS_PER_STRIP);
  // FastLED.addLeds<WS2812, 14, GRB>(stripes[2], NUM_LEDS_PER_STRIP);
  // FastLED.addLeds<WS2812, 20, GRB>(stripes[2], NUM_LEDS_PER_STRIP);
  FastLED.setBrightness(255);
  FastLED.setDither(0);

  FastLED.clear();

  // shader = new ChaserShader(NUM_LEDS_PER_STRIP);

  shader1 = new ChaserShader(NUM_LEDS_PER_STRIP);
  shader2 = new ChaserShader(NUM_LEDS_PER_STRIP);
  shader3 = new ChaserShader(NUM_LEDS_PER_STRIP);
  shader4 = new ChaserShader(NUM_LEDS_PER_STRIP);

  frameTimer.begin(drawFrame, 1000000 / 60);
}

void loop()
{
}

void drawFrame()
{

  float time = millis();
  float deltaTimeF = deltaTime * 0.001; // To pass delta time to seconds

  FastLED.clear();

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

    shader1->render(stripes[stripInx]);
    shader2->render(stripes[stripInx]);
    shader3->render(stripes[stripInx]);
    shader4->render(stripes[stripInx]);
  }
  FastLED.show();

  deltaTime = millis() - time;
  // Serial.println(deltaTime);
}