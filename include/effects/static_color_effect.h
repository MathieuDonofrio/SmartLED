#ifndef STATIC_COLOR_EFFECT_H
#define STATIC_COLOR_EFFECT_H

#include "core/strip.h"

namespace smartled
{
class StaticColorEffect
{
public:
  StaticColorEffect(const Color& color) noexcept : _color(color) {}

  ShowGenerator Show() noexcept;

  void OnStart() noexcept;

  void OnStop() noexcept;

private:
  Color _color;
};
} // namespace ledshow

#endif