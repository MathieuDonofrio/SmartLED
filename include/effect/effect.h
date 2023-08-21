#ifndef EFFECT_EFFECT_H
#define EFFECT_EFFECT_H

#include <concepts>
#include <chrono>

#include "utility/color.h"
#include "utility/generator.h"

namespace smartled
{
using ShowGenerator = Generator<std::chrono::milliseconds>;

template <typename T>
concept Effect = requires(T effect, const Color& color)
{
  { effect.Show(color) } -> std::same_as<ShowGenerator>;
};
} // namespace smartled

#endif