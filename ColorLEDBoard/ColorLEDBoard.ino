#include "config.h"

#include <FastLED.h>

#include "SceneManager.h"
#include "Clock.h"
#include "AudioInputs.h"

CRGB leds[NUM_STRIPS * NUM_LEDS_PER_STRIP];

// IntervalTimer frameTimer;

float deltaTime = 0;

SceneManager *sceneManager;

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
  randomSeed(analogRead(0));

  delay(500);
  Serial.begin(9600);
  // LED computations are done in parallel in the ports 19,18,14,15,17,16,22
  // LED computations are done in parallel in the ports 10,12,11,13,6,9,32,8,7
  LEDS.addLeds<NUM_STRIPS, WS2811, 19, GRB>(leds, NUM_LEDS_PER_STRIP);

  LEDS.setBrightness(255);
  LEDS.setDither(0);
  LEDS.setMaxPowerInVoltsAndMilliamps(5, 10000);

  clearAll();

  sceneManager = new SceneManager(leds);

  MasterClock.delegate = sceneManager;
  MasterClock.begin();

  MasterAudioInput.delegate = sceneManager;

  // frameTimer.begin(drawFrame, 1000000 / 30);

  pinMode(2, OUTPUT);
}

void loop()
{
  drawFrame();
  MasterAudioInput.update();
}

void drawFrame()
{

  float time = millis();
  float deltaTimeF = deltaTime * 0.001; // To pass delta time to seconds

  sceneManager->update(deltaTimeF);

  LEDS.show();

  deltaTime = millis() - time;
  // Serial.println(deltaTime);
}