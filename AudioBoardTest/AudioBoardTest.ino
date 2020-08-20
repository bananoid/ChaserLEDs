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

void setup()
{
  pinMode(24, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(28, OUTPUT);

  Serial.begin(9600);
  AudioMemory(160);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
  sgtl5000_1.inputSelect(AUDIO_INPUT_MIC);
  sgtl5000_1.micGain(15); // from 0db to 63db
  delay(1000);
}

void loop()
{
  // do nothing
  // digitalWrite(30, true);
  // digitalWrite(31, true);
  // digitalWrite(32, true);
  // delay(1000);
  // digitalWrite(30, false);
  // digitalWrite(31, false);
  // digitalWrite(32, false);
  // delay(1000);
  // analogWrite(24, 255);
  // analogWrite(25, 127);
  // analogWrite(28, 10);
  if (fft1024_1.available())
  {
    float lowBand = fft1024_1.read(0, 4);
    float midBand = fft1024_1.read(15, 150);
    float hiBand = fft1024_1.read(200, 511);

    analogWrite(24, powf(lowBand * 3, 9) * 200 * 255);
    analogWrite(25, powf(midBand * 20, 7) * 50 * 255);
    analogWrite(28, powf(hiBand * 20, 8) * 500 * 255);
  }
}
