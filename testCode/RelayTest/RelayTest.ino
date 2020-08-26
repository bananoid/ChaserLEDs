int pins[] = {33, 34, 35, 36, 37, 38, 39, 40};
int time = 10;
int speed = 1;
void setup()
{
  for (int i = 0; i < 8; i++)
  {
    pinMode(pins[i], OUTPUT);
  }
}

void loop()
{
  if (time >= 50)
  {
    time = 50;
    speed *= -1;
  }
  if (time <= 1)
  {
    time = 1;
    speed *= -1;
  }

  for (int i = 0; i < 8; i++)
  {
    digitalWrite(pins[i], true);
    delay(time);
    digitalWrite(pins[i], false);
    delay(time);
  }

  time += speed;
}