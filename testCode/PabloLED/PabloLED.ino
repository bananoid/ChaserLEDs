#include <Adafruit_NeoPixel.h>

// #define LED_PIN 2
#define NUMPIXELS 300

Adafruit_NeoPixel leds1 = Adafruit_NeoPixel(NUMPIXELS, 2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel leds2 = Adafruit_NeoPixel(NUMPIXELS, 5, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel leds3 = Adafruit_NeoPixel(NUMPIXELS, 11, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel leds4 = Adafruit_NeoPixel(NUMPIXELS, 7, NEO_GRB + NEO_KHZ800);

Adafruit_NeoPixel leds5 = Adafruit_NeoPixel(NUMPIXELS, 9, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel leds6 = Adafruit_NeoPixel(NUMPIXELS, 10, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel leds7 = Adafruit_NeoPixel(NUMPIXELS, 12, NEO_GRB + NEO_KHZ800);

void setup()
{

  leds1.begin();
  leds2.begin();
  leds3.begin();

  leds4.begin();
  leds5.begin();
  leds6.begin();
  leds7.begin();
}

void loop()
{
  leds1.clear();
  leds2.clear();
  leds3.clear();
  leds4.clear();
  leds5.clear();
  leds6.clear();
  leds7.clear();

  float time = millis();
  Serial.println(time);
  float osc1;
  float osc2;

  for (int i = 0; i < NUMPIXELS; i++)
  {
    osc1 = sinf(fmod(time * 0.02 + i * 0.5, TWO_PI)) * 0.5 + 0.5;
    osc1 = osc1 * osc1 * osc1;
    osc1 *= 255;

    osc2 = sinf(fmod(time * 0.02543, TWO_PI)) * 0.5 + 0.5;
    osc2 = osc2 * osc2 * osc2;
    osc2 *= 255;

    leds1.setPixelColor(i, leds1.Color(osc1, osc1 - osc2, osc1 - osc2));
    leds2.setPixelColor(i, leds2.Color(osc1 - osc2, osc1, osc1 - osc2));
    leds3.setPixelColor(i, leds3.Color(osc1 - osc2, osc1 - osc2, osc1));
    leds4.setPixelColor(i, leds4.Color(osc1, osc1 - osc2, osc1 - osc2));
    leds5.setPixelColor(i, leds5.Color(osc1 - osc2, osc1, osc1 - osc2));
    leds6.setPixelColor(i, leds6.Color(osc1 - osc2, osc1 - osc2, osc1));
    leds7.setPixelColor(i, leds7.Color(osc1, osc1 - osc2, osc1 - osc2));
  }

  leds1.show();
  leds2.show();
  leds3.show();
  leds4.show();
  leds5.show();
  leds6.show();
  leds7.show();
}