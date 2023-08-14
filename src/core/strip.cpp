#include "core/strip.h"

#define FASTLED_ESP8266_DMA
#define FASTLED_ESP8266_RAW_PIN_ORDER
#include <FastLED.h>

namespace smartled::strip
{
std::array<Color, LedAmount> leds;
Color color;

void Initialize() noexcept
{
  CRGB* fledcolors = reinterpret_cast<CRGB*>(leds.data()); // TODO bitcast

  FastLED.addLeds<WS2812B, DataPin, GRB>(fledcolors, LedAmount).setCorrection(TypicalLEDStrip);
  FastLED.clear(true);
  FastLED.setBrightness(255);
}

void Uninitialize() noexcept
{
  FastLED.clear(true);
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
