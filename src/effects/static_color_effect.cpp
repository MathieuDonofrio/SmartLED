#include "effects/static_color_effect.h"

#include "led_strip.h"

namespace ledshow
{
ShowGenerator StaticColorEffect::Show() noexcept 
{
  co_yield 1s;
}

void StaticColorEffect::OnStart() noexcept
{
  std::fill(strip::leds.begin(), strip::leds.end(), _color);
}

void StaticColorEffect::OnStop() noexcept
{
  std::fill(strip::leds.begin(), strip::leds.end(), Color::Black);
}
} // namespace ledshow