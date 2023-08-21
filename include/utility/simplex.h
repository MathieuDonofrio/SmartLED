#ifndef UTILITY_SIMPLEX_H
#define UTILITY_SIMPLEX_H

#include <array>
#include <cstdint>

namespace smartled
{
namespace details
{
  // clang-format off
  constexpr std::array<uint8_t, 256> perm = 
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

  constexpr std::array<float, 16> grad =
  {
    -8, -7, -6, -5, -4, -3, -2, -1, 1, 2, 3, 4, 5, 6, 7, 8
  };
  // clang-format on

  constexpr int32_t fastfloor(float x)
  {
    int32_t i = static_cast<int32_t>(x);
    return (x < i) ? (i - 1) : i;
  }
}

constexpr float simplex(float x) noexcept
{
  using namespace details;

  // Corner coodinates
  int32_t i0 = fastfloor(x);
  int32_t i1 = i0 + 1;

  // Distances to corders
  float x0 = x - i0;
  float x1 = x0 - 1.0f;

  // Contributions
  float t0 = 1.0f - x0 * x0;
  float t1 = 1.0f - x1 * x1;

  t0 *= t0;
  t1 *= t1;

  float n0 = t0 * t0 * grad[perm[static_cast<uint8_t>(i0)]] * x0;
  float n1 = t1 * t1 * grad[perm[static_cast<uint8_t>(i1)]] * x1;

  return 0.395f * (n0 + n1);
}
} // namespace smartled

#endif