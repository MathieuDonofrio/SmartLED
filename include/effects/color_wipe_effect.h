#ifndef COLOR_WIPE_EFFECT_H
#define COLOR_WIPE_EFFECT_H

#include "core/strip.h"

namespace smartled
{
class ColorWipeEffect
{
public:
  ColorWipeEffect(
    const Color& color, std::chrono::milliseconds delay) noexcept
    : _color(color), _delay(delay) {}

  ShowGenerator Show() noexcept;

  void OnStart() noexcept;

  void OnStop() noexcept;

private:
  Color _color;
  std::chrono::milliseconds _delay;
};
} // namespace ledshow

#endif