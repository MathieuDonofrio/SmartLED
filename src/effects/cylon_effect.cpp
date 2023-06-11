#include "effects/cylon_effect.h"

#include "led_strip.h"

namespace ledshow
{
ShowGenerator CylonEffect::Show() noexcept 
{
  const size_t steps = strip::leds.size() - _size + 1;

  for (uint32_t i = 0; i < steps; ++i)
  {
    std::fill(strip::leds.begin(), strip::leds.end(), Color::Black);

    for (uint32_t j = 0; j < _size; ++j)
    {
      strip::leds[i + j] = _color;
    }

    co_yield _move_delay;
  }

  co_yield _return_delay;

  for (int i = steps - 1; i >= 0; --i)
  {
    std::fill(strip::leds.begin(), strip::leds.end(), Color::Black);

    for (uint32_t j = 0; j < _size; ++j)
    {
      strip::leds[i + j] = _color;
    }

    co_yield _move_delay;
  }

  co_yield _return_delay;
}

void CylonEffect::OnStart() noexcept
{
  std::fill(strip::leds.begin(), strip::leds.end(), Color::Black);
}

void CylonEffect::OnStop() noexcept
{
  std::fill(strip::leds.begin(), strip::leds.end(), Color::Black);
}
} // namespace ledshow