#ifndef COLOR_WIPE_EFFECT_H
#define COLOR_WIPE_EFFECT_H

#include "core/strip.h"

namespace smartled
{
class ColorWipeEffect
{
public:
  ColorWipeEffect(std::chrono::milliseconds delay) noexcept : _delay(delay) {}

  ShowGenerator Show() noexcept;

  void OnStart() noexcept;

  void OnStop() noexcept;

private:
  std::chrono::milliseconds _delay;
};
} // namespace smartled

#endif