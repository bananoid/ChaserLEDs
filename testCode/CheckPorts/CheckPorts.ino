
#define AUDIO_IN_CLOCK_PIN 24 //A10
#define AUDIO_IN_LOW_PIN 25   //A11
#define AUDIO_IN_MID_PIN 26   //A12
#define AUDIO_IN_HIGH_PIN 27  //A13

#define AUDIO_DEBUG_CLOCK_LED_PIN 9
#define AUDIO_DEBUG_LOW_LED_PIN 4
#define AUDIO_DEBUG_MID_LED_PIN 8
#define AUDIO_DEBUG_HIGH_LED_PIN 7

void setup()
{
  pinMode(AUDIO_IN_CLOCK_PIN, INPUT);
  pinMode(AUDIO_IN_LOW_PIN, INPUT);
  pinMode(AUDIO_IN_MID_PIN, INPUT);
  pinMode(AUDIO_IN_HIGH_PIN, INPUT);

  pinMode(AUDIO_DEBUG_WHITE_LED_PIN, OUTPUT);
  pinMode(AUDIO_DEBUG_LOW_LED_PIN, OUTPUT);
  pinMode(AUDIO_DEBUG_MID_LED_PIN, OUTPUT);
  pinMode(AUDIO_DEBUG_HIGH_LED_PIN, OUTPUT);
}

void loop()
{
  digitalWrite(AUDIO_DEBUG_WHITE_LED_PIN, digitalRead(AUDIO_IN_CLOCK_PIN));
  //   digitalWrite(AUDIO_DEBUG_LOW_LED_PIN, digitalRead(AUDIO_IN_LOW_PIN));
  digitalWrite(AUDIO_DEBUG_MID_LED_PIN, digitalRead(AUDIO_IN_MID_PIN));
  digitalWrite(AUDIO_DEBUG_HIGH_LED_PIN, digitalRead(AUDIO_IN_HIGH_PIN));
}