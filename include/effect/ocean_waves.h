// Simulate the gentle ebb and flow of ocean waves using varying shades of blue that move in a wave-like pattern.

#ifndef EFFECT_OCEAN_WAVES_H
#define EFFECT_OCEAN_WAVES_H

#include "effect/effect.h"

namespace smartled::effect
{
class OceanWaves
{
public:
  ShowGenerator Show() noexcept 
  {
    std::array<uint8_t, strip::size> values;

    float e = std::exp(1.0f);

    co_return;
  }

// function ocean_waves(n::Int32, t::Float32, wave_speed::Float32)::Array{NTuple{3,Float32},1}
//   # Generate ocean wave heights

//   values = zeros(Float32, n)

//   e = exp(1.0f0)
//   x = 2 * pi * t * wave_speed
//   cycle = floor(x / pi)
//   x = mod(x, pi)

//   wave = (sin(x) * e^(-x^2)) / 0.4f0 # 0 to 1
//   dwave = -e^(-x^2)*(2*x*sin(x)-cos(x))

//   noise = normalize([fbm(perlin, Float32(i) / n * 8, t * 2, Int32(6), 0.8f0) for i in 1:n])

//   for i in 1:n
//     x = Float32(i) / n

//     if cycle % 2 == 1 # Change wave direction every cycle
//       x = 1 - x
//     end

//     # Wave foam 

//     foam = min(3 * x * wave, 1)

//     # Dissolve foam using noise

//     dissolve = dwave < 0

//     if dissolve
//       if noise[i] >= wave
//         foam *= noise[i]
//       end
//     end

//     values[i] = foam
//   end

//   # Generate colors

//   shallow = (0.0f0, 0.3686274509803922f0, 0.7215686274509804f0) #005EB8
//   deep = (0.0392156862745098f0, 0.6392156862745098f0, 0.8117647058823529f0) #0AA3CF

//   colors = [lerp(shallow, deep, values[x]) for x in 1:n]

//   return colors
// end

};
} // namespace smartled::effect

#endif