#ifndef CYLON_EFFECT_H
#define CYLON_EFFECT_H

#include "core/strip.h"

namespace smartled
{
class CylonEffect
{
public:
  CylonEffect(
    const Color& color, uint32_t size, std::chrono::milliseconds move_delay, std::chrono::milliseconds return_delay) noexcept
    : _color(color), _size(size), _move_delay(move_delay), _return_delay(return_delay) {}

  ShowGenerator Show() noexcept;

  void OnStart() noexcept;

  void OnStop() noexcept;

private:
  Color _color;
  uint32_t _size;
  std::chrono::milliseconds _move_delay;
  std::chrono::milliseconds _return_delay;
};
} // namespace ledshow

#endif