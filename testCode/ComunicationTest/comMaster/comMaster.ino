#include <Wire.h>

void setup()
{
  Wire.begin();
}

void loop()
{
  byte num = 0;

  Wire.beginTransmission(80);
  Wire.write(0); // address high byte
  Wire.write(0); // address low byte
  Wire.endTransmission();
}