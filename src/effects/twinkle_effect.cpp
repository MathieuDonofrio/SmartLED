#include "effects/twinkle_effect.h"

#include <random>

#include "core/strip.h"

namespace smartled
{
ShowGenerator TwinkleEffect::Show() noexcept 
{
  std::uniform_int_distribution<> dist(0, strip::leds.size() - 1);

  for (size_t i = 0; i < _count; ++i)
  {
    strip::leds[dist(_random)] = _color;

    co_yield _delay;
  }

  co_yield _delay;

  std::fill(strip::leds.begin(), strip::leds.end(), Color::Black);

  co_yield _delay;
}

void TwinkleEffect::OnStart() noexcept
{
  std::fill(strip::leds.begin(), strip::leds.end(), Color::Black);
}

void TwinkleEffect::OnStop() noexcept
{
  std::fill(strip::leds.begin(), strip::leds.end(), Color::Black);
}
} // namespace ledshow