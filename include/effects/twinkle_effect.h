#ifndef TWINKLE_EFFECT_H
#define TWINKLE_EFFECT_H

#include "led_strip.h"
#include "random.h"

namespace ledshow
{
class TwinkleEffect
{
public:
  TwinkleEffect(
    const Color& color, size_t count, std::chrono::milliseconds delay) noexcept
    : _color(color), _count(count), _delay(delay), _random() {}

  ShowGenerator Show() noexcept;

  void OnStart() noexcept;

  void OnStop() noexcept;

private:
  Color _color;
  size_t _count;
  std::chrono::milliseconds _delay;

  Random _random;
};
} // namespace ledshow

#endif