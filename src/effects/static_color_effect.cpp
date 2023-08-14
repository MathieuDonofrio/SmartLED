#include "effects/static_color_effect.h"

#include "core/strip.h"

namespace smartled
{
ShowGenerator StaticColorEffect::Show() noexcept
{
  co_yield 1s;
}

void StaticColorEffect::OnStart() noexcept
{
  std::fill(strip::leds.begin(), strip::leds.end(), strip::color);
}

void StaticColorEffect::OnStop() noexcept
{
  std::fill(strip::leds.begin(), strip::leds.end(), Color::Black);
}
} // namespace smartled