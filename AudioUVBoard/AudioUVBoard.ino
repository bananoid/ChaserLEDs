#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <IntervalTimer.h>

// GUItool: begin automatically generated code
AudioInputI2S i2s2;            //xy=509,547
AudioAnalyzeFFT1024 fft1024_1; //xy=861,676
AudioOutputI2S i2s1;           //xy=1019,579
AudioConnection patchCord1(i2s2, 0, i2s1, 0);
AudioConnection patchCord2(i2s2, 0, i2s1, 1);
AudioConnection patchCord3(i2s2, 0, fft1024_1, 0);
AudioControlSGTL5000 sgtl5000_1; //xy=736,779
// GUItool: end automatically generated code

#include "config.h"

#include "AudioOutputs.h"

#include "UVLightManager.h"

double lowBand = 0;
double midBand = 0;
double hiBand = 0;

int kickDebounceTime = 100;

double kickThreshold = 0.5;
double kickThresholdFilterSpeed = 0.0002; // 0.00001;
double kickMinThreshold = 5;

double hihatThreshold = 0.5;
double hihatThresholdFilterSpeed = 0.0002; // 0.00001;
double hihatMinThreshold = 0.3;

bool kickTrig = false;
bool hihatTrig = false;

int micGainValue = 0;

long deltaTime = 0;
unsigned long lastTime;

UVLightManager uvLightManager;

void setup()
{
  pinMode(AUDIO_OUT_CLOCK_PIN, OUTPUT);
  pinMode(AUDIO_OUT_LOW_PIN, OUTPUT);
  pinMode(AUDIO_OUT_MID_PIN, OUTPUT);
  pinMode(AUDIO_OUT_HIGH_PIN, OUTPUT);

  pinMode(AUDIO_GAIN_POT_PIN, INPUT);

  Serial.begin(9600);
  AudioMemory(160);
  sgtl5000_1.enable();
  sgtl5000_1.volume(1);
  sgtl5000_1.inputSelect(AUDIO_INPUT_MIC);
  sgtl5000_1.micGain(30); // from 0db to 63db
  delay(1000);

  lastTime = micros();

  uvLightManager.begin();
}

void loop()
{
  unsigned long curTime = micros();
  deltaTime = curTime - lastTime;
  lastTime = curTime;

  if (fft1024_1.available())
  {
    lowBand = fft1024_1.read(1, 3);
    midBand = fft1024_1.read(1, 511);
    hiBand = fft1024_1.read(150, 300);

    lowBand = powf(lowBand * 2, 9);
    // midBand = midBand;
    midBand = powf(midBand * 1.1, 2) - 0.15;
    midBand = fmax(midBand, 0.0);
    midBand = fmin(midBand, 1.0);
    // midBand = powf(midBand - 1, 3) + 1;

    hiBand = powf(hiBand * 1.5, 8);
  }

  // analogWrite(AUDIO_OUT_HIGH_PIN, midBand * 255);
  analogWrite(AUDIO_OUT_MID_PIN, midBand * 255);
  analogWrite(AUDIO_OUT_LOW_PIN, hiBand * 255);

  if (lowBand > kickThreshold)
  {
    if (!kickTrig)
    {
      kickTrig = true;
      uvLightManager.clockTick();
    }
  }
  else
  {
    kickTrig = false;
  }
  hihatTrig = hiBand > hihatThreshold * 1.5;

  kickThreshold += (lowBand - kickThreshold) * kickThresholdFilterSpeed;
  kickThreshold = max(kickThreshold, kickMinThreshold);

  if (kickTrig)
  {
    hihatTrig = false;
  }
  hihatThreshold += (hiBand - hihatThreshold) * hihatThresholdFilterSpeed;
  hihatThreshold = max(hihatThreshold, hihatMinThreshold);

  digitalWrite(AUDIO_OUT_CLOCK_PIN, kickTrig);
  digitalWrite(AUDIO_OUT_HIGH_PIN, hihatTrig);

  int gainPotValue = analogRead(AUDIO_GAIN_POT_PIN);

  int gainValue = map(gainPotValue, 30.0, 1023.0, 0, 40);
  gainValue = max(0, gainValue);
  gainValue = min(63, gainValue);

  if (micGainValue != gainValue)
  {
    micGainValue = gainValue;
    sgtl5000_1.micGain(micGainValue);
  }
}