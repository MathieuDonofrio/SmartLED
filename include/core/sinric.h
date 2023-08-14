#ifndef SINRIC_H
#define SINRIC_H

namespace smartled::sinric
{
void Initialize() noexcept;

void Handle() noexcept;

bool IsPowerOn() noexcept;
} // namespace smartled::sinric

#endif