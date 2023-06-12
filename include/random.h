#ifndef RANDOM_H
#define RANDOM_H

#include <cstdint>

namespace ledshow
{
class Random
{
public:
  using result_type = uint32_t;
  
  static constexpr uint64_t cMultiplier = 6364136223846793005ull;
  static constexpr uint64_t cIncrement = 1442695040888963407ull;

  constexpr Random() noexcept : Random(0) {}

  constexpr explicit Random(const uint64_t seed) noexcept : state_(seed ^ cMultiplier)
  {
    discard(2);
  }

  constexpr uint32_t operator()() noexcept
  {
    // Reference: pcg-random.org

    const uint64_t old_state = state_;

    // Advance internal state
    state_ = old_state * cMultiplier + (cIncrement | 1u);

    // Calculate output function (XSH RR), uses old state for max ILP
    const auto xor_shifted = static_cast<uint32_t>(((old_state >> 18u) ^ old_state) >> 27u);
    const auto rot = static_cast<uint32_t>(old_state >> 59u);

    return (xor_shifted >> rot) | (xor_shifted << ((-rot) & 31u));
  }

  constexpr void discard(const uint64_t z) noexcept
  {
    for (uint64_t i = 0; i < z; ++i)
    {
      state_ = state_ * cMultiplier + (cIncrement | 1u);
    }
  }

  static constexpr uint32_t min() noexcept
  {
    return 0u;
  }

  static constexpr uint32_t max() noexcept
  {
    return UINT32_MAX;
  }

private:
  uint64_t state_;
};
}

#endif