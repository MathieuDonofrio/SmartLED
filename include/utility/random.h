#ifndef UTILITY_RANDOM_H
#define UTILITY_RANDOM_H

#include <cstdint>
#include <random>

namespace smartled
{
template<uint64_t Multiplier = 6364136223846793005ull, uint64_t Increment = 1442695040888963407ull>
class Random
{
public:
  using result_type = uint32_t;

  constexpr Random() noexcept : Random(0) {}

  constexpr explicit Random(const uint64_t seed) noexcept : state_(seed ^ Multiplier)
  {
    discard(2);
  }

  constexpr uint32_t operator()() noexcept
  {
    // Reference: pcg-random.org

    const uint64_t old_state = state_;

    // Advance internal state
    state_ = old_state * Multiplier + (Increment | 1u);

    // Calculate output function (XSH RR), uses old state for max ILP
    const auto xor_shifted = static_cast<uint32_t>(((old_state >> 18u) ^ old_state) >> 27u);
    const auto rot = static_cast<uint32_t>(old_state >> 59u);

    return (xor_shifted >> rot) | (xor_shifted << ((-rot) & 31u));
  }

  constexpr void discard(uint64_t z) noexcept
  {
    for (uint64_t i = 0; i < z; ++i)
    {
      state_ = state_ * Multiplier + (Increment | 1u);
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
} // namespace smartled

#endif