#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

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

float lowBand = 0;
float midBand = 0;
float hiBand = 0;

int kickDebounceTime = 100;
float kickThreshold = 0.5;
float kickThresholdFilterSpeed = 0.00001;
float kickMinThreshold = 0.1;
float kickMaxThreshold = 0.9;
bool kickTrig = false;

void setup()
{
  pinMode(AUDIO_OUT_CLOCK_PIN, OUTPUT);
  pinMode(AUDIO_OUT_LOW_PIN, OUTPUT);
  pinMode(AUDIO_OUT_MID_PIN, OUTPUT);
  pinMode(AUDIO_OUT_HIGH_PIN, OUTPUT);

  Serial.begin(9600);
  AudioMemory(160);
  sgtl5000_1.enable();
  sgtl5000_1.volume(1);
  sgtl5000_1.inputSelect(AUDIO_INPUT_MIC);
  sgtl5000_1.micGain(30); // from 0db to 63db
  delay(1000);
}

void loop()
{

  if (fft1024_1.available())
  {
    lowBand = fft1024_1.read(0, 4);
    midBand = fft1024_1.read(15, 150);
    hiBand = fft1024_1.read(200, 511);

    lowBand = powf(lowBand * 5, 9) * 200;
    midBand = powf(midBand * 20, 7) * 50;
    hiBand = powf(hiBand * 20, 6) * 500;
  }

  // analogWrite(AUDIO_OUT_LOW_PIN, lowBand * 255);
  // analogWrite(AUDIO_OUT_MID_PIN, midBand * 255);

  analogWrite(AUDIO_OUT_HIGH_PIN, midBand * 255);
  analogWrite(AUDIO_OUT_MID_PIN, lowBand * 255);
  analogWrite(AUDIO_OUT_LOW_PIN, kickThreshold * 255); // debug

  if (lowBand > kickThreshold)
  {
    kickTrig = true;
  }
  else
  {
    kickTrig = false;
  }

  kickThreshold = max(kickThreshold, kickMinThreshold);
  // kickThreshold = min(kickThreshold, kickMaxThreshold);

  kickThreshold += (lowBand - kickThreshold) * kickThresholdFilterSpeed;

  digitalWrite(AUDIO_OUT_CLOCK_PIN, kickTrig);
}
