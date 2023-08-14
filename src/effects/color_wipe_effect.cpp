#include "effects/color_wipe_effect.h"

#include "core/strip.h"

namespace smartled
{
ShowGenerator ColorWipeEffect::Show() noexcept
{
  for (auto& led : strip::leds)
  {
    led = strip::color;
    co_yield _delay;
  }

  for (auto& led : strip::leds)
  {
    led = Color::Black;
    co_yield _delay;
  }
}

void ColorWipeEffect::OnStart() noexcept
{
  std::fill(strip::leds.begin(), strip::leds.end(), Color::Black);
}

void ColorWipeEffect::OnStop() noexcept
{
  std::fill(strip::leds.begin(), strip::leds.end(), Color::Black);
}
} // namespace smartled