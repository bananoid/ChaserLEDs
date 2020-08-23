#define NUM_LEDS_PER_STRIP 300
#define NUM_STRIPS 6
#define NUM_COMPOSITION 3

// LED computations are done in parallel in the ports 19,18,14,15,17,16,22
// LED computations are done in parallel in the ports 10,12,11,13,6,9,32,8,7
#define LED_PORTS_FIRST_PIN 19

#define CLOCK_LED_PIN 13
#define CLOCK_TAP_PIN 3

#define INTERNAL_CLOCK_SWITCH_PIN 34
#define SCENE_AUTO_BUTTON_PIN 32
#define SCENE_SELECT_1_BUTTON_PIN 31
#define SCENE_SELECT_2_BUTTON_PIN 30

#define AUDIO_IN_CLOCK_PIN 24 //A10
#define AUDIO_IN_LOW_PIN 25   //A11
#define AUDIO_IN_MID_PIN 26   //A12
#define AUDIO_IN_HIGH_PIN 27  //A13

#define AUDIO_DEBUG_CLOCK_LED_PIN 33
#define AUDIO_DEBUG_LOW_LED_PIN 9
#define AUDIO_DEBUG_MID_LED_PIN 8
#define AUDIO_DEBUG_HIGH_LED_PIN 7
