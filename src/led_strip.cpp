#include "led_strip.h"

#include <bit>

#include <FastLED.h>

namespace ledshow::strip
{
std::array<Color, LedAmount> leds;

constexpr uint8_t DATA_PIN = D1;

void Initialize() noexcept
{
  CRGB* fledcolors = reinterpret_cast<CRGB*>(leds.data()); // TODO bitcast

  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(fledcolors, LedAmount).setCorrection(TypicalLEDStrip);
}

void Uninitialize() noexcept
{
  FastLED.clear(true);
}

void Show() noexcept
{
  FastLED.show();
}
} // namespace ledshow::strip