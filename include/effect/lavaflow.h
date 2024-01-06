// Use shades of red to simulate the movement of lava, gradually shifting from deep red to brighter hues and back.

#ifndef EFFECT_LAVAFLOW_H
#define EFFECT_LAVAFLOW_H

#include "effect/effect.h"

namespace smartled::effect
{
class LavaFlow
{
public:

  ShowGenerator Show(const Color&) noexcept 
  {
    // using namespace std::chrono_literals;
    // Color red = Color(255, 0, 0);
    // Color orange = Color(255, 165, 0);

    // float speed = 0.01f;

    // while(true)
    // {
    //   auto t = time();

    //   std::array<float, strip::leds.size()> values;
      
    //   for (int32_t i = 0; i < strip::leds.size(); ++i)
    //   {
    //     float x = static_cast<float>(i) / strip::leds.size() * 2.0f;
    //     values[i] = fbm(voronoi, x, t * speed, 6, 0.7f);
    //   }

    //   normalize(values.begin(), values.end());

    //   for (int32_t i = 0; i < strip::leds.size(); ++i)
    //   {
    //     strip::leds[i] = lerp(red, orange, values[i]);
    //   }

    //   co_yield 10ms;
    // }

    co_return;
  }
};
} // namespace smartled::effect

#endif