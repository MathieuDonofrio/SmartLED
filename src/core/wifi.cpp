#include "core/wifi.h"

#if defined(ESP8266)
#include <ESP8266WiFi.h>
#elif defined(ESP32) || defined(ARDUINO_ARCH_RP2040)
#include <WiFi.h>
#endif

#include "config.h"

namespace smartled::wifi
{
bool IsConnected() noexcept
{
  return WiFi.SSID() == WiFiSSID && WiFi.status() == WL_CONNECTED;
}

void Connect() noexcept
{
  WiFi.persistent(true);
  WiFi.setAutoConnect(true);
  WiFi.setAutoReconnect(true);

#if defined(ESP8266)
  WiFi.setSleepMode(WIFI_NONE_SLEEP);
#elif defined(ESP32)
  WiFi.setSleep(false);
#endif

  WiFi.begin(WiFiSSID, WiFiPass, 0, WiFiBSSID);
}
} // namespace smartled::wifi