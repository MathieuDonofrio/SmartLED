#ifndef EFFECT_EFFECT_H
#define EFFECT_EFFECT_H

#include <concepts>

#include "core/strip.h"

namespace smartled
{
template <typename T>
concept Effect = requires(T effect, const Color& color)
{
  { effect.Show(color) } -> std::same_as<ShowGenerator>;
};
} // namespace smartled

#endif