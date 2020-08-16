void setup()
{
  Serial.begin(9600);
  Serial.print("Audio test");
  pinMode(13, OUTPUT);
}

float filterAudio = 0;

void loop()
{
  int val = analogRead(A9) / 7; // A9 = pin 23

  filterAudio += (val - filterAudio) * 0.01;
  analogWrite(13, filterAudio);

  // Serial.println(val);
}