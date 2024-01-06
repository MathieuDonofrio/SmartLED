// Create a breathing effect resembling the natural rhythm of trees and plants, where the green light gently fades in
// and out.

#ifndef EFFECT_BREATHING_FOREST_H
#define EFFECT_BREATHING_FOREST_H

#include "effect/effect.h"

namespace smartled::effect
{
class BreathingForest
{
public:
// function breathing_forest(n::Int32, t::Float32, speed::Float32, forest_scale::Float32)
//   # Wind 

//   wind = perlin(t * speed) * 0.1f0
//   wind_slope = wind - perlin((t - 0.1f0) * speed)
//   wind_intensity = max(min(abs(wind_slope), 1.0f0), 0.1f0)

//   # Forest

//   forest = [fbm(perlin, (Float32(i) / n) * forest_scale + wind, Int32(6), 0.9f0) for i in 1:n]
//   forest = normalize(forest)
//   forest = [x * wind_intensity for x in forest]

//   # Generate colors

//   dark_green = (0.10f0, 0.66f0, 0.44f0)
//   light_green = (0.72f0, 0.89f0, 0.78f0)

//   colors = [lerp(dark_green, light_green, forest[x]) for x in 1:n]

//   return colors
// end

  ShowGenerator Show(const Color& color) noexcept 
  {
    // using namespace std::chrono_literals;

    // Color dark_green = Color(26, 168, 112);
    // Color light_green = Color(184, 227, 199);

    // float speed = 0.01f;
    // float forest_scale = 0.1f;

    // // Wind

    // float wind = perlin(0.0f) * 0.1f;
    // float wind_slope = wind - perlin(0.1f);
    // float wind_intensity = std::clamp(std::abs(wind_slope), 0.1f, 1.0f);

    // // Forest

    // std::array<float, strip::leds.size()> forest;

    // for (int32_t i = 0; i < strip::leds.size(); ++i)
    // {
    //   float x = static_cast<float>(i) / strip::leds.size() * forest_scale + wind;
    //   forest[i] = fbm(perlin, x, 6, 0.9f);
    // }

    // normalize(forest.begin(), forest.end());

    // for (int32_t i = 0; i < strip::leds.size(); ++i)
    // {
    //   forest[i] *= wind_intensity;
    // }

    // while(true)
    // {
    //   for (int32_t i = 0; i < strip::leds.size(); ++i)
    //   {
    //     strip::leds[i] = lerp(dark_green, light_green, forest[i]);
    //   }

    //   co_yield 100ms;
    // }

    co_return;
  }
};
} // namespace smartled::effect

#endif