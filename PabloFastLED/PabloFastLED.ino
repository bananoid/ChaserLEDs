#include <FastLED.h>
#include "LEDShader.h"
#include "ChaserShader.h"

#define NUM_STRIPS 3
#define NUM_LEDS_PER_STRIP 300

CRGB stripes[NUM_STRIPS][NUM_LEDS_PER_STRIP];

ChaserShader *shader;

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

  shader = new ChaserShader(NUM_LEDS_PER_STRIP);

  frameTimer.begin(drawFrame, 1000000 / 60);
}

void loop()
{
}

void drawFrame()
{

  float time = millis();
  float deltaTimeF = deltaTime * 0.001;

  float speed = sinf(time * 0.00005) * 2;

  for (int stripInx = 0; stripInx < NUM_STRIPS; stripInx++)
  {
    shader->speed = speed;
    shader->density = 0.1;
    shader->scale = 1;
    shader->update(deltaTimeF);
    shader->render(stripes[stripInx]);
  }
  FastLED.show();

  deltaTime = millis() - time;
  // Serial.println(deltaTime);
}