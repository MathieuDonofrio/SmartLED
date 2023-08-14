#ifndef STRIP_H
#define STRIP_H

#include <array>
#include <chrono>

#include "utility/color.h"
#include "utility/generator.h"
#include "config.h"

using namespace std::chrono_literals;

namespace smartled
{
using ShowGenerator = Generator<std::chrono::milliseconds>;

namespace strip
{
  extern std::array<Color, LedAmount> leds;
  extern Color color;

  void Initialize() noexcept;

  void Show() noexcept;

  void SetBrightness(uint8_t brightness) noexcept;
}
}


#endif