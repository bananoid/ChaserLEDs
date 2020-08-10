#include "LEDShader.h"

class ChaserShader : public LEDShader
{
public:
  ChaserShader(long numPixels) : LEDShader(numPixels){};
  void render(CRGB *leds, int startInx) override;
};