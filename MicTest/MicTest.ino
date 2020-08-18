void setup()
{
  Serial.begin(9600);
  Serial.print("Audio test");
  pinMode(13, OUTPUT);
}

float filterAudio = 0;

void loop()
{
  int val = analogRead(A9) / 9; // A9 = pin 23
  analogWrite(13, val);

  // filterAudio += (val - filterAudio) * 0.01;
  // analogWrite(13, filterAudio);

  // Serial.println(val);
}