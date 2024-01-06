#ifndef DRIVERS_STRIP_H
#define DRIVERS_STRIP_H

#include <array>
#include <chrono>

#include "config.h"

#define FASTLED_ESP8266_DMA
#define FASTLED_ESP8266_RAW_PIN_ORDER
#include <FastLED.h>

using namespace std::chrono_literals;

namespace smartled
{
namespace strip
{
  constexpr size_t size = LedAmount;

  extern std::array<CRGB, size> leds;

  void Initialize() noexcept;

  void Show() noexcept;

  void SetBrightness(uint8_t brightness) noexcept;
} // namespace strip
} // namespace smartled

#endif