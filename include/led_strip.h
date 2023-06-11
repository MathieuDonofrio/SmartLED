#ifndef LED_STRIP_H
#define LED_STRIP_H

#include <array>
#include <chrono>
#include <cstdlib>

#include "color.h"
#include "generator.h"

using namespace std::chrono_literals;

namespace ledshow
{
using ShowGenerator = Generator<std::chrono::milliseconds>;

namespace strip
{
  constexpr size_t LedAmount = 16;

  extern std::array<Color, LedAmount> leds;

  void Initialize() noexcept;

  void Uninitialize() noexcept;

  void Show() noexcept;
} // namespace strip
} // namespace ledshow

#endif