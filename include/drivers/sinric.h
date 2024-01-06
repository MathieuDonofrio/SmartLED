#ifndef DRIVERS_SINRIC_H
#define DRIVERS_SINRIC_H

#include "drivers/strip.h"

namespace smartled::sinric
{
void Connect() noexcept;

void Handle() noexcept;

bool IsConnected() noexcept;

bool IsPowerOn() noexcept;

uint8_t GetBrightness() noexcept;

CRGB GetColor() noexcept;
} // namespace smartled::sinric

#endif