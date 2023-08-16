#include "drivers/strip.h"

#define FASTLED_ESP8266_DMA
#define FASTLED_ESP8266_RAW_PIN_ORDER
#include <FastLED.h>

namespace smartled::strip
{
std::array<Color, LedAmount> leds;

void Initialize() noexcept
{
  delay(1000);
  
  std::fill(leds.begin(), leds.end(), Color::Black);

  CRGB* fledcolors = reinterpret_cast<CRGB*>(leds.data());

  FastLED.addLeds<WS2812B, DataPin, GRB>(fledcolors, LedAmount).setCorrection(TypicalLEDStrip);
  FastLED.clear(true);
  FastLED.setBrightness(255);

  FastLED.show();
}

void Show() noexcept
{
  FastLED.show();
}

void SetBrightness(uint8_t brightness) noexcept
{
  FastLED.setBrightness(brightness);
}
} // namespace smartled::strip
