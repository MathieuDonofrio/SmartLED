#ifndef EFFECT_EFFECT_H
#define EFFECT_EFFECT_H

#include <concepts>
#include <chrono>

#include "drivers/strip.h"
#include "utility/generator.h"
#include "utility/noise.h"
#include "utility/random.h"

namespace smartled
{
using ShowGenerator = Generator<std::chrono::milliseconds>;

std::chrono::milliseconds time_ms() noexcept
{
  auto time = std::chrono::system_clock::now().time_since_epoch();
  return std::chrono::duration_cast<std::chrono::milliseconds>(time);
}
} // namespace smartled

#endif