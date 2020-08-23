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
  sgtl5000_1.micGain(20); // from 0db to 63db
  delay(1000);
}

void loop()
{

  if (fft1024_1.available())
  {
    float lowBand = fft1024_1.read(0, 4);
    float midBand = fft1024_1.read(15, 150);
    float hiBand = fft1024_1.read(200, 511);

    analogWrite(AUDIO_OUT_LOW_PIN, powf(lowBand * 5, 9) * 200 * 255);
    analogWrite(AUDIO_OUT_MID_PIN, powf(midBand * 20, 7) * 50 * 255);
    analogWrite(AUDIO_OUT_HIGH_PIN, powf(hiBand * 20, 6) * 500 * 255);
    // analogWrite(AUDIO_OUT_LOW_PIN, powf(lowBand * 5, 9) * 200 * 255);
    // analogWrite(AUDIO_OUT_MID_PIN, powf(midBand * 20, 7) * 50 * 255);
    // analogWrite(AUDIO_OUT_HIGH_PIN, powf(hiBand * 20, 8) * 500 * 255);
  }

  int time = millis() / 500;

  if (time % 2 == 0)
  {
    digitalWrite(AUDIO_OUT_CLOCK_PIN, true);
  }
  else
  {
    digitalWrite(AUDIO_OUT_CLOCK_PIN, 0);
  }
}
