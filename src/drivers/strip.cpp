#include "drivers/strip.h"

namespace smartled::strip
{
std::array<CRGB, LedAmount> leds;

void Initialize() noexcept
{
  delay(2000); // Sanity delay
  
  std::fill(leds.begin(), leds.end(), CRGB::Black);

  FastLED.addLeds<WS2812B, DataPin, GRB>(leds.data(), LedAmount).setCorrection(TypicalLEDStrip);
}
} // namespace smartled::strip
