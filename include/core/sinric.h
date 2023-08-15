#ifndef SINRIC_H
#define SINRIC_H

#include "utility/color.h"

namespace smartled::sinric
{
void Connect() noexcept;

void Handle() noexcept;

bool IsPowerOn() noexcept;

uint8_t GetBrightness() noexcept;

Color GetColor() noexcept;
} // namespace smartled::sinric

#endif