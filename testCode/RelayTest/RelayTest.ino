int pins[] = {0, 1, 2, 3, 4, 5, 6, 7};
int time = 10;
int speed = 1;
void setup()
{
  for (int i = 0; i < 8; i++)
  {
    pinMode(i, OUTPUT);
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
    digitalWrite(i, false);
    delay(time);
    digitalWrite(i, true);
    delay(time);
  }

  time += speed;
}