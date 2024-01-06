#ifndef UTILITY_NOISE_H
#define UTILITY_NOISE_H

#include <array>
#include <cstdint>
#include <cmath>

namespace smartled
{
namespace details
{
  // Permutation table

  // clang-format off
  constexpr std::array<uint8_t, 256> p = 
  { 
    151, 160, 137, 91, 90, 15, 131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 140, 36, 
    103, 30, 69, 142, 8, 99, 37, 240, 21, 10, 23, 190, 6, 148, 247, 120, 234, 75, 0, 
    26, 197, 62, 94, 252, 219, 203, 117, 35, 11, 32, 57, 177, 33, 88, 237, 149, 56, 
    87, 174, 20, 125, 136, 171, 168, 68, 175, 74, 165, 71, 134, 139, 48, 27, 166, 
    77, 146, 158, 231, 83, 111, 229, 122, 60, 211, 133, 230, 220, 105, 92, 41, 55, 
    46, 245, 40, 244, 102, 143, 54, 65, 25, 63, 161, 1, 216, 80, 73, 209, 76, 132, 
    187, 208, 89, 18, 169, 200, 196, 135, 130, 116, 188, 159, 86, 164, 100, 109, 
    198, 173, 186, 3, 64, 52, 217, 226, 250, 124, 123, 5, 202, 38, 147, 118, 126, 
    255, 82, 85, 212, 207, 206, 59, 227, 47, 16, 58, 17, 182, 189, 28, 42, 223, 183, 
    170, 213, 119, 248, 152, 2, 44, 154, 163, 70, 221, 153, 101, 155, 167, 43, 
    172, 9, 129, 22, 39, 253, 19, 98, 108, 110, 79, 113, 224, 232, 178, 185, 112, 
    104, 218, 246, 97, 228, 251, 34, 242, 193, 238, 210, 144, 12, 191, 179, 162, 
    241, 81, 51, 145, 235, 249, 14, 239, 107, 49, 192, 214, 31, 181, 199, 106, 
    157, 184, 84, 204, 176, 115, 121, 50, 45, 127, 4, 150, 254, 138, 236, 205, 
    93, 222, 114, 67, 29, 24, 72, 243, 141, 128, 195, 78, 66, 215, 61, 156, 180 
  };

  // clang-format on

  constexpr std::array<uint8_t, 512> makePerm()
  {
    std::array<uint8_t, 512> perm{};

    for (int i = 0; i < 256; ++i)
    {
      perm[256 + i] = perm[i] = p[i];
    }

    return perm;
  }

  constexpr std::array<uint8_t, 512> perm = makePerm();

  constexpr int32_t fastfloor(float x) noexcept
  {
    int32_t i = static_cast<int32_t>(x);
    return (x < 0) ? (i - 1) : i;
  }

  constexpr float lerp(float a, float b, float t) noexcept
  {
    return a + t * (b - a);
  }

  constexpr float fade(double t)
  {
    return t * t * t * (t * (t * 6 - 15) + 10);
  }

  constexpr std::pair<float, float> hash2(float x, float y)
  {
    const float a = std::sin(x * 127.1f + y * 311.7f) * 43758.5453f;
    const float b = std::sin(x * 269.5f + y * 183.3f) * 43758.5453f;

    return { a - std::floor(a), b - std::floor(b) };
  }
} // namespace details

// Perlin noise

constexpr float perlin(float x) noexcept
{
  using namespace details;

  // Find unit square that contains point
  const int32_t ix = fastfloor(x);

  // Find relative x of point in square
  const float fx = x - static_cast<float>(ix);

  // Wrap the integer cells at 255
  const int32_t ix0 = ix & 0xFF;
  const int32_t ix1 = (ix0 + 1) & 0xFF;

  // Calculate the hash values
  const uint8_t h0 = perm[ix0];
  const uint8_t h1 = perm[ix1];

  // Calculate the gradient
  const float gx0 = static_cast<float>((h0 & 0x0F) - 8);
  const float gx1 = static_cast<float>((h1 & 0x0F) - 8);

  // Calculate the dot products
  const float n0 = gx0 * fx;
  const float n1 = gx1 * (fx - 1.0f);

  // Compute fade curves
  const float u = fade(fx);

  // Interpolate the two results
  return details::lerp(n0, n1, u);
}

constexpr float perlin(float x, float y) noexcept
{
  using namespace details;

  // Find unit square that contains point
  const int32_t ix = fastfloor(x);
  const int32_t iy = fastfloor(y);

  // Find relative x, y of point in square
  const float fx = x - static_cast<float>(ix);
  const float fy = y - static_cast<float>(iy);

  // Wrap the integer cells at 255
  const int32_t ix0 = ix & 0xFF;
  const int32_t iy0 = iy & 0xFF;
  const int32_t ix1 = (ix0 + 1) & 0xFF;
  const int32_t iy1 = (iy0 + 1) & 0xFF;

  // Calculate the hash values
  const uint8_t h00 = perm[ix0 + iy0];
  const uint8_t h10 = perm[ix1 + iy0];
  const uint8_t h01 = perm[ix0 + iy1];
  const uint8_t h11 = perm[ix1 + iy1];

  // Calculate the gradients
  const float gx00 = static_cast<float>((h00 & 0x0F) - 8);
  const float gy00 = static_cast<float>(((h00 >> 4) & 0x0F) - 8);
  const float gx10 = static_cast<float>((h10 & 0x0F) - 8);
  const float gy10 = static_cast<float>(((h10 >> 4) & 0x0F) - 8);
  const float gx01 = static_cast<float>((h01 & 0x0F) - 8);
  const float gy01 = static_cast<float>(((h01 >> 4) & 0x0F) - 8);
  const float gx11 = static_cast<float>((h11 & 0x0F) - 8);
  const float gy11 = static_cast<float>(((h11 >> 4) & 0x0F) - 8);

  // Calculate the dot products
  const float n00 = gx00 * fx + gy00 * fy;
  const float n10 = gx10 * (fx - 1.0f) + gy10 * fy;
  const float n01 = gx01 * fx + gy01 * (fy - 1.0f);
  const float n11 = gx11 * (fx - 1.0f) + gy11 * (fy - 1.0f);

  // Compute fade curves
  const float u = fade(fx);
  const float v = fade(fy);

  // Interpolate the four results
  const float a = details::lerp(n00, n10, u);
  const float b = details::lerp(n01, n11, u);
  const float c = details::lerp(a, b, v);

  return c;
}

// Voronoi

constexpr float voronoi(float x, float y) noexcept
{
  using namespace details;

  // Find unit square that contains point

  const int32_t ix = fastfloor(x);
  const int32_t iy = fastfloor(y);

  // Find relative x, y of point in square

  const float fx = x - static_cast<float>(ix);
  const float fy = y - static_cast<float>(iy);

  // Find min distance squared

  float r = 8.0f;

  for (int32_t i = -1; i <= 1; ++i)
  {
    for (int32_t j = -1; j <= 1; ++j)
    {
      const auto [h0, h1] = hash2(static_cast<float>(ix + i), static_cast<float>(iy + j));

      const float x = static_cast<float>(i) - fx + h0;
      const float y = static_cast<float>(j) - fy + h1;

      r = std::min(r, x * x + y * y);
    }
  }

  return std::sqrt(r);
}

// Fractal Brownian Motion

template<typename NoiseFunction>
constexpr float fbm(NoiseFunction&& func, float x, int32_t octaves, float persistance) noexcept
{
  float total = 0.0f;
  float amplitude = 1.0f;

  for (int32_t i = 0; i < octaves; ++i)
  {
    total += func(x) * amplitude;
    x *= 2.0f;
    amplitude *= persistance;
  }

  return total;
}

template<typename NoiseFunction>
constexpr float fbm(NoiseFunction&& func, float x, float y, int32_t octaves, float persistance) noexcept
{
  float total = 0.0f;
  float amplitude = 1.0f;

  for (int32_t i = 0; i < octaves; ++i)
  {
    total += func(x, y) * amplitude;
    x *= 2.0f;
    y *= 2.0f;
    amplitude *= persistance;
  }

  return total;
}

// Normalization

template<typename Iterator>
constexpr void normalize(Iterator first, Iterator last) noexcept
{
  auto [min_it, max_it] = std::minmax_element(first, last);
  auto min = *min_it, max = *max_it;
  auto diff = max - min;

  for (; first != last; ++first)
  {
    *first = (*first - min) / diff;
  }
}

}



// namespace smartled

#endif