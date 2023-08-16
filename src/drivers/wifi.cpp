#include "drivers/wifi.h"

#if defined(ESP8266)
#include <ESP8266WiFi.h>
#elif defined(ESP32) || defined(ARDUINO_ARCH_RP2040)
#include <WiFi.h>
#endif

#include "config.h"

namespace smartled::wifi
{
void Connect() noexcept
{
  wifi_set_sleep_type(NONE_SLEEP_T);
  WiFi.persistent(false);
  WiFi.mode(WIFI_OFF);
  WiFi.mode(WIFI_STA);

  WiFi.begin(WiFiSSID, WiFiPass, 6, WiFiBSSID);
}

bool IsConnected() noexcept
{
  return WiFi.status() == WL_CONNECTED;
}
} // namespace smartled::wifi