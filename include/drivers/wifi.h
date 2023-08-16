#ifndef DRIVERS_WIFI_H
#define DRIVERS_WIFI_H

namespace smartled::wifi
{
void Connect() noexcept;

bool IsConnected() noexcept;
}

#endif